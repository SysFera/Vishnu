/**
* \file LocalAccountServer.hpp
* \brief This file presents the Class which manipulates VISHNU localAccount data on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/

#ifndef LOCAL_ACCOUNT_SERVER_H
#define LOCAL_ACCOUNT_SERVER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "SessionServer.hpp"
#include "UMS_Data.hpp"
#include "UMS_Data_forward.hpp"
#include "MachineServer.hpp"

/**
* \class LocalAccountServer
* \brief LocalAccountServer class implementation
*/
class LocalAccountServer {
public:
  /**
  * \brief Constructor
  * \param account The LocalAccount data structure
  * \param session The object which encapsulates session data
  */
  LocalAccountServer(UMS_Data::LocalAccount*& account, SessionServer& session);
  /**
  * \brief Function to add a new VISHNU localAccount
  * \return raises an exception on error
  */
  int
  add();
  /**
  * \brief Function to update a VISHNU localAccount
  * \return raises an exception on error
  */
  int
  update();
  /**
   * \brief Function to delete a VISHNU localAccount
   * \return raises an exception on error
   */
  int
  deleteLocalAccount();
  /**
   * \brief Destructor,
   */
  ~LocalAccountServer();
  /**
  * \brief Function to get localAccount data structure
  * \return  The LocalAccount data structure
  */
  UMS_Data::LocalAccount*
  getData();
  /**
   * \brief Function to get localAccount information from the database vishnu
   * \param condition The condition of the select request
   * \param attrname the name of the attribut to get
   * \return the value of the attribut or empty string if no results
   */
  std::string
  getAttribut(std::string condition, std::string attrname = "numaccountid");
  /**
   * \brief Function to get the content of the public ssh generated
   * \return The content of the ssh public key generated
   */
  std::string
  getPublicKey();

private:
  /////////////////////////////////
  // Attributes
  /////////////////////////////////
  /**
  * \brief The localAccount data structure
  */
  UMS_Data::LocalAccount *mlocalAccount;
  /**
  * \brief An object which encapsulates session data
  */
  SessionServer msessionServer;
  /**
  * \brief An instance of vishnu database
  */
  Database *mdatabaseVishnu;
  /**
  * \brief The content of the ssh public key generated
  */
  std::string msshpublickey;

  /////////////////////////////////
  // Functions
  /////////////////////////////////
  /**
   * \brief Function to generate a private/public ssh key
   */
  std::string
  generateKey();
  /**
   * \brief Function to check localAccount on database
   * \param idmachine The id of the machine
   * \param iduser The id of the user
   * \return true if the localAccount exists else false
   */
  bool
  exist(std::string idmachine, std::string iduser);
  /**
  * \brief Function to check if a given login is used on a machine
  * \param numMachine the internal id of the machine
  * \param acLogin the account login
  * \return true if the login is already used on the machine
  */
  bool
  isLoginUsed(std::string numMachine, std::string acLogin);
};
#endif
