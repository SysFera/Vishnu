/**
 * \file UMSLDAPAuthenticator.hpp
 * \brief This file defines the UMSLDAP authenticator object
 * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
 * \date 15/12/11
 */

#ifndef _UMSLDAPAUTHENTICATOR_H_
#define _UMSLDAPAUTHENTICATOR_H_

#include "Authenticator.hpp"

/**
 * \class UMSLDAPAuthenticator
 * \brief UMSLDAPAuthenticator
 */
class UMSLDAPAuthenticator : public Authenticator {

public :
  /**
   * \brief Constructor
   */
  UMSLDAPAuthenticator();
  /**
   * \brief Destructor
   */
  ~UMSLDAPAuthenticator();
   /**
  * \brief To authenticate a useer
  * \param user The user to authenticate
  * \return true if the corresponding user is
  * authenticated else false
  */
  bool
  authenticate(UMS_Data::User& user);
};


#endif // _UMSLDAPAUTHENTICATOR_H_
