#ifndef _ZHELPERS_HPP_
#define _ZHELPERS_HPP_

#include <zmq.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <cstring>
#include <cerrno>

#include "utils.hpp"

const int DEFAULT_TIMEOUT = 120; // seconds

/**
 * @class wraps zmq::socket_t to simplify its use
 * with std::string
 */
class Socket : public zmq::socket_t, public boost::noncopyable {
public:
  Socket(zmq::context_t& ctx, int type) : zmq::socket_t(ctx, type) {}

  /**
   * @brief set linger period for socket shutdown
   * @param linger linger time (default: -1 means infinite)
   * @returns true if it succeeded
   */
  bool
  setLinger(int linger = -1) {
    try {
      setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
      return true;
    } catch (const zmq::error_t& e) {
      return false;
    }
  }

  /**
   * @brief wraps zmq::socket_t connect
   * @param addr connection uri
   * @return void
   * @throw error_t if it fails
   */
  void
  connect(const std::string& addr) {
    connect(addr.c_str());
  }

  /**
   * @brief wraps zmq::socket_t connect
   * @param addr connection uri
   * @return void
   * @throw error_t if it fails
   */
  void
  connect(const char* addr) {
    /* we explicitely call base class method to avoid
       looping method calls */
    socket_t::connect(addr);
  }

  /**
   * @brief send data
   * @param data string to be sent
   * @param flags zmq flags
   * @return true if it succeeded
   */
  bool
  send(const std::string& data, int flags = 0) {
    return send(data.c_str(), data.length()+1, flags);
  }

  /**
   * @brief send data
   * @param data buffer to be sent
   * @param flags zmq flags
   * @return true if it succeeded
   */
  bool
  send(const char* data, int flags = 0) {
    return send(data, strlen(data)+1, flags);
  }

  /**
   * @brief get response for server
   * @param flags zmq flags
   * @return message
   */
  std::string
  get(int flags = 0) {
    zmq::message_t message;
    bool rv = false;

    do {
      try {
        rv = recv(&message, flags);
        break;
      } catch (const zmq::error_t& e) {
        if (EINTR == e.num()) {
          continue;
        } else {
          throw e;
        }
      }
    } while(true);

    if (!rv) {
      throw zmq::error_t();
    }


    const char *dat = static_cast<const char*>(message.data());
    // check that we receive or not a null-terminated string aka C strings
    size_t sz = message.size();
    const char* pos = dat + sz;

    return std::string(dat, pos);
  }

private:
  /**
   * @brief internal method that sends message
   * @param data buffer to be sent
   * @param len size of the buffer
   * @param flags zmq flags
   * @return true if it succeeded
   */
  bool
  send(const char* data, size_t len, int flags = 0) {
    zmq::message_t msg(len);
    memcpy(msg.data(), data, len);

    return socket_t::send(msg, flags);
  }
};


/**
 * @class implements the Lazy Pirate pattern, argh matey !
 */
class LazyPirateClient {
public:
  LazyPirateClient(zmq::context_t& ctx, const std::string& addr,
                   const int timeout = DEFAULT_TIMEOUT)
    : addr_(addr), ctx_(ctx), timeout_(timeout * 1000000) {
    reset();
  }

  /**
   * @brief most of the pattern is implemented here
   * @param data message to be sent
   * @param retries number of retries
   * @return true if it succeeded
   */
  bool
  send(const std::string& data, int retries = 3) {
    while (retries) {
      sock_->send(data);
      bool expect_reply(true);

      while (expect_reply) {
        zmq::pollitem_t items[] = { {*sock_, 0, ZMQ_POLLIN, 0} };
        zmq::poll(&items[0], 1, timeout_);

        if (items[0].revents & ZMQ_POLLIN) {
          buff_ = sock_->get();
          if (buff_.length()) {
            return true;
          } else {
            std::cerr << "E: received weird reply from server\n";
          }
        } else {
          if (--retries == 0) {
            std::cerr << "E: server seems offline, abandonning\n";
            expect_reply = false;
            break;
          } else {
            std::cerr << boost::format("W: no response from %1%, retrying ...\n") % addr_;
            reset();
            sock_->send(data);
          }
        }
      }
    }
    return false;
  }

  std::string
  recv() const {
    return buff_;
  }


private:
  void
  reset() {
    sock_.reset(new Socket(ctx_, ZMQ_REQ));
    sock_->connect(addr_);
    sock_->setLinger(0);
  }

  std::string addr_;
  std::string buff_;
  zmq::context_t& ctx_;
  boost::scoped_ptr<Socket> sock_;
  long timeout_;
};


template<typename WorkerType,
         typename WorkerParam1,
         typename WorkerParam2>
int
serverWorkerSockets(const std::string& serverUri,
                    const std::string& workerUri,
                    int nbThreads,
                    WorkerParam1 params1,
                    WorkerParam2 params2) {
  boost::shared_ptr<zmq::context_t> context(new zmq::context_t(1));
  zmq::socket_t socket_server(*context, ZMQ_ROUTER);
  zmq::socket_t socket_workers(*context, ZMQ_DEALER);

  // bind the sockets
  try {
    socket_server.bind(serverUri.c_str());
  } catch (const zmq::error_t& e) {
    std::cerr << boost::format("E: zmq socket_server (%1%) binding failed (%2%)\n") % serverUri % e.what();
    return 1;
  }

  try {
    socket_workers.bind(workerUri.c_str());
  } catch (const zmq::error_t& e) {
    std::cerr << boost::format("E: zmq socket_worker (%1%) binding failed (%2%)\n") % workerUri % e.what();
    return 1;
  }

  std::cout << boost::format("I: listening... (%1%)\n") % serverUri;

  // Create our pool of threads
  ThreadPool pool(nbThreads);
  for (int i = 0; i < nbThreads; ++i) {
    pool.submit(WorkerType(context, params1, i, params2));
  }

  // connect our workers threads to our server via a queue
  do {
    try {
      zmq::device(ZMQ_QUEUE, socket_server, socket_workers);
      break;
    } catch (const zmq::error_t& e) {
      if (EINTR == e.num()) {
        continue;
      } else {
        std::cerr << boost::format("E: zmq device creation failed (%1%)\n") % e.what();
        return 1;
      }
    }
  } while(true);

  return 0;
}



#endif /* _ZHELPERS_HPP_ */
