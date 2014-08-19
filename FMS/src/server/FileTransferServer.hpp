
/**
 * \file FileTransferServer.hpp
 * \brief Contains a declaration of all File transfer services
 */

#ifndef FILETRANSFERSERVER_HPP
#define FILETRANSFERSERVER_HPP

#include "FMS_Data.hpp"
#include <string>
#include <boost/thread.hpp>
#include "DbFactory.hpp"
#include "SessionServer.hpp"
#include "SSHFile.hpp"

/**
 * \brief A useful class to perform a transfer command
 */
class TransferExec {
public:
  /**
   * \brief A constructor by value
   * \param sessionServer a session server object
   * \param srcUser the source user
   * \param srcMachineName the source machine name
   * \param srcPath the source file path
   * \param srcUserKey the source user private key path
   * \param destUser the destination user
   * \param destMachineName the destination machine name
   * \param destPath the destination file path
   * \param transferId The transfer identifier
   */
  TransferExec(const SessionServer& sessionServer,
               const std::string& srcUser,
               const std::string& srcMachineName,
               const std::string& srcPath,
               const std::string& srcUserKey,
               const std::string& destUser,
               const std::string& destMachineName,
               const std::string& destPath,
               const std::string& transferId);
  /**
   * \brief Get the last execution return value
   * \return the last execution return value
   */
  const int&
  getLastExecStatus() const {return mlastExecStatus;}
  /**
   * \brief Get the session server object
   * \return the session server object
   */
  const SessionServer&
  getSessionServer() const {return msessionServer;}
  /**
   * \brief Get the source user
   * \return the source user
   */
  const std::string&
  getSrcUser() const {return msrcUser;}
  /**
   * \brief Get the source machine name
   * \return the source machine name
   */
  const std::string&
  getSrcMachineName() const  {return msrcMachineName;}
  /**
   * \brief Get the source file path
   * \return the source file path
   */
  const std::string&
  getSrcPath() const {return  msrcPath;}
  /**
   * \brief Get the source user private key path
   * \return the source user private key path
   */
  const std::string&
  getSrcUserKey() const {return msrcUserKey;}
  /**
   * \brief Get the destination user
   * \return the destination user
   */
  const std::string&
  getDestUser() const {return mdestUser;}
  /**
   * \brief Get the destination machine name
   * \return the destination machine name
   */
  const std::string&
  getDestMachineName() const {return  mdestMachineName;}
  /**
   * \brief Get the destination file path
   * \return the destination file path
   */
  const std::string&
  getDestPath() const {return mdestPath;}
  /**
   * \brief Get the transfer identifier
   * \return the file transfer identifier
   */
  const std::string&
  getTransferId() const {return mtransferId;}
  /**
   * \brief Get the process identifier
   * \return the process identifier
   */
  const int&
  getProcessId() const {return mprocessId;}
  /**
   * \brief Update the process identifier
   */
  void
  setProcessId(const int& processId) const {mprocessId=processId;}
  /**
   * \brief Update the process identifier in database
   */
  void
  updatePid(const int& pid) const;
  /**
   * \brief Update the last execution return value
   */
  void
  setLastExecStatus(const int& status) const {mlastExecStatus=status;}
  /**
   * \brief To perform a the transfer command
   * \param cmd the transfer command to perform
   * \return The command output or error
   */
  std::pair<std::string, std::string>
  exec(const std::string& cmd) const;

private:
  /**
   * @brief Holds database instance
   */
  Database* mdatabase;
  /**
   * \brief The last execution return value
   */
  mutable int mlastExecStatus;
  /**
   * \brief The last execution process identifier
   */
  mutable int mprocessId;
  /**
   * \brief The file transfer identifier
   */
  mutable std::string mtransferId;
  /**
   * \brief The session server object
   */
  SessionServer msessionServer;
  /**
   * \brief The source user
   */
  std::string msrcUser;
  /**
   * \brief The source machineName
   */
  std::string msrcMachineName;
  /**
   * \brief The source file path
   */
  std::string msrcPath;
  /**
   * \brief The source user private key path
   */
  std::string msrcUserKey;
  /**
   * \brief The destination user
   */
  std::string mdestUser;
  /**
   * \brief The destination machine name
   */
  std::string mdestMachineName;
  /**
   * \brief The destination file path
   */
  std::string mdestPath;
};


