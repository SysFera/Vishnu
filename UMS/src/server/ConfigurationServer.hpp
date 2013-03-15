/**
* \file ConfigurationServer.hpp
* \brief This file presents the Class which manipulates VISHNU configuration data on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/
#ifndef CONFIGURATION_SERVER_H
#define CONFIGURATION_SERVER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <ecore.hpp>
#include <ecorecpp.hpp>
#include "SessionServer.hpp"
#include "UMS_Data.hpp"
#include "UMS_Data_forward.hpp"

/**
* \class ConfigurationServer
* \brief ConfigurationServer class implementation
*/
class ConfigurationServer {

public:
  /**
  * \brief Constructor
  * \param session The object which encapsulates session data
  */
  ConfigurationServer(SessionServer session);
  /**
  * \brief Constructor
  * \param configuration The Configuration data structure
  * \param session The object which encapsulates session data
  */
  ConfigurationServer(UMS_Data::Configuration*& configuration, SessionServer session);
  /**
  * \brief Function to save a VISHNU configuration
  * \return raises an exception on error
  */
  int
  save();
  /**
  * \brief Function to restore a VISHNU configuration
  * \param vishnuId The identifier of the vishnu instance
  * \return raises an exception on error
  */
  int
  restore(int vishnuId);
  /**
   * \brief Destructor
   */
  ~ConfigurationServer();
  /**
   * \brief Function to get Configuration data structure
   * \return  The LocalAccount data structure
   */
  UMS_Data::Configuration*
  getData();

private:

  /////////////////////////////////
  // Attributes
  /////////////////////////////////
  /**
  * \brief The Configuration data structure
  */
  UMS_Data::Configuration *mconfiguration;
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
   * \brief Function to get the sql code of users from a VISHNU configuration
   * \param user The user object
   * \param vishnuId The identifier of the vishnu instance
   * \return the sql code containing the sql code of users
   */
  std::string
  userToSql(UMS_Data::User_ptr user, int vishnuId);
  /**
   * \brief Function to get the sql code of machines from a VISHNU configuration
   * \param machine The machine object
   * \param vishnuId The identifier of the vishnu instance
   * \return the sql code containing the sql code of machines
   */
  std::string
  machineToSql(UMS_Data::Machine_ptr machine, int vishnuId);
  /**
   * \brief Function to get the sql code of machines description from a VISHNU configuration
   * \param machine The machine object
   * \return the sql code containing the sql code of machines description
   */
  std::string
  machineDescToSql(UMS_Data::Machine_ptr machine);
  /**
   * \brief Function to get the sql code of user-authentication system from a VISHNU configuration
   * \param authsystem The authSystem object
   * \param vishnuId The identifier of the vishnu instance
   * \return the sql code containing the sql code of authentication systems
   */
  std::string
  authSystemToSql(UMS_Data::AuthSystem_ptr authsystem, int vishnuId);
  /**
   * \brief Function to get the sql code of machines description from a VISHNU configuration
   * \param authsystem The authSystem object
   * \return the sql code containing the sql code of authentication systems based on ldap
   */
  std::string
  ldapAuthSystemToSql(UMS_Data::AuthSystem_ptr authsystem);
};
#endif
