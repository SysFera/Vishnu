/**
 * \file AuthSystemProxy.cpp
 * \brief This file contains the VISHNU AuthSystemProxy class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#include "UMSVishnuException.hpp"
#include "utilsClient.hpp"
#include "AuthSystemProxy.hpp"

/**
 * \param authSystem The object which encapsulates the user aythentication system
 * \param session The object which encapsulates the session information (ex: identifier of the session)
 * \brief Constructor
 */
AuthSystemProxy::AuthSystemProxy(const UMS_Data::AuthSystem& authSystem, const SessionProxy& session):
  mauthSystem(authSystem), msessionProxy(session)
{
}


/**
 * \brief Function to add an authentication system
 * \return raises an exception on error
 */
int
AuthSystemProxy::add() {
  diet_profile_t* profile = NULL;
  std::string sessionKey;
  std::string authSystemToString;
  std::string authSystemInString;
  std::string errorInfo;
  std::string msg = "call of function diet_string_set is rejected ";

  profile = diet_profile_alloc("authSystemCreate", 1, 1, 3);

  sessionKey = msessionProxy.getSessionKey();

  ::ecorecpp::serializer::serializer _ser;
  //To serialize the mauthSystem object in to authSystemToString
  authSystemToString =  _ser.serialize_str(const_cast<UMS_Data::AuthSystem_ptr>(&mauthSystem));

  //IN Parameters
  if(diet_string_set(profile,0, const_cast<char*>(sessionKey.c_str()))) {
    msg += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msg);
  }
  if(diet_string_set(profile,1, const_cast<char*>(authSystemToString.c_str()))) {
    msg += "with authSystemToString parameter "+authSystemToString;
    raiseDietMsgException(msg);
  }

  //OUT Parameters
  diet_string_set(profile,2);
  diet_string_set(profile,3);

  if(!diet_call(profile)) {

    if(diet_string_get(profile,2, authSystemInString)) {
      msg += "with authSystemInString parameter " + authSystemInString;
      raiseDietMsgException(msg);
    }

    if(diet_string_get(profile,3, errorInfo)){
      msg += "by receiving errorInfo message";
      raiseDietMsgException(msg);
    }
  }
  else {
    raiseDietMsgException("DIET call failure");
  }

  /*To raise a vishnu exception if the receiving message is not empty*/
  raiseExceptionIfNotEmptyMsg(errorInfo);

  UMS_Data::AuthSystem_ptr authSystem_ptr;

  //To parse User object serialized
  parseEmfObject(authSystemInString, authSystem_ptr,
                 "Error by receiving AuthSystem object serialized");

  mauthSystem = *authSystem_ptr;
  delete authSystem_ptr;

  diet_profile_free(profile);

  return 0;
}

/**
 * \brief Function to update an authentication system
 * \return raises an exception on error
 */
int
AuthSystemProxy::update() {
  diet_profile_t* profile = NULL;
  std::string sessionKey;
  std::string authSystemToString;
  std::string errorInfo;
  std::string msg = "call of function diet_string_set is rejected ";

  profile = diet_profile_alloc("authSystemUpdate", 1, 1, 2);

  sessionKey = msessionProxy.getSessionKey();

  ::ecorecpp::serializer::serializer _ser;
  //To serialize the mauthSystem object in to authSystemToString
  authSystemToString =  _ser.serialize_str(const_cast<UMS_Data::AuthSystem_ptr>(&mauthSystem));

  //IN Parameters
  if(diet_string_set(profile,0, const_cast<char*>(sessionKey.c_str()))) {
    msg += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msg);
  }
  if(diet_string_set(profile,1, const_cast<char*>(authSystemToString.c_str()))) {
    msg += "with authSystemToString parameter "+authSystemToString;
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
    raiseDietMsgException("DIET call failure");
  }

  /*To raise a vishnu exception if the receiving message is not empty*/
  raiseExceptionIfNotEmptyMsg(errorInfo);

  diet_profile_free(profile);

  return 0;
}

/**
 * \brief Function to removes an authentication system
 * \return raises an exception on error
 */
int
AuthSystemProxy::deleteAuthSystem()
{
  diet_profile_t* profile = NULL;
  std::string sessionKey;
  std::string sysId;
  std::string errorInfo;
  std::string msg = "call of function diet_string_set is rejected ";

  profile = diet_profile_alloc("authSystemDelete", 1, 1, 2);
  sessionKey = msessionProxy.getSessionKey();
  sysId = mauthSystem.getAuthSystemId();

  //IN Parameters
  if(diet_string_set(profile,0, const_cast<char*>(sessionKey.c_str()))) {
    msg += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msg);
  }
  if(diet_string_set(profile,1, const_cast<char*>(sysId.c_str()))) {
    msg += "with systemId parameter "+sysId;
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
    raiseDietMsgException("DIET call failure");
  }

  /*To raise a vishnu exception if the receiving message is not empty*/
  raiseExceptionIfNotEmptyMsg(errorInfo);

  diet_profile_free(profile);

  return 0;
}

/**
  * \brief Function get AuthSystem information
  * \return the AuthSystem data structure
  */
UMS_Data::AuthSystem
AuthSystemProxy::getData() const {
  return mauthSystem;
}
/**
 * \brief Function get SessionProxy object which contains the VISHNU session identifier
 * \fn SessionProxy getSessionProxy()
 * \return a SessionProy object which contains the VISHNU session information
 * \return raises an exception on error
 */
SessionProxy AuthSystemProxy::getSessionProxy() const
{
  return msessionProxy;
}

/**
 * \brief Destructor, raises an exception on error
 */
AuthSystemProxy::~AuthSystemProxy()
{
}