/**
 * \brief The main class to handle file transfer
 */
class FileTransferServer {
public:
  /**
   * \brief A constructor by value
   * \param sessionServer a session server object
   */
  FileTransferServer(const SessionServer& sessionServer);

  /**
   * \brief Another constructor by value
   * \param sessionServer a session server object
   * \param srcHost the source host
   * \param destHost the destination host
   * \param srcFilePath the source file path
   * \param destFilePath the destination file path
   */
  FileTransferServer(const SessionServer& sessionServer,
                     const std::string& srcHost,
                     const std::string& destHost,
                     const std::string& srcFilePath,
                     const std::string& destFilePath);

  /**
   * \brief To add a new copy thread
   * \param srcUser the source user
   * \param srcMachineName the source host
   * \param srcUserKey the source user private key path
   * \param destUser the destination user
   * \param destMachineName the destination machine name
   * \param  options the transfer options
   * \return 0 if the service succeeds or an error code otherwise
   */
  int
  addCpThread(const std::string& srcUser,
              const std::string& srcMachineName,
              const std::string& srcUserKey,
              const std::string& destUser,
              const std::string& destMachineName,
              const FMS_Data::CpFileOptions& options);

  /**
   * \brief To add a new asynchronous copy thread
   * \param srcUser the source user
   * \param srcMachineName the source host
   * \param srcUserKey the source user private key path
   * \param destUser the destination user
   * \param destMachineName the destination machine name
   * \param  options the transfer options
   * \return 0 if the service succeeds or an error code otherwise
   */
  int
  addCpAsyncThread(const std::string& srcUser,
                   const std::string& srcMachineName,
                   const std::string& srcUserKey,
                   const std::string& destUser,
                   const std::string& destMachineName,
                   const FMS_Data::CpFileOptions& options);
  /**
   * \brief To add a new move thread
   * \param srcUser the source user
   * \param srcMachineName the source host
   * \param srcUserKey the source user private key path
   * \param destUser the destination user
   * \param destMachineName the destination machine name
   * \param  options the transfer options
   * \return 0 if the service succeeds or an error code otherwise
   */
  int
  addMvThread(const std::string& srcUser,
              const std::string& srcMachineName,
              const std::string& srcUserKey,
              const std::string& destUser,
              const std::string& destMachineName,
              const FMS_Data::CpFileOptions& options);

  /**
   * \brief To add a new asynchronous move thread
   * \param srcUser the source user
   * \param srcMachineName the source host
   * \param srcUserKey the source user private key path
   * \param destUser the destination user
   * \param destMachineName the destination machine name
   * \param  options the transfer options
   * \return 0 if the service succeeds or an error code otherwise
   */
  int
  addMvAsyncThread(const std::string& srcUser,
                   const std::string& srcMachineName,
                   const std::string& srcUserKey,
                   const std::string& destUser,
                   const std::string& destMachineName,
                   const FMS_Data::CpFileOptions& options);
  /**
   * \brief To stop a file transfer thread
   * \param options the stop file transfer options
   * \return 0 if the service succeeds or an error code otherwise
   */
  int
  stopThread(const FMS_Data::StopTransferOptions& options);

  /**
   * \brief To store file transfer information into database
   */
  void
  updateDatabaseRecord();

  /**
   * \brief Get The file transfer information
   * \return The file transfer information
   */
  const FMS_Data::FileTransfer&
  getFileTransfer() const {return mfileTransfer;}

  /**
   * \brief Get the ssh command
   * \return the ssh command
   */
  static const std::string&
  getSSHCommand(void) {return msshCommand;}

  /**
   * \brief Get A database instance to store file transfer information
   * \return the database instance
   */
  static Database*
  getDatabaseInstance();

  /**
   * \brief Get the ssh port
   * \return the ssh port
   */
  static const unsigned int
  getSSHPort() {return msshPort;}


