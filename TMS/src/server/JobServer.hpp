/**
  * \file JobServer.hpp
  * \brief This file contains the VISHNU JobServer class.
  * \author Daouda Traore (daouda.traore@sysfera.com)
  * \date April 2011
  */

#ifndef _JOB_SERVER_H
#define _JOB_SERVER_H

#include "TMS_Data.hpp"
#include <string>
#include "SessionServer.hpp"
#include "MachineServer.hpp"
/**
 * \class JobServer
 * \brief JobServer class implementation
 */
class JobServer
{

public:
	/**
  * \param sessionServer The object which encapsulates the session information
  * \param machineId The machine identifier
  * \param job The job data structure
  * \param batchType The batch scheduler type
  * \param batchVersion The batch scheduler version
  * \brief Constructor
  */
  explicit JobServer(const SessionServer& sessionServer,
                     const std::string& machineId,
                     const TMS_Data::Job& job,
                     const ExecConfiguration_Ptr sedConfig);


  /**
   * \brief Function to submit job
   * \param scriptContent the content of the script
   * \param options the options to submit job
   * \param vishnuId The VISHNU identifier
   * \param slaveDirectory the path to the TMS slave executable
   * \return raises an exception on error
   */
  int submitJob(const std::string& scriptContent,
                const TMS_Data::SubmitOptions& options,
                const int& vishnuId,
                const std::string& slaveDirectory,
                const std::vector<std::string>& defaultBatchOption);

  /**
   * \brief Destructor
   */
  ~JobServer();

  /**
   * \brief Function to cancel job
   * \param slaveDirectory the path to the TMS slave executable
   * \return raises an exception on error
   */
	int cancelJob(const std::string& slaveDirectory);

  /**
   * \brief Function to get job information
   * \return The job data structure
   */
  TMS_Data::Job getJobInfo();

  /**
   * \brief Function to get job data
   * \return The job data structure
   */
  TMS_Data::Job getData();

  /**
   * \brief To set the main configuration
   */
  void setSedConfig(ExecConfiguration_Ptr sedConfig);

  /**
   * \brief To get the main configuration
   * \return the pointer to configuration object
   */
  ExecConfiguration_Ptr
  getSedConfig() const;

  private:

  /**
   * \brief Function to scan VISHNU error message
   * \param errorInfo the error information to scan
   * \param code The code The code of the error
   * \param message The message associeted to the error code
   * \return raises an exception on erroor
   */
  void scanErrorMessage(const std::string& errorInfo, int& code, std::string& message);

  /**
   * \brief Function to convert a given date into correspondant long value
   * \fn long long convertToTimeType(std::string date)
   * \param date The date to convert
   * \return The converted value
   */
  long long convertToTimeType(std::string date);

  /**
   * \brief Function to treat the default submission options
   * \param scriptOptions The list of the option value
   * \param cmdsOptions The list of the option value
   * \param batchType The actual type of batch scheduler
   * \return raises an exception on error
   */
  void
  processDefaultOptions(const std::vector<std::string>& defaultBatchOption, std::string& content, std::string& key, BatchType batchType);

  /**
   * \brief Function to insert option line into string
   * \param optionLineToInsert the option to insert
   * \param content The buffer containing the inserted option
   * \param batchType The actual type of batch scheduler
   * \return raises an exception on error
   */
  void
  insertOptionLine(std::string& optionLineToInsert, std::string& content, std::string& key, BatchType batchType);

  /**
   * \brief job data structure
   */
  TMS_Data::Job mjob;

  /**
   * \brief The object which encapsulates the session information
   */
  SessionServer msessionServer;

  /**
   * \brief The machine identifier
   */
  std::string mmachineId;

  /**
   * \brief The type of the batch scheduler
   */
  BatchType mbatchType;

  /**
   * \brief The type of the batch scheduler
   */
  std::string mbatchVersion;

  /**
   * \brief An instance of vishnu database
   */
  Database *mdatabaseVishnu;

  /**
  * \brief The configuration of the SeD
  */
  ExecConfiguration_Ptr msedConfig;

  private:

  /**
  * \brief Function to set the path of output directory
  * \param parentDir The directory in which to create the output dir
* \param dirSuffix the suffix of the output dir
  * \param content the script content to be update which the generated path
  */
  void setOutputDir(const std::string& parentDir,
		const std::string & dirSuffix,
		  std::string & content);
};

#endif
