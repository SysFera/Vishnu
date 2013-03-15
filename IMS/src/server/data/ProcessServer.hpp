/**
 * \file ProcessServer.hpp
 * \brief This file defines the processes interaction with the database
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 * \date 19/04/11
 */

#ifndef __PROCESSSERVER__HH__
#define __PROCESSSERVER__HH__

#include <string>
#include <ecore.hpp> // Ecore metamodel
#include <ecorecpp.hpp> // EMF4CPP utils
#include "IMS_Data.hpp"
#include "SessionServer.hpp"

/**
 * \class ProcessServer
 * \brief Class linking the database and the processes
 */
class ProcessServer{
public:
  /**
   * \brief If the process is running
   */
  static const int PRUNNING = 1;
  /**
   * \brief If the process is down
   */
  static const int PDOWN = 2;
  /**
   * \brief If the process is deleted
   */
  static const int PDELETED = 3;
  /**
   * \brief Constructor
   */
  ProcessServer(const UserServer session);
  /**
   * \brief Constructor
   */
  ProcessServer(IMS_Data::ProcessOp_ptr op, const UserServer session);
  /**
   * \brief Destructor
   */
  ~ProcessServer();
  /**
   * \brief Function to list query information
   * \return The pointer to the ListOject containing list information
   * \return raises an exception on error
   */
  IMS_Data::ListProcesses*
  list();

  /**
   * \brief Function to get the name of the query command line
   * \return The the name of the query command line
   */
  std::string getCommandName();
  /**
   * \brief To update the database with a process connexion
   * \param proc: The process that has just connected
   * \return Success, an error code otherwise
   */
  int
  connectProcess(IMS_Data::Process_ptr proc);
  /**
   * \brief To update the database with a process disconnexion
   * \param proc: The process that has just disconnected
   * \return Success, an error code otherwise
   */
  int
  disconnectProcess(IMS_Data::Process_ptr proc);
  /**
   * \brief To update the database with the link between the diet and vishnu id
   * \param proc: The process that has just been authentified
   * \return Success, an error code otherwise
   */
  int
  authentifyProcess(IMS_Data::Process_ptr proc);
  /**
   * \brief To set a process as stopped
   * \param proc: The proc to flag as stopped
   * \return Success, an error code otherwise
   */
  int
  stopProcess(IMS_Data::Process_ptr proc);

  /**
   * \brief To set a process as stopped
   * \param proc: The proc down to flag as stopped (means restarted)
   * \return Success, an error code otherwise
   */
  int
  setRestarted(IMS_Data::Process_ptr proc);

  /**
   * \brief To set all running processes as stopped on the machine
   * \param proc: The proc to flag as stopped
   * \return Success, an error code otherwise
   */
  int
  stopAllProcesses(IMS_Data::Process_ptr proc);
  /**
   * \brief Return true if the process with a diet name Pname is of type IMS
   * \param Pname: DIET name of the process
   * \return True if Pname represents an IMS SeD
   */
  bool
  isIMSSeD(std::string Pname);
  /**
   * \brief Return true if the process with a diet name Pname is of type IMS
   * \param machine:  The vishnu machine id
   * \param type: The type of the sed
   * \return True if no process on this machine and of this type are down
   */
  bool
  checkStopped(std::string machine, std::string type);
  /**
   * \brief To get the script content from the machineId and dietName
   * \param p: Process to fill
   */
  void
  fillContent(IMS_Data::Process_ptr p);
  /**
   * \brief To get the script content from the dietId
   * \param p: Process to fill
   */
  void
  getDataFromDietId(IMS_Data::Process_ptr p);
  /**
   * \brief To get the hostname on the machine mmid
   * \param mmid: Vishnu machine id
   * \param hostname: hostname of the machine
   * \param acclog: Account login of the user 'root' on the machine
   */
  void
  getHost(std::string mmid, std::string &hostname, std::string& acclog);

  /**
   * \brief Return the last actif ims server
   * \return The last updated running IMS sed
   */
  std::string
  getElectedMid();
  /**
   * \brief Get the URI associated to the supervisor process for the server (located in dietname field in DB)
   * \return The URI
   */
  std::string
  getURI();

protected:
private:
  /**
   * \brief Position of the diet name in the process table, starting at 0
   */
  static const int NAMEPOS = 2;
  /**
   * \brief The list option
   */
  IMS_Data::ProcessOp_ptr mop;
  /**
   * \brief The session
   */
  UserServer msession;
  /**
  * \brief An instance of vishnu database
  */
  Database *mdatabase;
  /**
   * \brief The name of the command
   */
  std::string mcommandName;
};

#endif
