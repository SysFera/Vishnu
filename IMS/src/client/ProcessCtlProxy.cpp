#include <iostream>
#include <string>
#include "ProcessCtlProxy.hpp"
#include "utilClient.hpp"
#include "utilVishnu.hpp"
#include "TMS_Data.hpp"
#include "api_fms.hpp"

using namespace vishnu;

/**
* \param session The object which encapsulates the session information
* \param machineId The id of the machine
* \brief Constructor
*/
ProcessCtlProxy::ProcessCtlProxy( const SessionProxy& session):msessionProxy(session) {
}


/**
* \param session The object which encapsulates the session information
* \param machineId The id of the machine
* \brief Constructor
*/
ProcessCtlProxy::ProcessCtlProxy( const SessionProxy& session,
			  const std::string& machineId)
  :msessionProxy(session), mmachineId(machineId) {
}


/**
* \brief Function to to restart a SeD or a MA
* \param options the options for the restart
* \return raises an exception on error
*/
int
ProcessCtlProxy::restart(const IMS_Data::SupervisorOp& options) {

  diet_profile_t* restartProfile = NULL;
  std::string sessionKey;
  std::string errorInfo;

  std::string serviceName = "int_restart@"+mmachineId;

  restartProfile = diet_profile_alloc(serviceName.c_str(), 2, 2, 3);
  sessionKey = msessionProxy.getSessionKey();

  std::string msgErrorDiet = "call of function diet_string_set is rejected ";
  //IN Parameters
  if (diet_string_set(diet_parameter(restartProfile,0), sessionKey.c_str(), DIET_VOLATILE)) {
    msgErrorDiet += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msgErrorDiet);
  }

  if (diet_string_set(diet_parameter(restartProfile,1), mmachineId.c_str(), DIET_VOLATILE)) {
    msgErrorDiet += "with machineId parameter "+mmachineId;
    raiseDietMsgException(msgErrorDiet);
  }

  ::ecorecpp::serializer::serializer _ser;
  //To serialize the options object in to optionsInString
  std::string restartOpToString =  _ser.serialize_str(const_cast<IMS_Data::SupervisorOp_ptr>(&options));

  if (diet_string_set(diet_parameter(restartProfile,2), restartOpToString.c_str(),  DIET_VOLATILE)) {
    msgErrorDiet += "with SystemInfo parameter ";
    raiseDietMsgException(msgErrorDiet);
  }

  //OUT Parameters
  diet_string_set(diet_parameter(restartProfile,3), NULL, DIET_VOLATILE);

  if(!diet_call(restartProfile)) {
    if(diet_string_get(diet_parameter(restartProfile,3), errorInfo)){
      msgErrorDiet += " by receiving errorInfo message";
      raiseDietMsgException(msgErrorDiet);
    }
  }
  else {
    raiseDietMsgException("DIET call failure");
  }

  /*To raise a vishnu exception if the receiving message is not empty*/
  raiseExceptionIfNotEmptyMsg(errorInfo);

  diet_profile_free(restartProfile);
  return 0;
}

/**
* \brief Function to get the refresh period
* \param process The data structure containing information about the process to stop
* \return raises an exception on error
*/
int
ProcessCtlProxy::stop(const IMS_Data::SupervisorOp& op) {

   diet_profile_t* stopProfile = NULL;
  std::string sessionKey;
  std::string errorInfo;

  std::string serviceName = "int_stop@"+mmachineId;

  stopProfile = diet_profile_alloc(serviceName.c_str(), 2, 2, 3);
  sessionKey = msessionProxy.getSessionKey();

  std::string msgErrorDiet = "call of function diet_string_set is rejected ";
  //IN Parameters
  if (diet_string_set(diet_parameter(stopProfile,0), sessionKey.c_str(), DIET_VOLATILE)) {
    msgErrorDiet += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msgErrorDiet);
  }

  ::ecorecpp::serializer::serializer _ser2;
  std::string opToString =  _ser2.serialize_str(const_cast<IMS_Data::SupervisorOp_ptr>(&op));

  if (diet_string_set(diet_parameter(stopProfile,1), mmachineId.c_str(),  DIET_VOLATILE)) {
    msgErrorDiet += "with process parameter ";
    raiseDietMsgException(msgErrorDiet);
  }

  if (diet_string_set(diet_parameter(stopProfile,2), opToString.c_str(),  DIET_VOLATILE)) {
    msgErrorDiet += "with option stop parameter ";
    raiseDietMsgException(msgErrorDiet);
  }

  //OUT Parameters
  diet_string_set(diet_parameter(stopProfile,3), NULL, DIET_VOLATILE);

  if(!diet_call(stopProfile)) {
    if(diet_string_get(diet_parameter(stopProfile,3), errorInfo)){
      msgErrorDiet += " by receiving errorInfo message";
      raiseDietMsgException(msgErrorDiet);
    }
  }
  else {
    raiseDietMsgException("DIET call failure");
  }

  /*To raise a vishnu exception if the receiving message is not empty*/
  raiseExceptionIfNotEmptyMsg(errorInfo);

  diet_profile_free(stopProfile);

  return 0;
}

