/**
  * \file LDAPProxy.cpp
  * \brief This file contains the VISHNU LDAPProxy class.
  * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
  * \date March 2011
  */

#include "LDAPProxy.hpp"

#include <string>

#include "SystemException.hpp"
#include "UMSVishnuException.hpp"

using namespace std;


/**
* \param uri The LDAP uri by of the form host:port
* \param userName the distinguished name of the entry used to bind
* \param authMechanism the authentication method used to bind
* \param password the password of the user
* \param serverCtrls A list of LDAP server controls
* \param clientCtrls A list of LDAP client controls
* \brief Constructor
*/
LDAPProxy::LDAPProxy(const string& uri,
                     const string& userName,
                     const string& authMechanism,
                     const string& password,
                     LDAPControl* serverCtrls,
                     LDAPControl* clientCtrls) :
  muri(uri), muserName(userName),
  mauthMechanism(authMechanism), mpwd(password)
{

   mld = NULL;
   mserverCtrls =  serverCtrls;
   mclientCtrls = clientCtrls;
}

/**
* \brief Function to initialize a connection on a LDAP server
*/
int
LDAPProxy::connectLDAP(const string& ldapbase) {
  int ret;
  string fullPath;
  extract(ldapbase, fullPath);

  /* Initialize the LDAP session */
  if ((ldap_initialize(&mld, const_cast<char*>(muri.c_str()))) != LDAP_SUCCESS) {
      throw SystemException(ERRCODE_AUTHENTERR, "LDAP session initialization failed");
  }

  ldap_set_option(mld, LDAP_OPT_PROTOCOL_VERSION, &desired_version);

  ret = bind(fullPath);
  if (ret != LDAP_SUCCESS ) {
    if (ret != LDAP_INVALID_CREDENTIALS ) {
      throw SystemException(ERRCODE_AUTHENTERR, ldap_err2string(ret));
    }
    throw UserException(ERRCODE_UNKNOWN_USER, "The user is unrecognized on LDAP system");
  }
  return 0;
}



int
LDAPProxy::bind(string& fullUserPath) {
  struct berval cred;
  cred.bv_val = const_cast<char*>(mpwd.c_str());
  cred.bv_len = strlen(const_cast<char*>(mpwd.c_str()));

  /* Bind to the server */
  return ldap_sasl_bind_s (
  mld,
  const_cast<char*>(fullUserPath.c_str()),
  LDAP_SASL_SIMPLE,
  &cred,
  &mserverCtrls,
  &mclientCtrls,
  NULL);
}

LDAPProxy::~LDAPProxy() {
  if (mld != NULL) {
    ldap_unbind_ext_s ( mld, NULL, NULL );
  }
}

void
LDAPProxy::extract(const string& base, string& res){
  string p1;
  string p2;
  string templ = "$USERNAME";
  size_t pos = base.find(templ);
  if (pos==string::npos) {
    throw UserException(ERRCODE_INVALID_PARAM, "No $USERNAME string found in the ldapBase. Cannot generate the login for ldap");
  }
  p1 = base.substr(0, pos);
// End of string after $username
  p2 = base.substr(pos+templ.length());
  res = p1 + muserName + p2;
}
