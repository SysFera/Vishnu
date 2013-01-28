
#ifndef FMS_TEST_UTILS_HPP
#define FMS_TEST_UTILS_HPP

#include "UMS_Data_forward.hpp"
// FMS forward Headers
#include "FMS_Data_forward.hpp"
#include "FMS_fixtures.hpp"
#define STATUS_INPROGRESS 0
#define STATUS_COMPLETED 1
#define STATUS_CANCELED 2
#define STATUS_FAILED 3

// C++ Headers
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

// Boost Headers
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/assign/list_of.hpp>

// Vishnu Headers

#include "utilVishnu.hpp"
#include "vishnuTestUtils.hpp"

// namespaces declaration and  aliases
using namespace std;
using namespace UMS_Data;
using namespace FMS_Data;
using namespace vishnu;
namespace ba = boost::assign;
namespace bpt= boost::posix_time;
namespace bfs= boost::filesystem;


/*static const std::string machineId1 = "";//FMSDIR1;
static const std::string machineId2 = "";//FMSDIR2;
static const string adminId = "admin_1";
static const string adminPwd = "admin";
static const string userId = "user_1";
static const string userPwd = "toto";
static const string userLogin = "";//FMSUSERLOGIN;*/
/*static const string groupTest = "test"; // userLogin must belong to groupTest on host 1
static const string sep = ":";
static const string slash = "/";
static const string newFileName = "FMS_test_file";
static const string newDirName = "FMS_test_dir";
static const string newSubDirName = "FMS_test_sub_dir";

static const std::string remoteBaseDir1 = "";//FMSDIR1;
static const std::string remoteBaseDir2 = "";//FMSDIR2;
static const std::string baseDirFullPath1 = "host1" + sep + remoteBaseDir1;
static const std::string baseDirFullPath2 = "m_test_fms_host1" + sep + remoteBaseDir2;
static const std::string fileFullPath1 = baseDirFullPath1 + slash + newFileName;
static const std::string fileFullPath2 = baseDirFullPath2 + slash + newFileName;
static const std::string dirFullPath1 = baseDirFullPath1 + slash + newDirName;
static const std::string recursiveDirFullPath1 = dirFullPath1 + slash +  newSubDirName;
static const std::string dirFullPath2 = baseDirFullPath2 + slash + newDirName;
// local
static const string localDir = "";//FMSWORKINGDIR;
static const string localFilePath = localDir + slash + newFileName;
// remote*/




/**
 * \brief Check if given strings are found in directory
 * \param sessionKey  the session key
 * \param dirFullPath the directory complete path (host:path)
 * \param names       the strings to search for (vector)
 * \return true if all names are found within the directory long content
 */
bool areFoundInDir(const string& sessionKey,
                   const string& dirFullPath,
                   const vector<string>& names) {
  DirEntryList dirContent;
  LsDirOptions lsOptions;
  lsOptions.setLongFormat(true);
  BOOST_REQUIRE( ls(sessionKey, dirFullPath, dirContent) ==0  );
  bool areFound = true;
  unsigned int i;
  for (vector<string>::const_iterator iterNames = names.begin();
    iterNames != names.end();
    ++iterNames) {
      bool isFound = false;
      i=0;
      while (!isFound &&  i < dirContent.getDirEntries().size()) {
        isFound = ((*iterNames) == (dirContent.getDirEntries().get(i))->getPath());
        ++i;
      }
      if (!isFound) {
        areFound = false;
      }
  }
  return areFound;
}
/**
 * \brief Check if a given string is found in directory
 * \param sessionKey  the session key
 * \param dirFullPath the directory complete path (host:path)
 * \param name        the string to search for
 * \return true name is found within the directory long content
 */
bool isFoundInDir(const string& sessionKey,
                  const string& dirFullPath,
                  const string& name) {
  return areFoundInDir(sessionKey, dirFullPath, ba::list_of(name));
}
/**
 * \brief Check if a given string is found in a local directory (must match a FILE name)
 * \param dirLocalPath the directory local path
 * \param name        the string to search for
 * \return true name is found within the directory long content
 */
