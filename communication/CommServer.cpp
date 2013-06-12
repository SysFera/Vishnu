#include "CommServer.hpp"

#include <boost/shared_ptr.hpp>

#include "Database.hpp"
#include "DbFactory.hpp"
#include "utilVishnu.hpp"
#include "utilServer.hpp"
#include "SystemException.hpp"
#include "zmq.hpp"
#include "DIET_client.h"
#include "Server.hpp"
#include "zhelpers.hpp"
#include "SeD.hpp"

// TODO IMPLEMENT ME
int
unregisterSeD(const std::string& type, const ExecConfiguration& config) {
  return 0;
}

void
validateUri(const std::string & uri) {
  size_t pos = uri.find("*");
  if (pos != std::string::npos) {
    throw UserException(ERRCODE_INVALID_PARAM,
                        std::string("W: character '*' is not permitted in the uri"));
  }
}

int
registerSeD(const std::string& type,
            const ExecConfiguration& config,
            std::vector<std::string>& services,
            SslCryptoClient* cipher) {
  std::string uri;
  std::string mid;
  std::string uridispatcher;
  std::string urlsup;
  int timeout = 10;

  // Getting the machine id
  config.getRequiredConfigValue<std::string>(vishnu::MACHINEID, mid);
  config.getConfigValue<int>(vishnu::TIMEOUT, timeout);
  if (timeout <= 0) {
    timeout = 10;
  }

  config.getRequiredConfigValue<std::string>(vishnu::DISP_URISUBS, uridispatcher);
  config.getRequiredConfigValue<std::string>(vishnu::URLSUPERVISOR, urlsup);
  if (type == "fmssed") {
    config.getRequiredConfigValue<std::string>(vishnu::FMS_URIADDR, uri);
  } else  if (type == "imssed") {
    config.getRequiredConfigValue<std::string>(vishnu::IMS_URIADDR, uri);
  } else  if (type == "tmssed") {
    config.getRequiredConfigValue<std::string>(vishnu::TMS_URIADDR, uri);
  } else { // presumably UMS
    config.getRequiredConfigValue<std::string>(vishnu::UMS_URIADDR, uri);
  }

  // Check that the uri does not contain *
  validateUri(uridispatcher);

  // Register in database
  if (vishnu::isNew(urlsup, mid, type)) {
    std::string request = "insert into process (dietname, launchscript, machineid, pstatus, uptime, vishnuname) values ('"+urlsup+"','"+config.scriptToString()+"','"+mid+"','"+vishnu::convertToString(vishnu::PRUNNING)+"',CURRENT_TIMESTAMP, '"+type+"')";
    try {
      DbFactory factory;
      Database* database = factory.getDatabaseInstance();
      database->process(request.c_str());
    } catch (SystemException& e) {
      if (type.compare("umssed")!=0){
        throw (e);
      }
    }
  }

  zmq::context_t ctx(1);
  LazyPirateClient lpc(ctx, uridispatcher, cipher, timeout);

  boost::shared_ptr<Server> s = boost::shared_ptr<Server> (new Server(type, services, uri));
  // prefix with 1 to say registering the sed
  std::string req = "1" + s.get()->toString();

  if (!lpc.send(req)) {
    std::cerr << "W: failed to register in the naming service\n";
    return -1; //instead of exiting
  }
  std::string response = lpc.recv();

  return 0;
}

void
initSeD(const std::string& type, const ExecConfiguration& config,
        const std::string& uri, boost::shared_ptr<SeD> server) {

  std::string rsaPubkey;
  std::string rsaPrivkey;
  SslCryptoServer* serverCipher = NULL;
  SslCryptoClient* clientCipher = NULL;
  bool useSsl = false;
  if (config.getConfigValue<bool>(vishnu::USE_SSL, useSsl) &&  useSsl) {
    config.getRequiredConfigValue<std::string>(vishnu::SERVER_PRIVATE_KEY, rsaPrivkey);
    config.getRequiredConfigValue<std::string>(vishnu::SERVER_PUBLIC_KEY, rsaPubkey);
    serverCipher = new SslCryptoServer(rsaPrivkey);
    clientCipher = new SslCryptoClient(rsaPubkey);
  }

  // Initialize the DIET SeD
  try {
    std::vector<std::string> ls = server.get()->getServices();
    registerSeD(type, config, ls, clientCipher);
  } catch (VishnuException& e) {
    std::cout << "failed to register with err" << e.what()  << std::endl;
  }

  ZMQServerStart(server, uri, serverCipher);
  unregisterSeD(type, config);
}
