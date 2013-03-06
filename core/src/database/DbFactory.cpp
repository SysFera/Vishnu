/**
 * \file DbFactory.cc
 * \brief This file implements the database factory
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 * \date 15/12/10
 */

#include "DbFactory.hpp"

#include "SystemException.hpp"
#ifdef USE_POSTGRES
#include "POSTGREDatabase.hpp"
#endif
#ifdef USE_MYSQL
#include "MYSQLDatabase.hpp"
#endif

Database* DbFactory::mdb = NULL; //%RELAX<MISRA_0_1_3> Used in this file

DbFactory::DbFactory(){
}

DbFactory::~DbFactory(){
}

Database*
DbFactory::createDatabaseInstance(DbConfiguration config)
{
  if (mdb != NULL) {
    throw SystemException(ERRCODE_DBERR, "Database instance already initialized");
  }
  switch (config.getDbType()){
  case DbConfiguration::POSTGRESQL :
#ifdef USE_POSTGRES
    mdb = new POSTGREDatabase(config);
#else
    throw SystemException(ERRCODE_DBERR, "PostgreSQL is not enabled (re-compile with ENABLE_POSTGRES)");
#endif
    break;
  case DbConfiguration::MYSQL:
#ifdef USE_MYSQL
    mdb = new MYSQLDatabase(config);
#else
    throw SystemException(ERRCODE_DBERR, "MySQL is not enabled (re-compile with ENABLE_MYSQL)");
#endif
    break;
  case DbConfiguration::ORACLE:
    // Intentional fallthrough, Oracle is not managed
  default:
    throw SystemException(ERRCODE_DBERR, "Database instance type unknown or not managed");
  }
  return mdb;
}

Database* DbFactory::getDatabaseInstance()
{
  if (mdb == NULL) {
    throw SystemException(ERRCODE_DBERR, "Database instance not initialized");
  }
  return mdb;
}
