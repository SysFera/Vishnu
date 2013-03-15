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
#include "IMSServices.hpp"

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
   * \return the path of the configuration file
   */
  int
  getVishnuId();

  /**
   * \brief To get the path to the sendmail script
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
