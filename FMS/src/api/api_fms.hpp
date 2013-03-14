/** \file api_fms.hpp
 * \brief This file contains the VISHNU api functions for FMS package.
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 * \date MAY 2011
 */

#ifndef API_FMS_HPP
#define API_FMS_HPP

// C++ Headers
#include <string>

#include <sys/types.h>

#include "UserException.hpp"
#include "SystemException.hpp"
#include "UMSVishnuException.hpp"
#include "FMSVishnuException.hpp"
//FMS data  declarations
#include "FMS_Data.hpp"


namespace vishnu {

  /**
   * \brief create a new remote file
   * \param sessionKey the session key
   * \param path  the file path using host:path format
   * \return 0 if everything is OK, another value otherwise
   */
  int
    touch(const std::string& sessionKey,const std::string& path)
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief change the group of a file
   * \param sessionKey the session key
   * \param group the name of the new group to use for this file
   * \param path  the file path using host:path format
   * \return 0 if everything is OK, another value otherwise
   */
  int
    chgrp(const std::string& sessionKey, const std::string& group, const std::string& path)
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief  change the permissions of a file
   * \param sessionKey the session key
   * \param mode the path new mode
   * \param path  the file path using host:path format
   * \return 0 if everything is OK, another value otherwise
   */
  int chmod(const std::string& sessionKey, const mode_t& mode, const std::string& path)
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief  copy the file
   * \param sessionKey the session key
   * \param src  the "source" file path using host:path format
   * \param dest  the "destination" file path using host:path format
   * \param options contains the options
   * \return 0 if everything is OK, another value otherwise
   */
int cp(const std::string& sessionKey, const std::string& src,
       const std::string& dest,
       const FMS_Data::CpFileOptions& options= FMS_Data::CpFileOptions())
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief copy the file in a asynchronous mode
   * \param sessionKey the session key
   * \param src   the "source" file path using host:path format
   * \param dest  the "destination" file path using host:path format
   * \param transferInfo contains different information about the submitted file
   * transfer (like the transfer identifier)
   * \param options contains options used to perform the file transfer
   * \return 0 if everything is OK, another value otherwise
   */
int acp(const std::string& sessionKey,const std::string& src, const std::string& dest,
        FMS_Data::FileTransfer& transferInfo,
        const FMS_Data::CpFileOptions& options = FMS_Data::CpFileOptions())
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief get the first lines of a file
   * \param sessionKey the session key
   * \param path   the file path using host:path format
   * \param contentOfFile the first "nline" lines of the file
   * \param options   contains the options used to perform the service (like the maximum number of lines to get)
   * \return 0 if everything is OK, another value otherwise
   */
  int head(const std::string& sessionKey,const std::string& path,
           std::string& contentOfFile,
           const FMS_Data::HeadOfFileOptions& options = FMS_Data::HeadOfFileOptions())
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief get the content of a file
   * \param sessionKey the session key
   * \param path   the file path using host:path format
   * \param contentOfFile  the content of specified the file
   * \return 0 if everything is OK, another value otherwise
   */
  int more(const std::string& sessionKey,const std::string& path, std::string& contentOfFile)
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);


  /**
   * \brief get the list of files and subdirectories of a directory
   * \param sessionKey the session key
   * \param path  the directory path using host:path format
   * \param dirContent  the directory content
   * \param options   contains the options used to perform the service (like the long format list)
   * \return 0 if everything is OK, another value otherwise
   */

  int ls(const std::string& sessionKey,const std::string& path,
         FMS_Data::DirEntryList& dirContent,
         const FMS_Data::LsDirOptions& options = FMS_Data::LsDirOptions())
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief create a directory
   * \param sessionKey the session key
   * \param path: the directory path using host:path format
   * \param options   contains the options used to perform the service (like the recursive creation)
   * \return 0 if everything is OK, another value otherwise
   */
  int mkdir(const std::string& sessionKey,const std::string& path,
            const FMS_Data::CreateDirOptions& options = FMS_Data::CreateDirOptions())
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief move a file
   * \param sessionKey the session key
   * \param src   the "source" file path using host:path format
   * \param dest  the "destination" file path using host:path format
   * \param options   contains the options used to perform the service (like the transfer command :scp or rsync)
   * \return 0 if everything is OK, another value otherwise
   */
  int mv(const std::string& sessionKey,const std::string& src,
         const std::string& dest,
         const FMS_Data::CpFileOptions& options= FMS_Data::CpFileOptions() )
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief move a file in a asynchronous mode
   * \param sessionKey the session key
   * \param src:   the "source" file path using host:path format
   * \param dest:  the "destination" file path using host:path format
   * \param transferInfo contains different information about the submitted file
   * transfer (like the transfer identifier)
   * \param options   contains the options used to perform the service (like the transfer command :scp or rsync)
   * \return 0 if everything is OK, another value otherwise
   */
  int amv(const std::string& sessionKey,const std::string& src, const std::string& dest,
      FMS_Data::FileTransfer& transferInfo,
          const FMS_Data::CpFileOptions& options= FMS_Data::CpFileOptions())
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /** remove a file
   * \param sessionKey the session key
   * \param path    the file path using host:path format
   * \param options contains options used to perform the remove file function
   \return 0 if everything is OK, another value otherwise
   */
  int rm(const std::string& sessionKey,const std::string& path,
         const FMS_Data::RmFileOptions& options= FMS_Data::RmFileOptions())
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief  remove a directory
   * \param sessionKey the session key
   * \param path    the directory path using host:path format
   * \return 0 if everything is OK, another value otherwise
   */
  int rmdir(const std::string& sessionKey,const std::string& path)
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief get the last lines of a file
   * \param sessionKey the session key
   * \param path    the file path using host:path format
   * \param contentOfFile  the last "nline" lines of the file
   * \param options  the options used to perform the service
   * \param contentOfFile  an user-allocated buffer to store the result
   * \return 0 if everything is OK, another value otherwise
   */
  int tail(const std::string& sessionKey,const std::string& path,
           std::string& contentOfFile,
           const FMS_Data::TailOfFileOptions& options = FMS_Data::TailOfFileOptions())
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);

  /**
   * \brief  obtain informations about a file
   * \param sessionKey the session key
   * \param path the file path using host:path format
   * \param filesInfo  the file informations
   * \return 0 if everything is OK, another value otherwise
   */
  int stat(const std::string& sessionKey,const std::string& path,
           FMS_Data::FileStat& filesInfo)
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);


  /**
   * \brief cancel a file transfer
   * \param sessionKey the session key
   * \param options   contains the options used to perform the service (like the transfer id obtained after a call to acp or
   *          amv )
   \return 0 if everything is OK, another value otherwise
   */
  int stopFileTransfer(const std::string& sessionKey,
                       const FMS_Data::StopTransferOptions& options = FMS_Data::StopTransferOptions() )
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);


  /**
   * \brief List  file transfers
   * \param sessionKey the session key
   * \param fileTransferList the file transfer list
   * \param options contains the options used to perform the service (like the transfer id obtained after a call to acp or
   amv)
   \return 0 if everything is OK, another value otherwise
   */
  int listFileTransfers(const std::string& sessionKey,
                        FMS_Data::FileTransferList& fileTransferList,
                        const FMS_Data::LsTransferOptions& options = FMS_Data::LsTransferOptions())
    throw (UMSVishnuException, FMSVishnuException, UserException, SystemException);




}

#endif
