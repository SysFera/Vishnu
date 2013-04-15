/**
 * \file ListUsersServer.hpp
 * \brief This file contains the VISHNU QueryServer class.
 * \author Daouda Traore (daouda.traore@sysfera.com) and
 *   Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
 * \date February 2011
 */
#ifndef _QUERY_SERVER_H_
#define _QUERY_SERVER_H_

#include <string>
#include <vector>
#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"

#include "ListUsersServer.hpp"
#include "DbFactory.hpp"


/**
 * \brief Constructor, raises an exception on error
 * \param session The object which encapsulates the session information (ex: identifier of the session)
 */
ListUsersServer::ListUsersServer(const SessionServer& session):
msessionServer(session)
{
   mlistUsers = NULL;
   DbFactory factory;
   mdatabaseVishnu = factory.getDatabaseInstance();
}

/**
 * \brief Constructor, raises an exception on error
 * \param option The ListUsersServer option
 * \param session The object which encapsulates the session information (ex: identifier of the session)
 */
ListUsersServer::ListUsersServer(const UMS_Data::ListUsersOptions_ptr& option, const SessionServer& session):
moption(option), msessionServer(session)
{
   mlistUsers = NULL;
   DbFactory factory;
   mdatabaseVishnu = factory.getDatabaseInstance();
}

/**
 * \brief Function to treat the ListUsersServer options
 * \param userServer the object which encapsulates user information
 * \param optionsListUsersServer option
 * \param sqlRequest the sql data base request
 * \return raises an exception on error
 */
void
ListUsersServer::processOptions(UserServer userServer, const UMS_Data::ListUsersOptions_ptr& options, std::string& sqlRequest)
{
  if(!userServer.isAdmin()) {
    UMSVishnuException e (ERRCODE_NO_ADMIN);
    throw e;
  }
  std::string  userId = options->getUserId();
  if(userId.size()!=0) {
    sqlRequest.append(" and userid=");
    sqlRequest.append("'"+userId+"'");
    boost::scoped_ptr<DatabaseResult> ListofUsers (mdatabaseVishnu->getResult(sqlRequest.c_str()));
    if(ListofUsers->getNbTuples()==0) {
      UMSVishnuException e(ERRCODE_UNKNOWN_USERID);
      throw e ;
    }
  }
}

/**
 * \brief Function to list machines information
 * \return The pointer to the UMS_Data::ListUsers containing users information
 * \return raises an exception on error
 */
ListUsers*
ListUsersServer::list()
{
  std::string sqlListofUsers = "SELECT userid, pwd, firstname, lastname, privilege, email, status from users "
    "where not userid='"+ ROOTUSERNAME +"' and status !=" + vishnu::convertToString(DELETED_STATUS);

  std::vector<std::string>::iterator ii;
  std::vector<std::string> results;
  UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
  mlistUsers = ecoreFactory->createListUsers();

  //Creation of the object user
  UserServer userServer = UserServer(msessionServer);
  userServer.init();
  //if the user exists
  if (userServer.exist()) {

    processOptions(userServer, moption, sqlListofUsers);
    sqlListofUsers.append(" order by userid");
    //To get the list of users from the database
    boost::scoped_ptr<DatabaseResult> ListofUsers (mdatabaseVishnu->getResult(sqlListofUsers.c_str()));
    if (ListofUsers->getNbTuples() != 0){
      for (size_t i = 0; i < ListofUsers->getNbTuples(); ++i) {
        results.clear();
        results = ListofUsers->get(i);
        ii = results.begin();
        UMS_Data::User_ptr user = ecoreFactory->createUser();
        user->setUserId(*ii);
        user->setPassword(*(++ii));
        user->setFirstname(*(++ii));
        user->setLastname(*(++ii));
        user->setPrivilege(convertToInt(*(++ii)));
        user->setEmail(*(++ii));
        user->setStatus(convertToInt(*(++ii)));

        mlistUsers->getUsers().push_back(user);
        }
    }
  }
  else {
    UMSVishnuException e (ERRCODE_UNKNOWN_USER);
    throw e;
  }
  return mlistUsers;
}

/**
 * \brief Destructor, raises an exception on error
 */
ListUsersServer::~ListUsersServer()
{
}

#endif
