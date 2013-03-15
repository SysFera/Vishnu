/**
 * \file Database.hpp
 * \brief This file presents an abstract database.
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 * \date 15/12/10
 */

#ifndef _ABSTRACTDATABASE_H_
#define _ABSTRACTDATABASE_H_

#include <string>
#include "DatabaseResult.hpp"
#include "DbConfiguration.hpp"

static const int SUCCESS =  0;
/**
 * \class Database
 * \brief This class describes a database
 */
class Database{
public :
  /**
   * \brief Function to process the request in the database
   * \param request The request to process (must contain a SINGLE SQL statement without a semicolumn)
   * \param transacId the id of the transaction if one is used
   * \return raises an exception on error
   */
  virtual int
  process(std::string request, int transacId = -1) = 0;
  /**
  * \brief To make a connection to the database
  * \return raises an exception on error
  */
  virtual int
  connect() = 0;
  /**
  * \brief To get the result of a select request
  * \param request The request to process
  * \param transacId the id of the transaction if one is used
  * \return An object which encapsulates the database results
  */
  virtual DatabaseResult*
  getResult(std::string request, int transacId = -1) = 0;
  /**
   * \brief To get the type of database
   * \return An enum identifying the type of database
   */
  virtual DbConfiguration::db_type_t
  getDbType() = 0;

    /**
     * \brief Destructor, raises an exception on error
     */
virtual ~Database();
/**
 * \brief Start a transaction
 * \return The transaction ID
 */
  virtual int
  startTransaction() = 0;
/**
 * \brief End a transaction
 * \param transactionID: The ID of the transaction
 */
  virtual void
  endTransaction(int transactionID) = 0;
/**
 * \brief Cancel a transaction
 * \param transactionID: The ID of the transaction
 */
  virtual void
  cancelTransaction(int transactionID) = 0;
/**
 * \brief To commit a transaction
 * \param transactionID: The ID of the transaction
 */
  virtual void
  flush(int transactionID) = 0;
/**
 * \brief To get a unique id
 * \param table The table to use to generate the id
 * \param fields The fields of the table
 * \param val The values of the fields to insert
 * \param tid The transaction id
 * \param primary the primary key on the table
 * \return A new integer never returned by this function
 */
  virtual int
  generateId(std::string table, std::string fields, std::string val, int tid, std::string primary) = 0;

protected :
  /**
   * \brief Constructor, raises an exception on error
   */
  Database();

private :
  /**
   * \brief To disconnect from the database
   * \return raises an exception on error
   */
  virtual int
  disconnect() = 0;
};


#endif // ABSTRACTDATABASE
