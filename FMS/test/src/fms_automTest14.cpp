/**
 * \file fms_automTest
 * \brief Contains FMS API test implementation
 * References: VISHNU_D3_1b_FMS-PlanTests
 */
// Prerequisites for this test suite to work correctly:
// 1/ check the cmake parameters TEST_*
// 2/ setup a 'test' unix group on host TEST_FMS_HOST1
//    and add the user TEST_USER_LOGIN to this group
// 3/ check that the /root directory is not accessible for
//    the user that runs the tests (on TEST_FMS_HOST1)

//Vishnu Headers
#include "FMS_test_utils.hpp"

// namespaces declaration and  aliases
using namespace std;
using namespace UMS_Data;
using namespace FMS_Data;
using namespace vishnu;
namespace ba = boost::assign;
namespace bpt= boost::posix_time;
namespace bfs= boost::filesystem;

// The database, UMS and FMS SeD are launched by FMSSedFixture.
BOOST_FIXTURE_TEST_SUITE(SyncMoveFile, FMSSeDFixture)

// All tests of category 4

BOOST_AUTO_TEST_CASE(SyncMoveFile_Base)
{
  std::string newFileName = "Test_FMS_File";
  std::string newDirName = "Test_FMS_Dir";
  std::string newSubDirName = "Test_FMS_Sub_Dir";
  std::string baseDirFullPath1 = m_test_fms_host1 + ":" + m_test_fms_dir1;
  std::string baseDirFullPath2 = m_test_fms_host2 + ":" + m_test_fms_dir2;
  std::string fileFullPath1 = baseDirFullPath1 + "/" + newFileName;
  std::string fileFullPath2 = baseDirFullPath2 + "/" + newFileName;
  std::string dirFullPath1 = baseDirFullPath1 + "/" + newDirName;
  std::string recursiveDirFullPath1 = dirFullPath1 + "/" +  newSubDirName;
  std::string dirFullPath2 = baseDirFullPath2 + "/" + newDirName;
  std::string localFilePath = m_test_fms_working_dir + "/" + newFileName;

  BOOST_TEST_MESSAGE("Testing synchronous move of files UC F2.MV1-B");
  VishnuConnection vc(m_test_fms_user_login, m_test_fms_user_pwd);
  string sessionKey=vc.getSessionKey();
  string slash = "/";
  string sep = ":";

  try {
    createFile<10>(localFilePath);
    // local to remote
    BOOST_MESSAGE("Checking local to remote move");
    BOOST_MESSAGE("SRC=" + localFilePath);
    BOOST_MESSAGE("DST=" + baseDirFullPath1);
    BOOST_REQUIRE( mv(sessionKey, localFilePath, baseDirFullPath1) == 0);
    // Check
    bool isLocalSourceFound = isFoundInLocalDir(m_test_fms_working_dir, newFileName);
    BOOST_CHECK(!isLocalSourceFound);
    bool isRemoteCopyFound1 = isFoundInDir(sessionKey, baseDirFullPath1, newFileName);
    BOOST_CHECK(isRemoteCopyFound1);

    // remote to remote (using file from previous step)
    BOOST_MESSAGE("Checking remote to remote move");
    BOOST_REQUIRE( mv(sessionKey, fileFullPath1, baseDirFullPath2) == 0);
    // Check
    isRemoteCopyFound1 = isFoundInDir(sessionKey, baseDirFullPath1, newFileName);
    BOOST_CHECK(!isRemoteCopyFound1);
    bool isRemoteCopyFound2 = isFoundInDir(sessionKey, baseDirFullPath2, newFileName);
    BOOST_CHECK(isRemoteCopyFound2);

    // remote to local (using file from previous step)
    BOOST_MESSAGE("Checking remote to local move");
    BOOST_REQUIRE( mv(sessionKey, fileFullPath2, m_test_fms_working_dir) == 0);
    // Check
    isRemoteCopyFound2 = isFoundInDir(sessionKey, baseDirFullPath2, newFileName);
    BOOST_CHECK(!isRemoteCopyFound2);
    bool isLocalCopyFound = isFoundInLocalDir(m_test_fms_working_dir, newFileName);
    BOOST_CHECK(isLocalCopyFound);
    // Cleanup
    vishnu::deleteFile(localFilePath.c_str());

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_CASE(SyncMoveFile_Exceptions)
{
  std::string newFileName = "Test_FMS_File";
  std::string newDirName = "Test_FMS_Dir";
  std::string newSubDirName = "Test_FMS_Sub_Dir";
  std::string baseDirFullPath1 = m_test_fms_host1 + ":" + m_test_fms_dir1;
  std::string baseDirFullPath2 = m_test_fms_host2 + ":" + m_test_fms_dir2;
  std::string fileFullPath1 = baseDirFullPath1 + "/" + newFileName;
  std::string fileFullPath2 = baseDirFullPath2 + "/" + newFileName;
  std::string dirFullPath1 = baseDirFullPath1 + "/" + newDirName;
  std::string recursiveDirFullPath1 = dirFullPath1 + "/" +  newSubDirName;
  std::string dirFullPath2 = baseDirFullPath2 + "/" + newDirName;
  std::string localFilePath = m_test_fms_working_dir + "/" + newFileName;

  BOOST_TEST_MESSAGE("Testing synchronous move of files errors UC F2.MV1-E");
  VishnuConnection vc(m_test_fms_user_login, m_test_fms_user_pwd);
  string sessionKey=vc.getSessionKey();
  string slash = "/";
  string sep = ":";

  try {
    DirEntryList dirContent;
    createFile<10>(localFilePath);
    // E1 case - wrong source path
    BOOST_MESSAGE("Check wrong source path");
    string invalidDir = "rtiui";
    string invalidFullPath = baseDirFullPath1 + slash + invalidDir;
    BOOST_CHECK_THROW( mv(sessionKey, invalidFullPath, baseDirFullPath1), VishnuException);
    // E2 case - wrong destination path
    BOOST_MESSAGE("Check wrong destination path");
    string invalidFullPath2 = baseDirFullPath1 + slash + invalidDir + slash;
    BOOST_CHECK_THROW( mv(sessionKey, localFilePath, invalidFullPath2), VishnuException);
    // E3 case - no access to source path
    BOOST_MESSAGE("Check unaccessible source path");
    string noAccessLocalPath = "/etc/ssh/ssh_host_dsa_key";;
    string noAccessFullPath = m_test_fms_host1 + sep + noAccessLocalPath;
    BOOST_CHECK_THROW( mv(sessionKey, noAccessFullPath, baseDirFullPath1), VishnuException);
    // E3 case - no access to remote path
    BOOST_MESSAGE("Check unaccessible destination path");
    string noAccessRemotePath = m_test_fms_host1 + sep + "/root";
    BOOST_CHECK_THROW( mv(sessionKey, localFilePath, noAccessRemotePath), VishnuException);
    // E4 case
    BOOST_MESSAGE("Check invalid machine");
    string invalidMachineId = "tt";
    string invalidMachineFullPath = invalidMachineId + sep + m_test_fms_dir1;
    BOOST_CHECK_THROW( mv(sessionKey, invalidMachineFullPath, baseDirFullPath1), VishnuException);
    // Cleanup
    vishnu::deleteFile(localFilePath.c_str());
  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}


BOOST_AUTO_TEST_SUITE_END()
// THE END
