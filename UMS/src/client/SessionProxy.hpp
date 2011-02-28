/**
 * \file SessionProxy.hpp
 * \brief This file contains the VISHNU SessionProxy class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#ifndef _SESSION_PROXY_H_
#define _SESSION_PROXY_H_

#include <string>
#include <iostream>

//EMF
#include <ecore.hpp> // Ecore metamodel
#include <ecorecpp.hpp> // EMF4CPP utils
#include "UMS_Data.hpp"

#include "DIET_client.h"

#include "UserProxy.hpp"
#include "Session.hpp"
#include "ConnectOptions.hpp"

class UserProxy;
const int HOST_NAME_MAX_SIZE = 256;

/**
 * \class SessionProxy 
 * \brief SessionProxy class implementation 
 */
class SessionProxy
{

public:
  
 /**
  * \fn SessionProxy()
  * \brief Constructor, raises an exception on error
  */ 
  SessionProxy();
 /**
  * \fn explicit SessionProxy(const std::string& sessionKey)
  * \param sessionKey The encrypted identifier of the session generated by VISHNU
  * \brief Constructor, raises an exception on error
  */
  explicit SessionProxy(const std::string& sessionKey);
 /**
  * \fn explicit SessionProxy(const UMS_Data::Session& session)
  * \param session The object which encapsulates the session information (ex: identifier of the session) 
  * \brief Constructor, raises an exception on error
  */
  explicit SessionProxy(const UMS_Data::Session& session);

  /**
   * \brief Function to open a session 
   * \fn  int connect(const UserProxy& user, const UMS_Data::ConnectOptions& options)
   * \param user The object which encapsulates the user information (ex: userId and password) 
   * \param options the object which encapsulate the options available for the connect method. It allows the user 
   *  to choose the way for way for closing the session automatically on TIMEOUT or on DISCONNECT and the
   *  possibility for an admin to open a session as she was a specific user
   * \return raises an exception on error
   */ 
  int connect(const UserProxy& user, const UMS_Data::ConnectOptions& options);
  /**
   * \brief Function to reconnect to an opened session 
   * \fn  int reconnect(const UserProxy& user) 
   * \param user The object which encapsulates the user information (ex: userId and password) 
   * \return raises an exception on error
   */
  int reconnect(const UserProxy& user);
   /**
   * \brief Function close an opened session 
   * \fn  int close() 
   * \return raises an exception on error
   */
  int close();
  /**
   * \brief Function get the encrypted identifier of the session generated by VISHNU
   * \fn std::string getSessionKey() const
   * \return the encrypted identifier of the session generated by VISHNU 
   * \return raises an exception on error
   */
  std::string getSessionKey() const;
  /**
   * \brief Function get machine information 
   * \fn  UMS_Data::Session getData()
   * \return Session object encapsulates the information of the session 
   * \return raises an exception on error
   */
  UMS_Data::Session getData() const;
  /**
   * \fn ~SessionProxy()
   * \brief Destructor, raises an exception on error
   */ 
  ~SessionProxy();

private:

  /**
   * \brief Function to combine connect() and reconnect() into one function 
   * \fn  _connect(const UserProxy& user, 
   *               bool connect = false, 
   *               const UMS_Data::ConnectOptions& options=UMS_Data::ConnectOptions())
   * \param user The object which encapsulates the user information (ex: userId and password) 
   * \param connect to select the call of connect or reconnect function 
   * \param options the object which encapsulate the options available for the connect method. It allows the user 
   *  to choose the way for way for closing the session automatically on TIMEOUT or on DISCONNECT and the
   *  possibility for an admin to open a session as she was a specific user
   * \return raises an exception on error
   */       
  int _connect(const UserProxy& user, bool connect = false, const UMS_Data::ConnectOptions& options=UMS_Data::ConnectOptions());

   /////////////////////////////////
  // Attributes
  /////////////////////////////////
     
  /**
  * \brief The SessionProxy object containing the encrypted identifier of the session
  *  generated by VISHNU
  */ 
  UMS_Data::Session msession;
  /**
  * \brief The encrypted identifier of the session generated by VISHNU
  */
  std::string msessionKey;
};
#endif
