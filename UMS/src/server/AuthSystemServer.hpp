/**
* \file AuthSystemServer.hpp
* \brief This file presents the Class which manipulates VISHNU AuthSystem data on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 03/02/2012
*/

#ifndef AUTH_SYSTEM_SERVER_H
#define AUTH_SYSTEM_SERVER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "SessionServer.hpp"
#include "UMS_Data.hpp"
#include "UMS_Data_forward.hpp"


/**
* \class AuthSystemServer
* \brief AuthSystemServer class implementation
*/
class AuthSystemServer {
public:
  /**
  * \brief Constructor
  * \param authSystem The AuthSystem data structure
  */
  AuthSystemServer(UMS_Data::AuthSystem*& authSystem);
  /**
  * \brief Constructor
  * \param authSystem The AuthSystem data structure
  * \param session The object which encapsulates session data
  */
  AuthSystemServer(UMS_Data::AuthSystem*& authSystem, SessionServer& session);
  /**
  * \brief Function to add a new VISHNU localAccount
  * \param vishnuId The identifier of the vishnu instance
  * \return raises an exception on error
  */
  int
  add(int vishnuId);
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
  deleteAuthSystem();
  /**
  * \brief Destructor,
  */
  ~AuthSystemServer();
  /**
  * \brief Function to get localAccount data structure
  * \return  The AuthSystem data structure
  */
  UMS_Data::AuthSystem*
  getData();
  /**
  * \brief Function to get localAccount information from the database vishnu
  * \param condition The condition of the select request
  * \param attrname the name of the attribut to get
  * \return the value of the attribut or empty string if no results
  */
  std::string
  getAttribut(std::string condition, std::string attrname = "numauthsystemid");

private:
  /////////////////////////////////
  // Attributes
  /////////////////////////////////
  /**
  * \brief The AuthSystem data structure
  */
  UMS_Data::AuthSystem *mauthsystem;
  /**
  * \brief An object which encapsulates session data
  */
  SessionServer msessionServer;
  /**
  * \brief An instance of vishnu database
  */
  Database *mdatabaseVishnu;

  /////////////////////////////////
  // Functions
  /////////////////////////////////
 /**
  * \brief Function to check the user-authentication system on database
  * \return true if the user-authentication system exists else false
  */
  bool
  exist();
  /**
  * \brief Function to check the user-authentication system parameters values
  *\return raises an exception on error
  */
  int
  checkValues();
  /**
  * \brief Function to check the $USERNAME string on the ldap base
  *\return raises an exception on error
  */
  int
  checkLdapBase();
};
#endif
