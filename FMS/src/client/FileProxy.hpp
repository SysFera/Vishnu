/**
 * \file FileProxy.hpp
 * This file declares a  proxy class to handle a file
 * \author Daouda Traore (daouda.traore@sysfera.com)
 */


#ifndef FILEPROXY_HH
#define FILEPROXY_HH

#include <string>
#include <list>

#include <sys/types.h>
#include <sys/stat.h>

#include "SessionProxy.hpp"
#include "FMS_Data_forward.hpp"
#include "FMS_Data.hpp"
#include "FMSConstants.hpp"
using namespace FMS_Data;


/**
 * \brief FileProxy "locality" enumeration.
 */
typedef enum {
  local,
  remote
} file_host_t;

/**
 * \brief The stat structure differs depending on the system type. 
 * BSD file systems used the same structure for large and small
 * partition type.
 */
#if FS_32 | BSD_LIKE_SYSTEM
typedef struct stat file_stat_t;
typedef off_t file_size_t;
#define STAT(path, buf) stat((path), (buf))
#else
typedef struct stat64 file_stat_t;
/**
 * \brief The object size definition type
 */
typedef off64_t file_size_t;
/**
 * \brief A stat function default definition
 */

#define STAT(path, buf) stat64((path), (buf))
#endif

/**
 * \brief Main FileProxy class. Encapsulates all the files attributes. 
 *  Defines the common operation on files (local or remote)
 */
class FileProxy {

  private:
    /**
     * \brief The host of the file
     */
    std::string mhost;
  
    /**
     * \brief To check if the file exists
     */  
    mutable bool exist;
    
    /**
     * \brief The session object proxy 
     */  
      SessionProxy msessionProxy;
    /**
     * \brief The inode information of the file
     */  
      mutable FileStat mfileStat;

    protected:

    /**
     * \brief To update the inode information of the file
     * \param fileStat the new inode information
     */  
      void setFileStat(const FileStat& fileStat)const;
    /**
     * \brief To update the path  of the file
     * \param path the new path
     */  
      void setPath(const std::string& path);
   
      /**
       * \brief To update the host  of the file
       * \param host the new host
       */  
     
      void setHost(const std::string& host);

      /**
       * \brief To update the name of the file owner
       * \param owner the new owner
       */  
      void setOwner(const std::string& owner) const;
      
      /**
       * \brief To update the group of the file owner
       * \param group the new group
       */  
      void setGroup(const std::string& group) const;
      
      /**
       * \brief To update the access permissions of the file
       * \param perms the new access permissions
       */  
      void setPerms(const mode_t perms) const;
      
      /**
       * \brief To update the identifier of the file owner
       * \param uid the new owner identifier
       */  
      void setUid(const uid_t uid) const;
      
      /**
       * \brief To update the group identifier of the file owner
       * \param gid the new group identifier
       */  
      void setGid(const gid_t gid) const;
      
      /**
       * \brief To update the size of the file
       * \param size the new size
       */  
      void setSize(const file_size_t size) const;
      
      /**
       * \brief To update the last access time of the file
       * \param atime the new access time
       */  
      void setAtime(const time_t atime) const;
      
      /**
       * \brief To update the last modification time of the file
       * \param mtime the new modofocation time
       */  
      void setMtime(const time_t mtime) const;
      
      /**
       * \brief To update the last change time of the file
       * \param ctime the new change time
       */  
      void setCtime(const time_t ctime) const;
      
      /**
       * \brief To update the file type
       * \param type the new  file type
       */  
      void setType(const FileType& type) const;
      
      /**
       * \brief To updata the file existence flag
       * \param exist the new file existence flag 
       */  
      void exists(const bool exist) const;

    public:

      /**
       * \brief The default constructor
       */ 
      FileProxy();
      /**
       * \brief Another constructor taking two parameters
       * \param sessionProxy  the session object proxy
       * \param path the path of the file
       */ 
      FileProxy(const SessionProxy& sessionProxy,
          const std::string& path);
      /**
       * \brief Another constructor by reference
       * \param fileProxy the other file 
       */ 
      explicit FileProxy(const FileProxy& fileProxy);
      /**
       * \brief The default destructor
       */
      virtual ~FileProxy();

      /**
       * \brief The assignment operator
       * \param fileProxy the object to assign
       * \return the new assigned file
       */
      FileProxy& operator=(const FileProxy& fileProxy);  

      /**
       * \brief To get session proxy object
       * \return the session in which the file was created
       */
      const SessionProxy& getSession() const;
      /**
       * \brief To get the inode information of the file
       * \return the file inode information
       */
      const FileStat& getFileStat() const;

      /**
       * \brief To get the path of the file
       * \return the file path
       */
      const std::string& getPath() const;
      
      /**
       * \brief To get the name of the file owner
       * \return the file owner name
       */
      const std::string& getOwner() const;
      /**
       * \brief To get the group name of the file owner
       * \return the group name
       */

