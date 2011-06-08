/**
* \file MonitorFMS.cpp
* \brief This file presents the implementation of the FMS Monitor
* \authors Daouda Traore (daouda.traore@sysfera.com) and
* Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date April
*/

#include <boost/scoped_ptr.hpp>
#include "ServerFMS.hpp"
#include "DbFactory.hpp"
#include "utilVishnu.hpp"
#include "MonitorFMS.hpp"

/**
* \brief Constructor, raises an exception on error
* \param interval The interval to check the database
*/
MonitorFMS::MonitorFMS(int interval) {
minterval = interval;
mdatabaseVishnu = NULL;
}

/**
* \brief Destructor
* \fn ~MonitorFMS()
*/

MonitorFMS::~MonitorFMS() {
  if (mdatabaseVishnu != NULL) {
    delete mdatabaseVishnu;
  }
}


/**
 * \brief To initialize the FMS monitor with individual parameters instead of configuration file
 * \param vishnuId The password of the root user vishnu_user for the connection with the database
 * \param dbConfig The configuration of the database
 * \param machineId The machine identifier
 * \param batchType The batch scheduler type
 * \return raises an execption
*/
void
MonitorFMS::init(int vishnuId, DbConfiguration dbConfig) {

  DbFactory factory;

  mdatabaseVishnu = factory.createDatabaseInstance(dbConfig);

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
* \brief To launch the FMS Monitor
* \return raises an exception
*/
int
MonitorFMS::run() {

  std::vector<std::string>::iterator iter;
  std::vector<std::string> tmp;
  std::string pid;
  int state;
  std::string sqlUpdatedRequest;
  std::string sqlRequest = "SELECT transferId,processid from filetransfer, vsession where vsession.numsessionid=filetransfer.vsession_numsessionid "
                           " and status=0";

  try {

    boost::scoped_ptr<DatabaseResult> result(mdatabaseVishnu->getResult(sqlRequest.c_str()));
    if (result->getNbTuples() != 0) {
      for (size_t i = 0; i < result->getNbTuples(); ++i) {
        tmp.clear();
        tmp = result->get(i);
        iter = tmp.begin();
        transferId=*iter;
        ++iter;
        pid = *iter;
        ++iter;
        if(false==process_exists(converToString(pid))) {
          sqlUpdatedRequest = "UPDATE filetransfer SET state=3 where transferid='"+transferId+"'";
          mdatabaseVishnu->process(sqlUpdatedRequest.c_str());
        }
      }
    }

    sleep(minterval);

  } catch (VishnuException& e) {
    string errorInfo =  e.buildExceptionString();
  }
  return 0;
}
