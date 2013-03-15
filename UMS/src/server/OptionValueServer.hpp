/**
* \file OptionValueServer.hpp
* \brief This file presents the Class which manipulates VISHNU options on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/

#ifndef OPTION_VALUE_SERVER_H
#define OPTION_VALUE_SERVER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <exception>
#include "VishnuException.hpp"
#include "UMS_Data.hpp"
#include "UMS_Data_forward.hpp"
#include "Database.hpp"

class SessionServer;

static const std::string CLOSEPOLICY_OPT = "VISHNU_CLOSE_POLICY";
static const std::string TIMEOUT_OPT = "VISHNU_TIMEOUT";
static const std::string TRANSFERCMD_OPT = "VISHNU_TRANSFER_CMD";

/**
* \class OptionValueServer
* \brief OptionValueServer class implementationT
*/
class OptionValueServer {

public:
  /**
   * \brief Constructor
   */
  OptionValueServer();
  /**
   * \brief Constructor
   * \param optionvalue the option data structure
   * \param session The object to manipulate session
   */
  OptionValueServer(UMS_Data::OptionValue*& optionvalue, SessionServer session);
  /**
   * \brief Function to configure options on the database
   * \param defaultOptions the flag to get data from defauts options table
   * \return  raises an exception on error
   */
  int
  configureOption(bool defaultOptions = false);
  /**
   * \brief Destructor
   */
  ~OptionValueServer();
  /**
   * \brief Function to get option data structure
   * \return  The user data structure
   */
  UMS_Data::OptionValue*
  getData();
  /**
   * \brief Function to get option information from the database vishnu
   * \param condition The condition of the select request
   * \param attrname the name of the attribut to get
   * \param defaultOptions the flag to get data from defauts options table
   * \return the value of the attribut or empty string if no results
   */
  std::string
  getAttribut(std::string condition, std::string attrname="value", bool defaultOptions=false);
  /**
  * \brief Function to get user option value
  * \param numuserId The database number id of the user
  * \param optionName the name of the option
  * \return The error or success code
  */
  int
  getOptionValueForUser(std::string numuserId, std::string optionName);

private:
  /////////////////////////////////
  // Attributes
  /////////////////////////////////
  /**
  * \brief The option data structure
  */
  UMS_Data::OptionValue *moptionValue;
  /**
  * \brief An instance of vishnu database
  */
  Database *mdatabaseVishnu;
  /**
  * \brief An object which encapsulates user data
  */
  SessionServer *msessionServer;

  /////////////////////////////////
  // Function
  /////////////////////////////////
  /**
   * \brief Function to check the value for a specific option
   * \return  true if the option value is correct else false
   */
  bool
  isCorrectValue();
};
#endif//OPTION_VALUE_SERVER_H