      const std::string& getGroup() const;

      /**
       * \brief To get the host in which the file is located
       * \return the host of the file
       */
      const std::string& getHost() const;

      /**
       * \brief To get the file access permissions
       * \return the file access permissions
       */
      mode_t getPerms() const;

      /**
       * \brief To get the identifier of the file owner
       * \return the identifier of the file owner
       */
      uid_t getUid() const;

      /**
       * \brief To get the group identifier of the file owner
       * \return the group identifier of the file owner
       */
      gid_t getGid() const;

      /**
       * \brief To get the size of the file 
       * \return the file size
       */
      file_size_t getSize() const;

      /**
       * \brief To get the last access time of the file
       * \return the last file access time
       */
      time_t getAtime() const;

      /**
       * \brief To get the last  modification time of the file
       * \return the last  modification time
       */
      time_t getMtime() const;

      /**
       * \brief To get the last change time of the file
       * \return the last change time
       */
      time_t getCtime() const;

      /**
       * \brief To get the file type
       * \return the file type
       */
      FileType getType() const;
      /**
       * \brief To check if the file exists
       * \return true if the file exists, false otherwise
       */
      bool exists() const;
      /**
       * \brief To check if the file information is up to date
       * \return true if the file is already updated, false otherwise
       */
      virtual bool isUpToDate() const = 0;

      /**
       * \brief To get the file inode information
       */
      virtual void getInfos() const = 0;

      /**
       * \brief To update the group of the file
       * \param group the new group
       * \return 0 if the command succeeds, an error code otherwise
       */
      virtual int chgrp(const std::string& group) = 0;

      /**
       * \brief To update the new file access permissions
       * \param mode the new file access permissions
       * \return 0 if the command succeeds, an error code otherwise
       */
      virtual int chmod(const mode_t mode) = 0;
      /**
       * \brief To get the first lines of the file
       * \param options the options object 
       * \return the first lines of the file
       */
      virtual std::string head(const HeadOfFileOptions& options) = 0;

      /**
       * \brief To get the last lines of the file
       * \param options the options object 
       * \return the last lines of the file
       */
      virtual std::string tail(const TailOfFileOptions& options) = 0;

      /**
       * \brief To get the content of the file
       * \return the content of the file
       */
      virtual std::string getContent() = 0;
      /**
       * \brief To create a new file
       * \param mode the access permission of the file
       * \return 0 if the command succeeds, an error code otherwise
       */ 
      virtual int mkfile(const mode_t mode=defaultFileAccessMode) = 0;  

      /**
       * \brief To create a new directory
       * \param mode the access permission of the directory
       * \return 0 if the command succeeds, an error code otherwise
       */ 
      virtual int mkdir(const mode_t mode=defaultDirectoryAccessMode) = 0;

      /**
       * \brief To remove a file
       * \param options the remove file options  
       * \return 0 if the command succeeds, an error code otherwise
       */ 
      virtual int rm(const RmFileOptions& options) = 0;

      /**
       * \brief To remove an empty directory
       * \return 0 if the command succeeds, an error code otherwise
       */ 
      virtual int rmdir() = 0;

      /**
       * \brief To list the content of a directory
       * \param options the list options 
       * \return the content of the directory
       */ 
      virtual std::list<std::string> ls(const LsDirOptions& options) const = 0; 
      /**
       * \brief To copy the file 
       * \param dest the copy destination
       * \param options the copy options  
       * \return 0 if the command succeeds, an error code otherwise
       */
      virtual int cp(const std::string& dest, const CpFileOptions& options) = 0;

      /**
       * \brief To move the file 
       * \param dest the move destination
       * \param options the move options  
       * \return 0 if the command succeeds, an error code otherwise
       */

      virtual int mv(const std::string& dest, const CpFileOptions& options) = 0; 

      /**
       * \brief To copy the file in asynchronous mode 
       * \param dest the copy destination
       * \param options the copy options  
       * \param fileTransfer the file transfer informatio
       * \return 0 if the command succeeds, an error code otherwise
       */
      virtual int cpAsync(const std::string& dest, 
          const CpFileOptions& options, 
          FileTransfer& fileTransfer) = 0;

      /**
       * \brief To move the file in asynchronous mode 
       * \param dest the move destination
       * \param options the move options  
       * \param fileTransfer the file transfer informatio
       * \return 0 if the command succeeds, an error code otherwise
       */
      virtual int mvAsync(const std::string& dest, 
          const CpFileOptions& options, 
          FileTransfer& fileTransfer) = 0;

      /**
       * \brief a useful function to extract the host name from path
       * \param path the file path 
       * \return the host name
       */
      static std::string extHost(const std::string& path);

      /**
       * \brief a useful function to extract the file path name from the complete path
       * \param path the complete file path 
       * \return the file path
       */
      static std::string extName(const std::string& path);
};



#endif
