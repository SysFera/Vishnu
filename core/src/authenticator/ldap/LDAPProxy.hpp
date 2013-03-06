/**
  * \file LDAPProxy.hpp
  * \brief This file contains the VISHNU LDAPProxy class.
  * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
  * \date March 2011
  */

#ifndef _LDAP_PROXY_H
#define _LDAP_PROXY_H

#include <string>

extern "C" {
#include <ldap.h>
#include <lber.h>
}

static const int desired_version = LDAP_VERSION3;

/**
 * \class LDAPProxy
 * \brief LDAPProxy class implementation
 */
class LDAPProxy {

  public:

  /**
  * \param uri The LDAP uri by of the form host:port
  * \param userName the user name
  * \param authMechanism the authentication method used to bind
  * \param password the password of the user
  * \param serverCtrls A list of LDAP server controls
  * \param clientCtrls A list of LDAP client controls
  * \brief Constructor
  */
  explicit LDAPProxy(const std::string& uri,
                     const std::string& userName,
                     const std::string& authMechanism,
                     const std::string& password,
                     LDAPControl* serverCtrls = NULL,
                     LDAPControl* clientCtrls = NULL
                    );

  /**
  * \brief Function to initialize a connection on a LDAP server
  * \param ldapbase the ldapbase of the ldap system
  * \return If the connection was a succes or an error code
  */
  int
  connectLDAP(const std::string& ldapbase);

  /**
    * \brief Destructor
    */
  ~LDAPProxy();

  private:
/**
 * \brief Function to extract and replace the $username part of the base and store it in res
 * \param base ldap base to extract the $USERNAME substring
 * \param res  the base string with $USERNAME replaced by the login
 */
  void
  extract(const std::string& base, std::string& res);

/**
 * \brief Perform the bind to the ldap object
 * \param fullUserPath The path in the ldap to from the root to the user location
 * \return 0 on success (same as ldap_bind)
 */
  int
  bind(std::string& fullUserPath);
  /////////////////////////////////
  // Attributes
  /////////////////////////////////

  /**
  * \brief An LDAP structure
  */
  LDAP* mld;

  /**
  * \brief The LDAP uri by of the form host:port
  */
   std::string muri;
  /**
  * \brief the distinguished name of the entry used to bind
  */
   std::string muserName;
  /**
  * \brief the authentication method used
  */
   std::string mauthMechanism;
   /**
  * \brief the credential to use for authentication
  */
   std::string mpwd;

/**
 * \brief the server controls
 */
   LDAPControl* mserverCtrls;
/**
 * \brief the client controls
 */
   LDAPControl* mclientCtrls;
};
#endif //_LDAP_PROXY_H
