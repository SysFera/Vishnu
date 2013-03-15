/**
* \file MonitorUMS.cpp
* \brief This file presents the implementation of the UMS Monitor
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2001
*/

#include <boost/scoped_ptr.hpp>
#include "MonitorUMS.hpp"
#include "SystemException.hpp"
#include "AuthenticatorConfiguration.hpp"
#include "AuthenticatorFactory.hpp"
#include "Authenticator.hpp"

using namespace std;


/**
* \brief Constructor, raises an exception on error
* \param interval The interval to check the database
*/
MonitorUMS::MonitorUMS(int interval) {
minterval = interval;
mdatabaseVishnu = NULL;
mauthenticator = NULL;
}

/**
* \brief Destructor
*/

MonitorUMS::~MonitorUMS() {
  if (mdatabaseVishnu != NULL) {
    delete mdatabaseVishnu;
  }
}


/**
* \brief To initialize the UMS monitor with individual parameters instead of configuration file
* \param vishnuId The password of the root user vishnu_user for the connection with the database
* \param dbConfig The configuration of the database
* \param authenticatorConfig The configuration of the authenticator
* \return raises an execption
*/
void
MonitorUMS::init(int vishnuId,
                 DbConfiguration dbConfig,
                 AuthenticatorConfiguration authenticatorConfig) {

  DbFactory factory;
  mdatabaseVishnu = factory.createDatabaseInstance(dbConfig);

  AuthenticatorFactory authfactory;
  mauthenticator = authfactory.createAuthenticatorInstance(authenticatorConfig);

  std::string sqlCommand("SELECT * FROM vishnu where vishnuid="+vishnu::convertToString(vishnuId));

  try {
    /*connection to the database*/
    mdatabaseVishnu->connect();

    /* Checking of vishnuid on the database */
    boost::scoped_ptr<DatabaseResult> result(mdatabaseVishnu->getResult(sqlCommand.c_str()));
    if (result->getResults().size() == 0) {
      throw SystemException(ERRCODE_DBERR, "The vishnuid is unrecognized");
    }
  } catch (VishnuException& e) {
    exit(0);
  }

}

/**
* \brief To launch the UMS Monitor
* \return raises an exception
*/
int
MonitorUMS::run() {

  std::vector<std::string>::iterator ii;
  std::vector<std::string> tmp;
  SessionServer closer;

  try {
    boost::scoped_ptr<DatabaseResult> result(closer.getSessionToclosebyTimeout());

    if (result->getNbTuples() != 0) {
      for (size_t i = 0; i < result->getNbTuples(); ++i) {
        tmp.clear();
        tmp = result->get(i);

        ii = tmp.begin();
        SessionServer sessionServer (*ii);

        try {
          //closure of the session
          sessionServer.close();
        }
        catch (VishnuException& e) {
          string errorInfo =  e.buildExceptionString();
          cerr << errorInfo << endl;
          if (e.getMsgI() == ERRCODE_AUTHENTERR) {
            //FIXME: Do something for the sed UMS when the monitor goes out
            cerr << errorInfo << endl;
            exit(1);
          }
        }
      }
    }
    sleep(minterval);

  } catch (VishnuException& e) {
    string errorInfo =  e.buildExceptionString();

    if ((e.getMsgI() == ERRCODE_DBERR) || (e.getMsgI() == ERRCODE_AUTHENTERR)) {
      cerr << errorInfo << endl;
      exit(1);
    }
    sleep(minterval);
  }
  return 0;
}
