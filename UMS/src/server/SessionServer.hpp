/**
* \file SessionServer.hpp
* \brief This file presents the Class which manipulates VISHNU sessions on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/

#ifndef SESSION_SERVER_H
#define SESSION_SERVER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <ecore.hpp>
#include <ecorecpp.hpp>
#include <iostream>
#include <exception>
#include <boost/scoped_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "VishnuException.hpp"
#include "UMSVishnuException.hpp"
#include "SystemException.hpp"
#include "UMS_Data.hpp"
#include "UMS_Data_forward.hpp"
#include "UserServer.hpp"
#include "MachineClientServer.hpp"
#include "OptionValueServer.hpp"
#include "utilVishnu.hpp"
#include "utilServer.hpp"


class UserServer;

using namespace vishnu;
using namespace boost::posix_time;
using namespace boost::gregorian;

/**
* \class SessionServer
* \brief UserServer class implementation
*/
class SessionServer {
public:
  /**
  * \brief Constructor
  * \fn SessionServer()
  */
  SessionServer();
  /**
  * \brief Constructor
  * \fn SessionServer(std::string sessionKey);
  * \param sessionKey The session key of the session
  */
  SessionServer(std::string sessionKey);
  /**
  * \brief Constructor
  * \fn SessionServer(const UMS_Data::Session& session)
  * \param session The session data structure
  */
  SessionServer(const UMS_Data::Session& session);
  /**
  * \brief Function to connect the session
  * \fn int connectSession(UserServer user, MachineClientServer host, UMS_Data::ConnectOptions* connectOpt)
  * \param user The object which manipulates user information
  * \param host The object which manipulates client machine information
  * \param connectOpt The options data structure for connection
  * \return raises an exception on error
  */
  int
  connectSession(UserServer user, MachineClientServer host, UMS_Data::ConnectOptions* connectOpt);
  /**
  * \brief Function to reconnect the session
  * \fn int reconnect(UserServer, MachineClientServer, std::string sessionId)
  * \param user The object which manipulates user information
  * \param host The object which manipulates client machine information
  * \param sessionId The session identifier
  * \return raises an exception on error
  */
  int
  reconnect(UserServer user, MachineClientServer host, std::string sessionId);
  /**
  * \brief Function to close the session
  * \fn int close()
  * \return raises an exception on error
  */
  int
  close();
  /**
  * \brief Destructor
  * \fn ~SessionServer()
  */
  ~SessionServer();
  /**
  * \brief Function to get the session information
  * \fn UMS_Data::Session getData()
  * \return  The session data structure
  */
  UMS_Data::Session
  getData() const;
  /**
  * \brief Function to get user information from the database vishnu
  * \fn getAttribut(std::string condition, std::string attrname);
  * \param condition The condition of the select request
  * \param attrname the name of the attribut to get
  * \return the value of the attribut or empty string if no results
  */
  std::string
  getAttribut(std::string condition, std::string attrname="sessionkey");
  /**
  * \brief Function to save the date of the last connection
  * \fn int saveConnection()
  * \return raises an exception on error
  */
  int
  saveConnection();
  /**
  * \brief Function to get the list of sessions with close on timeout mode to close
  * \fn DatabaseResult* getSessionToclosebyTimeout()
  * \return the list of results
  */
  DatabaseResult*
  getSessionToclosebyTimeout();
  /**
  * \brief Function to make a complete checking of the session key
  * \fn int check()
  * \return raises an exception on error
  */
  int
  check();
  /**
  * \brief Function to finalize the service
  * \param cmdDescription The description of the command
  * \param cmdType The type of the command (UMS, TMS, FMS, IMS)
  * \param cmdStatus The status of the command
  * \param newVishnuObjectID the new vishnu object Id
  * \return raises an exception on error
  */
  int
  finish (std::string cmdDescription,
          CmdType cmdType,
          CmdStatus cmdStatus,
          std::string newVishnuObjectID = "");

  private:
  /////////////////////////////////
  // Attributes
  /////////////////////////////////
  /**
  * \brief The session data structure
  */
  UMS_Data::Session msession;
  /**
  * \brief An instance of vishnu database
  */
  Database* mdatabaseVishnu;

  /////////////////////////////////
  // Functions
  /////////////////////////////////
  /**
  * \brief Function to generate the session key
  * \fn    int generateSessionKey(std::string salt)
  * \param salt This string is used to perturb the algorithm
  * \return an encrypted message registered on the session data structure
  */
  int
  generateSessionKey(std::string salt);
  /**
  * \brief Function to generate the session identifier
  * \fn int generateSessionId(std::string userId)
  * \param userId the userId of the owner of the session
  * \return record the the session id on the session data structure
  */
  int
  generateSessionId(std::string userId);
  /**
  * \brief Function to record the session on the database
  * \fn int recordSessionServer(std::string idmachine, std::string iduser)
  * \param idmachine the database number id of the client machine
  * \param iduser the database number id of the owner of the session
  * \return record the the session id on the session data structure
  */
  int
  recordSessionServer(std::string idmachine, std::string iduser);
  /**
  * \brief Function to check the session on database
  * \fn bool exist(bool flagSessionId)
  * \param flagSessionId A flag to check the session id
  * \return true if the session key (or sessionId) exists else false
  */
  bool
  exist(bool flagSessionId = false);
  /**
  * \brief Function to check the session on database
  * \fn int getState(bool flagSessionId)
  * \param flagSessionId A flag to check the session identifier
  * \return the session status
  */
  int
  getState(bool flagSessionId = false);
  /**
  * \brief Function to check the session on database
  * \fn int getSessionkey(std::string idmachine, std::string iduser, bool flagAdmin = false)
  * \param idmachine the database number id of the client machine
  * \param iduser the database number id of the owner of the session
  * \param flagAdmin A flag for an admin to get the session key from another user
  * \return 0 on success and -1 if there is no results
  */
  int
  getSessionkey(std::string idmachine, std::string iduser, bool flagAdmin = false);
  /**
  * \brief Function to solve the session connection parameters
  * \fn int solveConnectionMode(UMS_Data::ConnectOptions* connectOpt, std::string numuserId)
  * \param connectOpt the connection parameters
  * \param numuserId the database number id of the user to connect
  * \return the connection parameters are registered on the session data structure
  */
  int
  solveConnectionMode(UMS_Data::ConnectOptions* connectOpt, std::string numuserId);
  /**
  * \brief Function to change the closure connection mode disconnet to timeout
  * \fn int disconnetToTimeout(UserServer user)
  * \param user The object which manipulates user information
  * \return the new connection parameters are registered on the session data structure
  */
  int
  disconnetToTimeout(UserServer user);
};
#endif
