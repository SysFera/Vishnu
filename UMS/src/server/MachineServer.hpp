/**
* \file MachineServer.hpp
* \brief This file presents the Class which manipulates VISHNU machine data on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/

#ifndef MACHINE_SERVER_H
#define MACHINE_SERVER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <exception>
#include "VishnuException.hpp"
#include "UMSVishnuException.hpp"
#include "SessionServer.hpp"
#include "UMS_Data.hpp"
#include "UMS_Data_forward.hpp"



/**
* \class MachineServer
* \brief MachineServer class implementation
*/
class MachineServer {

public:
  /**
  * \brief Constructor
  * \param machine The machine data structure
  */
  MachineServer(UMS_Data::Machine*& machine);
  /**
  * \brief Constructor
  * \param machine The machine data structure
  * \param session The object which encapsulates session data
  */
  MachineServer(UMS_Data::Machine*& machine, SessionServer& session);
  /**
  * \brief Function to add a new VISHNU machine
  * \param vishnuId The identifier of the vishnu instance
  * \return raises an exception on error
  */
  int
  add(int vishnuId);
  /**
  * \brief Function to update a VISHNU machine
  * \return raises an exception on error
  */
  int
  update();
  /**
  * \brief Function to delete a VISHNU machine
  * \return raises an exception on error
  */
  int
  deleteMachine();
  /**
  * \brief Destructor
  */
  ~MachineServer();
  /**
  * \brief Function to get machine information
  * \return  The user data structure
  */
  UMS_Data::Machine*
  getData();
  /**
  * \brief Function to get machine information from the database vishnu
  * \param condition The condition of the select request
  * \param attrname the name of the attribut to get
  * \return the value of the attribut or empty string if no results
  */
  std::string
  getAttribut(std::string condition, std::string attrname = "nummachineid");
  /**
   * \brief Function to get the machine
   * \return The name of the machine
   */
  std::string getMachineName();

  /**
   * \brief Function to check the machineId
   * \return raises an exception
   */
  void checkMachine();

private:
  /////////////////////////////////
  // Attributes
  /////////////////////////////////
  /**
  * \brief The machine data structure
  */
  UMS_Data::Machine *mmachine;
  /**
  * \brief An object which encapsulates session data
  */
  SessionServer msessionServer;
  /**
  * \brief An instance of vishnu database
  */
  Database *mdatabaseVishnu;
};
#endif
