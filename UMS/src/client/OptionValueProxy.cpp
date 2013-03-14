/**
 * \file OptionValueProxy.cpp
 * \brief This file contains the VISHNU OptionValueProxy class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#include "OptionValueProxy.hpp"

#include <string>                       // for allocator, string, etc
#include "DIET_client.h"                // for diet_string_set, etc
#include "ecorecpp/serializer/serializer.hpp"  // for serializer
#include "utilClient.hpp"               // for raiseDietMsgException, etc
#include "UMSServices.hpp"

/**
 * \fn OptionValueProxy(const UMS_Data::OptionValue& optionValue,
 *                      const SessionProxy& session)
 * \param optionValue The object which encapsulates the information of the option
 * \param session The object which encapsulates the session information (ex: identifier of the session)
 * \brief Constructor, raises an exception on error
 */
OptionValueProxy::OptionValueProxy(const UMS_Data::OptionValue& optionValue, const SessionProxy& session):
  moptionValue(optionValue), msessionProxy(session)
{
}

/**
 * \brief Function to combine configureOption() and configureDefaultOption() into one function
 * \fn  int setOptionValue(bool defaultValue=true);
 * \param defaultValue to select the call of configureOption() or configureOption() function
 * \return raises an exception on error
 */
int
OptionValueProxy::setOptionValue(bool defaultValue) {
  diet_profile_t* profile = NULL;
  std::string sessionKey;
  std::string optionValueToString;
  std::string errorInfo;
  std::string msg = "call of function diet_string_set is rejected ";

  if(defaultValue) {
    profile = diet_profile_alloc(SERVICES_UMS[OPTIONVALUESETDEFAULT], 1, 1, 2);
  }
  else {
    profile = diet_profile_alloc(SERVICES_UMS[OPTIONVALUESET], 1, 1, 2);
  }
  sessionKey = msessionProxy.getSessionKey();

  ::ecorecpp::serializer::serializer _ser;
  //To serialize the moptionValue object in to optionValueToString
  optionValueToString =  _ser.serialize_str(const_cast<UMS_Data::OptionValue_ptr>(&moptionValue));

  //IN Parameters
  if (diet_string_set(profile, 0, sessionKey)) {
    msg += "with sessionKey parameter "+sessionKey;
    raiseDietMsgException(msg);
  }
  if (diet_string_set(profile, 1, optionValueToString)) {
    msg += "with optionValueToString parameter "+optionValueToString;
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
 * \brief Function to configure an option of the user
 * \fn  int configureOption()
 * \return raises an exception on error
 */
int
OptionValueProxy::configureOption() {
  return setOptionValue(false);
}

/**
 * \brief Function to configure a default option value
 * \fn  int configureDefaultOption()
 * \return raises an exception on error
 */
int
OptionValueProxy::configureDefaultOption() {
  return setOptionValue();
}

/**
 * \brief Function get option information
 * \fn  UMS_Data::OptionValue getData()
 * \return OptionValue object encapsulates the information of the machine
 * \return raises an exception on error
 */
UMS_Data::OptionValue
OptionValueProxy::getData() {
  return moptionValue;
}

/**
 * \brief Function get SessionProxy object which contains the VISHNU session identifier
 * \fn SessionProxy getSessionProxy()
 * \return a SessionProy object which contains the VISHNU session information
 * \return raises an exception on error
 */
SessionProxy
OptionValueProxy::getSessionProxy() {
  return msessionProxy;
}

/**
 * \fn ~OptionValueProxy()
 * \brief Destructor, raises an exception on error
 */
OptionValueProxy::~OptionValueProxy()
{
}