bool isFoundInLocalDir(const string& dirLocalPath,
                       const string& name) {
  bfs::path dir(dirLocalPath);
  bfs::directory_iterator end_iter;
  if ( bfs::exists(dir) && bfs::is_directory(dir)) {
    for( bfs::directory_iterator dir_iter(dir) ; dir_iter != end_iter ; ++dir_iter) {
      if ( bfs::is_regular_file(dir_iter->status())
            && dir_iter->path().leaf() == name) {
        return true;
      }
    }
  }
  return false;
}

/**
 * \brief Add prefix to a vector of strings
 * \param prefix  the common prefix
 * \param suffixes  the vector of strings
 * \return the modified vector of strings (prefix + suffixes[i])
 */
vector<string>&
addPrefix(const string& prefix, vector<string>& suffixes) {
  for (vector<string>::iterator iter = suffixes.begin();
    iter != suffixes.end();
    ++iter  )
    {
      (*iter) = prefix + (*iter);
   }
  return suffixes;
}
/**
 * \brief Create several files on remote machine
 * \param sessionKey  the session key
 * \param localFilePaths  the local paths for the files
 * \param remoteFullPath  the destination full path (directory)
 */
void
createRemoteFiles(const string& sessionKey,
                  const vector<string>& localFilePaths,
                  const string& remoteFullPath) {
  for (vector<string>::const_iterator iter = localFilePaths.begin();
    iter != localFilePaths.end();
    ++iter) {
    const string& localFilePath = *iter;
    createFile<1>(localFilePath);
    BOOST_MESSAGE("CreateRemoteFile: " << localFilePath);
    string errorMsg =  "Could not copy file ";
    errorMsg.append(localFilePath);
    errorMsg.append(" on remote host");
    BOOST_REQUIRE_MESSAGE(cp(sessionKey, localFilePath, remoteFullPath) == 0,
      errorMsg);
  }
}

/*****************************************************************************/
/************************** T R A N S F E R S ********************************/
/*****************************************************************************/
/**
 * \brief Wait until termination of an asynchronous file transfer
 * \param sessionKey the session Key
 * \param transferInfo  the file transfer information
 * \return the final status value of the file transfer (-1 if error)
 */

int
waitAsyncCopy(const string& sessionKey, const FileTransfer& transferInfo) {
  unsigned int        pollCounter = 10;
  bool                terminated = false;
  LsTransferOptions   options;
  FileTransferList    fileTransferList;
  options.setTransferId(transferInfo.getTransferId());
  while (!terminated && pollCounter--) {
    if (listFileTransfers(sessionKey, fileTransferList, options) != 0) {
      BOOST_MESSAGE("ERROR: Could not retrieve file transfer information");
      return -1;
    }
    if (fileTransferList.getFileTransfers().size() == 1) {
      FileTransfer* ft = fileTransferList.getFileTransfers().get(0);
      if (ft->getStatus() != STATUS_INPROGRESS) {
        BOOST_MESSAGE("Async transfer is terminated! - status = " + convertToString(ft->getStatus()));
        if (ft->getStatus() == STATUS_FAILED) {
          BOOST_MESSAGE("Transfer failed message: " + ft->getErrorMsg());
        }
        terminated = true;
      }
    } else if (fileTransferList.getFileTransfers().size() == 0) {
      BOOST_MESSAGE("ERROR: File transfer list is empty for a given transferId!");
      return -1;
    } else {
      BOOST_MESSAGE("ERROR: File transfer list contains more than 1 item for a given transferId!");
      return -1;
    }
    bpt::seconds sleepTime(5);
    boost::this_thread::sleep(sleepTime);
  }
  if (!terminated) {
    BOOST_MESSAGE("ERROR: End of polling for file transfer");
    return -1;
  }
  return fileTransferList.getFileTransfers().get(0)->getStatus();
}


#endif
