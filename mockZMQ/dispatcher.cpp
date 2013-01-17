#include "Server.hpp"
#include "Annuary.hpp"
#include "utilVishnu.hpp"
#include "zhelpers.hpp"
#include "DIET_client.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include "UserException.hpp"
#include "utils.hpp"
#include "ExecConfiguration.hpp"


#define SEPARATOR "#"
#define INIT "$"

namespace bfs = boost::filesystem;

void
usage(){
  std::cout << "Usage: dispatcher [configFile]\n";
}

//function to get the first element from the annuary
std::string
elect(const std::vector<boost::shared_ptr<Server> >& serv){
  if (serv.empty()) {
    return "";
  }
  return serv.at(0)->getURI();
}

template<class Callable>
int
ZMQStartDevice(const std::string& uriExternal,
		const std::string& uriInproc,
		const int & nbWorker,
		boost::shared_ptr<Annuary>& ann) {

	// Prepare our context and the sockets for server
  boost::shared_ptr<zmq::context_t> context(new zmq::context_t(1));
  zmq::socket_t socket_server(*context, ZMQ_ROUTER);
  zmq::socket_t socket_workers(*context, ZMQ_DEALER);

  // bind the sockets
//  std::cout << boost::format("I: listening... (%1%)\n") % uriExternal;
  socket_server.bind(uriExternal.c_str());
  socket_workers.bind(uriInproc.c_str());

  // Create our threads pool
  ThreadPool pool(nbWorker);
  for (int i = 0; i < nbWorker; ++i) {
    pool.submit(Callable(context, uriInproc, i, ann));
  }

  // connect our workers threads to our server via a queue
  zmq::device(ZMQ_QUEUE, socket_server, socket_workers);

  return 0;
}

class ServiceWorker {
public:
  explicit ServiceWorker(boost::shared_ptr<zmq::context_t> ctx,
                         const std::string & uriInproc, int id,
                         boost::shared_ptr<Annuary>& ann)
    : ctx_(ctx), uriInproc_(uriInproc), id_(id), mann(ann) {}

  void
  operator()() {
    Socket socket(*ctx_, ZMQ_REP);
    socket.connect(uriInproc_.c_str());

    while (true) {
      //Receive message from ZMQ
      zmq::message_t message(0);
      try {
        if (!socket.recv(&message, 0)) {
        }
      } catch (zmq::error_t &error) {
        std::cerr << boost::format("E: %1%\n") % error.what();
      }
      // Deserialize and call UMS Method
      if (message.size() != 0) {
        boost::shared_ptr<diet_profile_t> profile(my_deserialize(static_cast<const char*>(message.data())));
        std::string servname = profile->name;
        std::vector<boost::shared_ptr<Server> > serv = mann->get(servname);
        std::string uriServer = elect(serv);

        std::string resultSerialized =
          (boost::format("error %1%: the service %2% is not available")
           % vishnu::convertToString(ERRCODE_INVALID_PARAM)
           % servname).str();
        if (!uriServer.empty()) {
//            std::cout << my_serialize(profile.get());
            diet_call_gen(profile.get(), uriServer);
            resultSerialized = my_serialize(profile.get());
        }
//        std::cout << boost::format("I: Sending> %1%...\n") % resultSerialized;
        socket.send(resultSerialized);
      }
    }
  }

private:
  boost::shared_ptr<zmq::context_t> ctx_; /**< zmq context */
  std::string uriInproc_; /**< worker id */
  int id_; /**< worker id */
  boost::shared_ptr<Annuary>& mann;
};

//FIXME: clear unused parameters
class SubscriptionWorker {
public:
  explicit SubscriptionWorker(boost::shared_ptr<zmq::context_t> ctx,
                              const std::string & uriInproc, int id,
                              boost::shared_ptr<Annuary>& ann)
    : ctx_(ctx), uriInproc_(uriInproc), id_(id), mann(ann) {}

  void
  operator()() {
    Socket socket(*ctx_, ZMQ_REP);
    socket.connect(uriInproc_.c_str());

    while (true) {
      //Receive message from ZMQ
      zmq::message_t message(0);
      try {
        if (!socket.recv(&message, 0)) {
        }
      } catch (zmq::error_t &error) {
        std::cerr << boost::format("E: %1%\n") % error.what();
      }
      std::string data(static_cast<const char*>(message.data()), message.size());
//      std::cout << boost::format("I: Recv> %1%, size %2%\n") % data % data.length();

      int mode = vishnu::convertToInt(data.substr(0,1));

      // Deserialize
      boost::shared_ptr<Server> server = Server::fromString(data.substr(1));

      if (mode == 1) { // If add a server
        mann->add(server->getName(), server->getURI(),
                        server->getServices());
      } else if (mode == 0) {
        mann->remove(server->getName(), server->getURI());
      }
      std::string resultSerialized = "OK";

      // Send reply back to client
//      std::cout << boost::format("I: Sending> %1%...\n") % resultSerialized;
      socket.send(resultSerialized);
    }
  }

private:
  boost::shared_ptr<zmq::context_t> ctx_; /**< zmq context */
  std::string uriInproc_; /**< worker id */
  int id_; /**< worker id */
  boost::shared_ptr<Annuary> mann;
};


