/**
 * \file ServerTMS.hpp
 * \brief This file presents the implementation of the TMS server.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date April
*/

#ifndef _TMS_SERVER_H_
#define _TMS_SERVER_H_

#include <string>

#include "DIET_server.h"
#include "DbConfiguration.hpp"
#include "utilVishnu.hpp"
#include "TMSMapper.hpp"
#include "MapperRegistry.hpp"

class Database;

/**
 *  * \brief Number of service in TMS
 *   */
#define NB_SRV 8 

static const char* SERVICES[NB_SRV] = {
  "jobSubmit_",
  "jobCancel_",
  "jobInfo_",
  "getListOfJobs_",
  "getJobsProgression_",
  "getListOfQueues_",
  "jobOutputGetResult_",
  "jobOutputGetCompletedJobs_"
};

/**
 * \class ServerTMS
 * \brief This class describes the g server
 */
class ServerTMS {
public :

  /**
   * \brief To get the unique instance of the server
   */
  static ServerTMS*  getInstance();
  /**
   * \brief To get the unique instance of the database
   */
  Database* getDatabaseVishnu();

  /**
   * \brief to get the VishnuId
   * \return the path of the configuration file
   */
  int
  getVishnuId() const;
  /**
  * \brief To get the batchType
  * \return the type of the underlying batch scheduler
  */
  BatchType
  getBatchType();

 /**
  * \brief To get the machine id of the TMS server
  * \return the machine id
  */
  std::string
  getMachineId();

  /**
   * \brief To get the slave binary directory
   * \return path to the binary tmsSlave
   */
  std::string
  getSlaveDirectory();

   /**
   * \brief To initialize the TMS Server class
   * \param vishnuId The identifier of the vishnu instance
   * \param dbConfig  The configuration of the database
   * \param machineId the id of the machine
   * \param batchType the type of batch scheduler
   * \param slaveBinDir  the directory that contains the slave binary
   * \return raises an exception on error
   */
  int
  init(int vishnuId,
       DbConfiguration dbConfig,
       std::string machineId,
       BatchType batchType,
       std::string slaveBinDir);

  /**
   * \brief Destructor, raises an exception on error
   */
  ~ServerTMS();

private :

  /**
   * \brief Constructor, private because class is singleton
   */
  ServerTMS();

  /**
   * \brief operator=
   */
  ServerTMS& operator=(const ServerTMS&);

  /////////////////////////////////
  // Attributes
  /////////////////////////////////
  /**
   * \brief The singleton reference
   */
  static ServerTMS *minstance;
  /**
   * \brief Instance of TMSMapper
   */
  static TMSMapper *mmapper;
  /**
   * \brief The vishnu id
   */
  int mvishnuId;
  /**
  * \brief represents The batch Type
  */
  BatchType mbatchType;
  /**
  * \brief represents The batch Type
  */
  std::string mmachineId;
  /**
  * \brief Structure representing a profile description
  */
  diet_profile_desc_t* mprofile;
  /**
  * \brief Instance of Database
  */
  Database *mdatabaseVishnu;
  /**
   * \brief Directory containing the slave binary
   */
  std::string mslaveBinDir;
};
#endif // SERVER
