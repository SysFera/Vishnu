/**
 * \file MachineProxy.cpp
 * \brief This file contains the VISHNU MachineProxy class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#include "UMSVishnuException.hpp"
#include "MachineProxy.hpp"
#include "utilsClient.hpp"

/**
 * \fn MachineProxy(const UMS_Data::Machine& machine,
 *                       const SessionProxy& session)
 * \param machine The object which encapsulates the information of the machine
 * \param session The object which encapsulates the session information (ex: identifier of the session)
 * \brief Constructor, raises an exception on error
 */
MachineProxy::MachineProxy(const UMS_Data::Machine& machine, const SessionProxy& session):
  mmachine(machine), msessionProxy(session)
{
}

/**
 * \brief Function to add a new machine
 * \fn  int add()
 * \return raises an exception on error
 */
int MachineProxy::add()
{

  diet_profile_t* addProfile = NULL;
  std::string sessionKey;
  std::string machineToString;
  std::string machineInString;
  std::string errorInfo;
  std::string msg = "call of function diet_string_set is rejected ";

  addProfile = diet_profile_alloc("machineCreate", 1, 1, 3);
  sessionKey = msessionProxy.getSessionKey();

  ::ecorecpp::serializer::serializer _ser;
  //To serialize the mmachine object in to machineToString
  machineToString =  _ser.serialize_str(const_cast<UMS_Data::Machine_ptr>(&mmachine));

  std::string sshKeyFilePath = mmachine.getSshPublicKey();
  if(sshKeyFilePath.find("\"")!=std::string::npos) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM, " The machine SshPublicKey contains special character double quote \"");
  }

  //IN Parameters
  if(diet_string_set(diet_parameter(addProfile,0), const_cast<char*>(sessionKey.c_str()))) {
    msg += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msg);
  }
  if(diet_string_set(diet_parameter(addProfile,1), const_cast<char*>(machineToString.c_str()))) {
    msg += "with machineToString parameter "+machineToString;
    raiseDietMsgException(msg);
  }

  //OUT Parameters
  diet_string_set(diet_parameter(addProfile,2), NULL);
  diet_string_set(diet_parameter(addProfile,3), NULL);

  if(!diet_call(addProfile)) {
    if(diet_string_get(diet_parameter(addProfile,2), machineInString)){
      msg += "by receiving Machine serialized  message";
      raiseDietMsgException(msg);
    }
    if(diet_string_get(diet_parameter(addProfile,3), errorInfo)){
      msg += "by receiving errorInfo message";
      raiseDietMsgException(msg);
    }
  }
  else {
    raiseDietMsgException("DIET call failure");
  }

  /*To raise a vishnu exception if the receiving message is not empty*/
  raiseExceptionIfNotEmptyMsg(errorInfo);

  UMS_Data::Machine_ptr machine_ptr;

  //To parse machine object serialized
  parseEmfObject(machineInString, machine_ptr, "Error by receiving Machine object serialized");

  mmachine = *machine_ptr;
  delete machine_ptr;

  diet_profile_free(addProfile);

  return 0;

}

/**
 * \brief Function to update machine description
 * \fn  int update()
 * \return raises an exception on error
 */
int MachineProxy::update()
{
  diet_profile_t* updateProfile = NULL;
  std::string sessionKey;
  std::string machineToString;
  std::string errorInfo;
  std::string msg = "call of function diet_string_set is rejected ";

  updateProfile = diet_profile_alloc("machineUpdate", 1, 1, 2);
  sessionKey = msessionProxy.getSessionKey();

  ::ecorecpp::serializer::serializer _ser;
  //To serialize the mmachine object in to machineToString
  machineToString =  _ser.serialize_str(const_cast<UMS_Data::Machine_ptr>(&mmachine));

  std::string sshKeyFilePath = mmachine.getSshPublicKey();
  if(sshKeyFilePath.find("\"")!=std::string::npos) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM, " The machine SshPublicKey contains special character double quote \"");
  }

  //IN Parameters
  if(diet_string_set(diet_parameter(updateProfile,0), const_cast<char*>(sessionKey.c_str()))) {
    msg += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msg);
  }
  if(diet_string_set(diet_parameter(updateProfile,1), const_cast<char*>(machineToString.c_str()))) {
    msg += "with machineToString parameter "+machineToString;
    raiseDietMsgException(msg);
  }

  //OUT Parameters
  diet_string_set(diet_parameter(updateProfile,2), NULL);

  if(!diet_call(updateProfile)) {
    if(diet_string_get(diet_parameter(updateProfile,2), errorInfo)){
      msg += "by receiving errorInfo message";
      raiseDietMsgException(msg);
    }
  }
  else {
    raiseDietMsgException("DIET call failure");
  }

  /*To raise a vishnu exception if the receiving message is not empty*/
  raiseExceptionIfNotEmptyMsg(errorInfo);

  diet_profile_free(updateProfile);

  return 0;
}

/**
 * \brief Function to remove a machine
 * \fn  int deleteMachine()
 * \return raises an exception on error
 */
int MachineProxy::deleteMachine()
{
  diet_profile_t* deleteProfile = NULL;
  std::string sessionKey;
  std::string machineId;
  std::string errorInfo;
  std::string msg = "call of function diet_string_set is rejected ";

  deleteProfile = diet_profile_alloc("machineDelete", 1, 1, 2);
  sessionKey = msessionProxy.getSessionKey();
  machineId = mmachine.getMachineId();

  //IN Parameters
  if(diet_string_set(diet_parameter(deleteProfile,0), const_cast<char*>(sessionKey.c_str()))) {
    msg += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msg);
  }
  if(diet_string_set(diet_parameter(deleteProfile,1), const_cast<char*>(machineId.c_str()))) {
    msg += "with machineId parameter "+machineId;
    raiseDietMsgException(msg);
  }

  //OUT Parameters
  diet_string_set(diet_parameter(deleteProfile,2), NULL);

  if(!diet_call(deleteProfile)) {
    if(diet_string_get(diet_parameter(deleteProfile,2), errorInfo)){
      msg += "by receiving errorInfo message";
      raiseDietMsgException(msg);
    }
  }
  else {
    raiseDietMsgException("DIET call failure");
  }

  /*To raise a vishnu exception if the receiving message is not empty*/
  raiseExceptionIfNotEmptyMsg(errorInfo);

  diet_profile_free(deleteProfile);

  return 0;
}

/**
 * \brief Function get SessionProxy object which contains the VISHNU session identifier
 * \fn SessionProxy getSessionProxy()
 * \return a SessionProy object which contains the VISHNU session information
 * \return raises an exception on error
 */
SessionProxy MachineProxy::getSessionProxy()
{
  return msessionProxy;
}

/**
 * \brief Function get machine information
 * \fn  UMS_Data::Machine getData()
 * \return Machine object encapsulates the information of the machine
 * \return raises an exception on error
 */
UMS_Data::Machine MachineProxy::getData()
{
  return mmachine;
}

/**
 * \fn ~MachineProxy()
 * \brief Destructor, raises an exception on error
 */
MachineProxy::~MachineProxy()
{
}