class AddressDealer{
public:
  AddressDealer(std::string uri, boost::shared_ptr<Annuary>& ann, int nbThread)
    : muri(uri), mann(ann), mnbThread(nbThread) {}

  ~AddressDealer() {}

  void
  run() {
    ZMQStartDevice<ServiceWorker>(muri, "inproc://vishnuServiceWorker",
                                  mnbThread, mann);
  }


private:
  std::string muri;
  boost::shared_ptr<Annuary>& mann;
  int mnbThread;
};

class AddressSubscriber{
public:
  AddressSubscriber(std::string uri, boost::shared_ptr<Annuary>& ann, int nbThread)
    : muri(uri), mann(ann), mnbThread(nbThread) {}

  ~AddressSubscriber() {}

  void
  run(){
    ZMQStartDevice<SubscriptionWorker>(muri, "inproc://vishnuSubcriberWorker",
                                       mnbThread, mann);
  }


private:
  std::string muri;
  boost::shared_ptr<Annuary> mann;
  int mnbThread;
};

class Heartbeat{
public:
  Heartbeat(int freq, boost::shared_ptr<Annuary> ann)
    : mfreq(freq), mann(ann) {}

  ~Heartbeat() {}

  void
  run() {
    zmq::context_t ctxt(1);
    while (true) {
      std::vector<boost::shared_ptr<Server> > serv = mann->get();
      BOOST_FOREACH(boost::shared_ptr<Server> it,  serv) {
        std::string uri = it->getURI();
        LazyPirateClient lpc(ctxt, uri);
        diet_profile_t* hb = NULL;
        hb = diet_profile_alloc("heartbeat", 0, 0, 1);
        //OUT Parameters
        diet_string_set(hb,0, const_cast<char *>("hb"));
        diet_string_set(hb,1);
        std::string p1 = my_serialize(hb);

//        std::cout << boost::format("I: Sending> %1%...\n") % p1;
        if (!lpc.send(p1)) {
//          std::cout << boost::format("I: Sed Disconnected %1%\n") % uri;
          mann->remove(it->getName(), it->getURI());
        }
      }
      sleep(mfreq);
    }
  }


private:
  int mfreq;
  boost::shared_ptr<Annuary> mann;
};



int
main(int argc, char** argv) {
  // Prepare our context and socket
  boost::shared_ptr<Annuary> ann = boost::make_shared<Annuary>();

  // Set default values
  std::string  uriAddr = "tcp://127.0.0.1:5560";  // localhost and 5560
  std::string  uriSubs = "tcp://127.0.0.1:5561";  // localhost and 5561
  std::string  confFil;  // no init configuration file
  unsigned int nthread = 5;  // 5 threads to manage requests
  unsigned int timeout = 10; // wait 10s before retrying

  ExecConfiguration config;
  if (argc == 2) {
    config.initFromFile(argv[1]);
    config.getRequiredConfigValue<std::string>(vishnu::DISP_URIADDR, uriAddr);
    config.getRequiredConfigValue<std::string>(vishnu::DISP_URISUBS, uriSubs);
    config.getRequiredConfigValue<std::string>(vishnu::DISP_INITFILE, confFil);
    config.getRequiredConfigValue<unsigned int>(vishnu::DISP_TIMEOUT, timeout);
    config.getRequiredConfigValue<unsigned int>(vishnu::DISP_NBTHREAD, nthread);
  }

  std::cerr << "====== Initial configuration =====\n"
            << "disp_uriAddr=" << uriAddr << "\n"
            << "disp_uriSubs=" << uriSubs << "\n"
            << "disp_initFile=" << confFil << "\n"
            << "disp_timeout=" << timeout << "\n"
            << "disp_nbthread=" << nthread << "\n"
            << "==================================\n";


  // Get initial configuration
  if (confFil != "") {
    ann->initFromFile(confFil);
  }
  ann->print();


  AddressDealer AD = AddressDealer(uriAddr, ann, nthread);
  AddressSubscriber AS = AddressSubscriber(uriSubs, ann, nthread);

  boost::thread th1(boost::bind(&AddressDealer::run, &AD));//%RELAX<MISRA_0_1_3> Because it used to launch a thread
  boost::thread th2(boost::bind(&AddressSubscriber::run, &AS));//%RELAX<MISRA_0_1_3> Because it used to launch a thread
//  boost::thread th3(boost::bind(&Heartbeat::run, &HB));//%RELAX<MISRA_0_1_3> Because it used to launch a thread

  // To avoid quitting too fast in case of problems
  while(1) {
    sleep(1000);
  }
  return 0;
}