/**
* \brief Function to get the refresh period
* \param loadShedType the type of the load shedding mode (SOFT or HARD)
* \return raises an exception on error
*/
int
ProcessCtlProxy::loadShed(IMS_Data::LoadShedType loadShedType) {

  // Cancelling FMS transfer
  try {
    // If no FMS sed, catching exception and do nothing
  cancelFMS();
  } catch (UserException& e) {
    //    throw (e);
  } catch (SystemException& e) {
    //    throw (e);
  }
  // Cancelling TMS jobs
  try {
    // If no TMS sed, catching exception and do nothing
    cancelTMS();
  } catch (VishnuException& e) {
  }

  // If hard load shedding
  if (loadShedType == 1) {
    diet_profile_t* loadShedProfile = NULL;
    std::string sessionKey;
    std::string errorInfo;

     std::string serviceName = "int_loadShed@"+mmachineId;
    loadShedProfile = diet_profile_alloc(serviceName.c_str(), 2, 2, 3);
    sessionKey = msessionProxy.getSessionKey();

    std::string msgErrorDiet = "call of function diet_string_set is rejected ";
    //IN Parameters
    if (diet_string_set(diet_parameter(loadShedProfile,0), sessionKey.c_str(), DIET_VOLATILE)) {
      msgErrorDiet += "with sessionKey parameter "+sessionKey;
      raiseDietMsgException(msgErrorDiet);
    }

    if (diet_string_set(diet_parameter(loadShedProfile,1), mmachineId.c_str(), DIET_VOLATILE)) {
      msgErrorDiet += "with machineId parameter "+mmachineId;
      raiseDietMsgException(msgErrorDiet);
    }

    if (diet_string_set(diet_parameter(loadShedProfile,2), convertToString(loadShedType).c_str(), DIET_VOLATILE)) {
      msgErrorDiet += "with SystemInfo parameter ";
      raiseDietMsgException(msgErrorDiet);
    }

    //OUT Parameters
    diet_string_set(diet_parameter(loadShedProfile,3), NULL, DIET_VOLATILE);

    if(!diet_call(loadShedProfile)) {
      if(diet_string_get(diet_parameter(loadShedProfile,3), errorInfo)){
	msgErrorDiet += " by receiving errorInfo message";
	raiseDietMsgException(msgErrorDiet);
      }
    }
    else {
      raiseDietMsgException("DIET call failure");
    }

    /*To raise a vishnu exception if the receiving message is not empty*/
    raiseExceptionIfNotEmptyMsg(errorInfo);

    diet_profile_free(loadShedProfile);
  }
  return 0;
}

/**
* \brief Destructor
*/
ProcessCtlProxy::~ProcessCtlProxy() {
}

void
ProcessCtlProxy::cancelFMS() {
#ifdef COMPILE_FMS
  FMS_Data::StopTransferOptions op = FMS_Data::StopTransferOptions();
  op.setFromMachineId(mmachineId);
  op.setTransferId("all");
  op.setUserId("all");

  stopFileTransfer(msessionProxy.getSessionKey(), op);
#endif
}

void
ProcessCtlProxy::cancelTMS() {
#ifdef COMPILE_TMS
  diet_profile_t* cancelTMSProfile = NULL;
  std::string sessionKey;
  std::string errorInfo;
  std::string serviceName = "jobCancel_";
  TMS_Data::Job job;
  job.setJobId("all");

  serviceName.append(mmachineId);

  cancelTMSProfile = diet_profile_alloc(serviceName.c_str(), 2, 2, 3);
  sessionKey = msessionProxy.getSessionKey();

  std::string msgErrorDiet = "call of function diet_string_set is rejected ";
  //IN Parameters
  if (diet_string_set(diet_parameter(cancelTMSProfile,0), sessionKey.c_str(), DIET_VOLATILE)) {
    msgErrorDiet += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msgErrorDiet);
  }

  if (diet_string_set(diet_parameter(cancelTMSProfile,1), mmachineId.c_str(), DIET_VOLATILE)) {
    msgErrorDiet += "with machineId parameter "+mmachineId;
    raiseDietMsgException(msgErrorDiet);
  }

  ::ecorecpp::serializer::serializer _ser;
  //To serialize the job object in to optionsInString
  std::string jobToString =  _ser.serialize_str(const_cast<TMS_Data::Job_ptr>(&job));

  if (diet_string_set(diet_parameter(cancelTMSProfile,2), jobToString.c_str(), DIET_VOLATILE)) {
    msgErrorDiet += "with jobInString parameter "+std::string(jobToString);
    raiseDietMsgException(msgErrorDiet);
  }

  //OUT Parameters
  diet_string_set(diet_parameter(cancelTMSProfile,3), NULL, DIET_VOLATILE);

  if(!diet_call(cancelTMSProfile)) {
    if(diet_string_get(diet_parameter(cancelTMSProfile,3), errorInfo)){
      msgErrorDiet += " by receiving errorInfo message";
      raiseDietMsgException(msgErrorDiet);
    }
  }
  else {
    raiseDietMsgException("DIET call failure");
  }

  /*To raise a vishnu exception if the receiving message is not empty*/
  raiseExceptionIfNotEmptyMsg(errorInfo);

  diet_profile_free(cancelTMSProfile);
#endif
}
