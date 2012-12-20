/**
 * \file ServerIMS.hpp
 * \brief This file presents the implementation of the IMS server.
 * \author Kevin COULOMB (kevin.coulomb@sysfera.com)
 * \date 12/03/2011
 */

#ifndef _SERVERIMS_H_
#define _SERVERIMS_H_

#include <string>
#include "DbConfiguration.hpp"
#include "Database.hpp"
#include "UMSMapper.hpp"
#include "TMSMapper.hpp"
#include "FMSMapper.hpp"
#include "IMSMapper.hpp"
#include "SeD.hpp"

/**
 * \brief Number of service in IMS
 */
#define NB_SRV 19

static const char* SRV[NB_SRV] = {
  "int_exportCommands", // 0
  "int_getMetricCurentValue", // 1
  "int_getMetricHistory", // 2
  "int_getProcesses", // 3
  "int_setSystemInfo", // 4
  "int_setSystemThreshold", // 5
  "int_getSystemThreshold", // 6
  "int_defineUserIdentifier", // 7
  "int_defineJobIdentifier", // 8
  "int_defineTransferIdentifier", // 9
  "int_defineMachineIdentifier", // 10
  "int_loadShed", // 11
  "int_setUpdateFrequency", // 12
  "int_getUpdateFrequency", // 13
  "int_restart", // 14
  "int_stop", // 15
  "int_getSystemInfo", // 16
  "int_defineAuthIdentifier", // 17
  "int_defineWorkIdentifier" // 18
};
/**
 * \class ServerIMS
 * \brief This class describes the IMS server
 */
class ServerIMS : public SeD {
public :

  /**
   * \brief To get the unique instance of the server
   */
  static ServerIMS*  getInstance();

  /**
   * \brief To get the vishnuId
   * \fn int getVishnuId()
   * \return the path of the configuration file
   */
  int
  getVishnuId();

  /**
   * \brief To get the path to the sendmail script
   * \fn std::string getSendmailScriptPath()
   * \return the path of the configuration file
   */
  std::string
  getSendmailScriptPath();

   /**
    * \brief To initialize the IMS server
    * \param vishnuId The password of the root user vishnu_user for the connection with the database
    * \param dbConfig  The configuration of the database
    * \param sendmailScriptPath The path to the script for sending emails
    * \param mid: The machine id
    * \return an error code (0 if success and 1 if an error occurs)
    */
  int
  init(int vishnuId, DbConfiguration dbConfig,
       std::string sendmailScriptPath, std::string mid);

  /**
   * \brief Destructor, raises an exception on error
   * \fn ~ServerIMS()
   */
  ~ServerIMS();

private:
  /**
   * \brief init the function pointer map
   */
  void
  initMap(std::string mid);

  /**
   * \brief Constructor, private because class is singleton
   */
  ServerIMS();

  /////////////////////////////////
  // Attributes
  /////////////////////////////////
  /**
   * \brief The path to the sendmail script
   */
  std::string msendmailScriptPath;
  /**
   * \brief The singleton reference
   */
  static ServerIMS *minstance;
  /**
   * \brief The vishnu id
   */
  int mvishnuId;
  /**
   * \brief Instance of Database
   */
  static Database *mdatabaseVishnu;
  /**
   * \brief Instance of UMSMapper
   */
  static UMSMapper *mmapperUMS;
  /**
   * \brief Instance of UMSMapper
   */
  static TMSMapper *mmapperTMS;
  /**
   * \brief Instance of UMSMapper
   */
  static FMSMapper *mmapperFMS;
  /**
   * \brief Instance of UMSMapper
   */
  static IMSMapper *mmapperIMS;
};
#endif // SERVERIMS