  /**
   * \brief Update The file transfer information
   * \param fileTransfer The new file transfer information
   */
  void
  setFileTransfer(const FMS_Data::FileTransfer& fileTransfer) const {mfileTransfer=fileTransfer;}

private:
  /**
   * @brief Holds database instance
   */
  Database* mdatabase;

  /**
   * \brief The file transfer type  (copy or move)
   */
  File::TransferType mtransferType;
  /**
   * \brief The file transfer execution thread
   */
  boost::thread mthread;
  /**
   * \brief The session server object
   */
  SessionServer msessionServer;
  /**
   * \brief A mutex to synchronise several transfer threads
   */
  boost::mutex mmutex;
  /**
   * \brief The file transfer information
   */
  mutable FMS_Data::FileTransfer mfileTransfer;
  /**
   * \brief The ssh port
   */
  static unsigned int msshPort;
  /**
   * \brief The ssh command
   */
  static std::string msshCommand;

  /**
   * \brief To wait until the end of the file transfer
   */
  void
  waitThread ();
  /**
   * @brief return a pair <machineid, userid> corresponding to the user session
   * @return
   */
  std::pair<std::string, std::string>
  getMachineUserPair(void);
  /**
   * \brief acommon add transfer function used by the other add transfer function
   * \param srcUser the source user
   * \param srcMachineName the source host
   * \param srcUserKey the source user private key path
   * \param destUser the destination user
   * \param destMachineName the destination machine name
   * \param  options the transfer options
   * \return 0 if the service succeeds or an error code otherwise
   */
  int
  addTransferThread(const std::string& srcUser,
                    const std::string& srcMachineName,
                    const std::string& srcUserKey,
                    const std::string& destUser,
                    const std::string& destMachineName,
                    const FMS_Data::CpFileOptions& options);
  /**
   * \brief To perform a copy transfer
   * \param transferExec the information about the transfer
   * \param trCmd the transfer command
   */
  void
  copy(const TransferExec& transferExec, const std::string& trCmd);
  /**
   * \brief To perform a move transfer
   * \param transferExec the information about the transfer
   * \param trCmd the transfer command
   */
  void
  move(const TransferExec& transferExec, const std::string& trCmd);
  /**
   * \brief To stop a  transfer
   * \param transferid the transfer identifier
   * \param pid the transfer process identifier
   * \return 0 if the process succeeds or an error code otherwise
   */
  int
  stopThread(const std::string& transferid,const int& pid);
  /**
   * \brief To process database query options
   * \param options the stop options
   * \param sqlRequest the sql request
   */
  void
  processOptions(const FMS_Data::StopTransferOptions& options,
                 std::string& sqlRequest);

  /**
   * \brief To Update file transfer data in database
   * \param status the last execution status
   * \param transferId the transfer identifier
   * \param errorMsg the eventual file transfer execution error message
   */
  void
  updateStatus(const FMS_Data::Status& status,
               const std::string& transferId,
               const std::string& errorMsg);

  /**
   * \brief A helper function to clean output message from verbosity
   * \param outputMsg the output message
   * \return the cleaned  output message
   */
  static std::string
  cleanOutputMsg(const std::string& outputMsg);


  /**
   * \brief Get an error execution of file transfer from database
   * \param transferid the transfer identifier
   * \return the error message
   */
  std::string
  getErrorFromDatabase(const std::string& transferid);


  /**
   * \brief To add options to sql request
   * \param name the option name
   * \param value the option value
   * \param request the sql request to modify
   */
  void
  addOptionRequest(const std::string& name,
                   const std::string& value,
                   std::string& request);


  /**
   * \brief To check if the transfer identifier exists
   * \param  transferId the transfer identifier
   */
  void
  checkTransferId(std::string transferId);

  /**
   * \brief Update the ssh port
   * \param sshPort The new ssh port
   */
  static void
  setSSHPort(const unsigned int sshPort) {msshPort=sshPort;}

  /**
   * \brief Update the ssh command
   * \param sshCommand The new ssh command
   */
  static void
  setSSHCommand(const std::string& sshCommand) {msshCommand=sshCommand;}

  /**
   * @brief Insert the current transfer info into database
   * @return void. The transfer id will be recored in the encapsulated transfer object description
   */
  void
  dbSave(void);

};

#endif
