/**
 * \file configurationProxy.cpp
 * \brief This file contains the VISHNU configurationProxy class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#include "ConfigurationProxy.hpp"

#include <fstream>                      // for ofstream, basic_ostream

#include "Configuration.hpp"            // for Configuration
#include "DIET_client.h"                // for diet_string_set, etc
#include "ecorecpp/serializer/serializer.hpp"  // for serializer
#include "utilClient.hpp"               // for raiseDietMsgException, etc
#include "utilVishnu.hpp"
#include "UMSServices.hpp"


/**
 * \fn ConfigurationProxy(const std::string& filePath,
 *                        const SessionProxy& session)
 * \param filePath The file containing the configuration (serialized)
 * \param session The object which encapsulates the session information (ex: identifier of the session)
 * \brief Constructor, raises an exception on error
 */
ConfigurationProxy::ConfigurationProxy(const std::string& filePath, const SessionProxy& session):
  msessionProxy(session), mfilePath(filePath)
{
  mconfiguration = NULL;
}

/**
 * \fn ConfigurationProxy(UMS_Data::Configuration* config,
 *                        const SessionProxy& session)
 * \param config The object which encapsulates the configuration description
 * \param session The object which encapsulates the session information (ex: identifier of the session)
 * \brief Constructor, raises an exception on error
 */
ConfigurationProxy::ConfigurationProxy(UMS_Data::Configuration* config, const SessionProxy& session):
  mconfiguration(config), msessionProxy(session)
{
}

/**
 * \brief Function to save the configuration of VISHNU
 * \fn  int save()
 * \return raises an exception on error
 */
int
ConfigurationProxy::save() {
  diet_profile_t* profile = NULL;
  std::string sessionKey;
  std::string errorInfo;
  std::string configurationInString;
  std::string msg = "call of function diet_string_set is rejected ";


  profile = diet_profile_alloc(SERVICES_UMS[CONFIGURATIONSAVE], 0, 0, 2);
  //To get the encrypted identifier of the session generated by VISHNU
  sessionKey = msessionProxy.getSessionKey();

  //IN Parameters
  if (diet_string_set(profile, 0, sessionKey)) {
    msg += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msg);
  }

  //OUT Parameters
  diet_string_set(profile,1);
  diet_string_set(profile,2);

  if(!diet_call(profile)) {
    if(diet_string_get(profile,1, configurationInString)){
      msg += "by receiving configurationInString message";
      raiseDietMsgException(msg);
    }
    if(diet_string_get(profile,2, errorInfo)){
      msg += "by receiving errorInfo message";
      raiseDietMsgException(msg);
    }
  }
  else {
    raiseDietMsgException("VISHNU call failure");
  }

  /*To raise a vishnu exception if the receiving message is not empty*/
  raiseExceptionIfNotEmptyMsg(errorInfo);

  //To parse the Configuration object serialized
  parseEmfObject(configurationInString, mconfiguration, "Error by receiving Configuration object serialized");

  mconfiguration->setFilePath(mfilePath);

  //To serialize the mconfiguration
  ::ecorecpp::serializer::serializer _ser;
  std::string configurationToSave =  _ser.serialize_str(mconfiguration);

  //To save the configuration in the file
  std::ofstream ofile(mfilePath.c_str());
  ofile << configurationToSave;
  ofile.close();

  diet_profile_free(profile);

  return 0;
}

/**
 * \brief Function to combine restoreFromFile() and restoreFromData() into one function
 * \fn  int restore(bool fromFile=true)
 * \param fromFile To select the call of restoreFromFile or restoreFromData function
 * \return raises an exception on error
 */
int
ConfigurationProxy::restore(bool fromFile) {
  diet_profile_t* profile = NULL;
  std::string sessionKey;
  std::string errorInfo;
  std::string msg = "call of function diet_string_set is rejected ";

  std::string configurationInString = "";
  if(fromFile) { // To get the content of the mfile
    configurationInString = vishnu::get_file_content(mfilePath);
  }
  else { //To serialize the mconfiguration object in to configurationInString
    ::ecorecpp::serializer::serializer _ser;
    configurationInString =  _ser.serialize_str(mconfiguration);
  }
  //To intialize the service description
  profile = diet_profile_alloc(SERVICES_UMS[CONFIGURATIONRESTORE], 1, 1, 2);
  //To get the encrypted identifier of the session generated by VISHNU
  sessionKey = msessionProxy.getSessionKey();

  //IN Parameters
  if (diet_string_set(profile, 0, sessionKey)) {
    msg += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msg);
  }
  if (diet_string_set(profile, 1, configurationInString)) {
    msg += "with configurationInString parameter " + configurationInString;
    raiseDietMsgException(msg);
  }
  //OUT Parameters
  diet_string_set(profile,2);

  if(!diet_call(profile)) {
    if(diet_string_get(profile,2, errorInfo)){
      msg += "by receiving errorInfo message";
      raiseDietMsgException(msg);
    }
  }
  else {
    raiseDietMsgException("VISHNU call failure");
  }

  /*To raise a vishnu exception if the receiving message is not empty*/
  raiseExceptionIfNotEmptyMsg(errorInfo);

  diet_profile_free(profile);

  return 0;
}

/**
 * \brief Function to restore the configuration of VISHNU from a file
 * \fn  int restoreFromFile()
 * \return raises an exception on error
 */
int
ConfigurationProxy::restoreFromFile() {
  return restore();
}

/**
 * \brief Function to restore the configuration of VISHNU from an object (Data)
 * \fn  int restoreFromFile()
 * \return raises an exception on error
 */
int
ConfigurationProxy::restoreFromData() {
  return restore(false);
}

/**
 * \brief Function get the saved configuration of VISHNU
 * \fn  UMS_Data::Configuration* getData()
 * \return saved configuration
 * \return raises an exception on error
 */
UMS_Data::Configuration*
ConfigurationProxy::getData() {
  return mconfiguration;
}

/**
 * \brief Function get SessionProxy object which contains the VISHNU session identifier
 * \fn SessionProxy getSessionProxy()
 * \return a SessionProy object which contains the VISHNU session information
 * \return raises an exception on error
 */
SessionProxy
ConfigurationProxy::getSessionProxy() {
  return msessionProxy;
}

/**
 * \fn ~ConfigurationProxy()
 * \brief Destructor, raises an exception on error
 */
ConfigurationProxy::~ConfigurationProxy() {
}
