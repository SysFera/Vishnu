/**
 * \file fms_automTest
 * \brief Contains FMS API test implementation
 * References: VISHNU_D3_1b_FMS-PlanTests
 */
// Prerequisites for this test suite to work correctly:
// 1/ check the cmake parameters TEST_*
// 2/ setup a 'test' unix group on host TEST_FMS_HOST1
//    and add the user TEST_USER_LOGIN to this group

//UMS forward Headers
#include "UMS_Data_forward.hpp"

// FMS forward Headers
#include "FMS_Data_forward.hpp"
#include "FMS_fixtures.hpp"
#include "FMS_testconfig.h"

// C++ Headers
#include <iostream>
#include <sstream>
#include <cmath>

// Boost Headers
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>

#include "vishnuTestUtils.hpp"

// namespaces declaration and  aliases
using namespace std;
using namespace UMS_Data;
using namespace FMS_Data;
using namespace vishnu;
namespace bpt= boost::posix_time;
namespace bfs= boost::filesystem;

static const string adminId = "admin_1";
static const string adminPwd = "admin";
static const string userId = "user_1";
static const string userPwd = "toto";
static const string userLogin = FMSUSERLOGIN;
static const string groupTest = "test"; // userLogin must belong to groupTest on host 1
static const string sep = ":";
static const string slash = "/";
static const string machineId1 = "machine_1"; // name is TEST_FMS_HOST1 set in cmake
static const string machineId2 = "machine_2"; // name is TEST_FMS_HOST2 set in cmake
static const string newFileName = "FMS_test_file";
// local
static const string localDir = FMSWORKINGDIR;
static const string localFilePath = localDir + slash + newFileName;
// remote
static const string remoteDir = "/tmp";
static const string dirFullPath1 = machineId1 + sep + remoteDir;
static const string dirFullPath2 = machineId2 + sep + remoteDir;
static const string fileFullPath1 = dirFullPath1 + slash + newFileName;
static const string fileFullPath2 = dirFullPath2 + slash + newFileName;

// The database, UMS and FMS SeD are launched by FMSSedFixture.
BOOST_GLOBAL_FIXTURE(FMSSeDFixture)

// All tests of category 1,2,3 for FILES only
BOOST_AUTO_TEST_SUITE(singleFile)

BOOST_AUTO_TEST_CASE(CreateFile_Base)
{

  BOOST_TEST_MESSAGE("Testing file creation UC F1.CR1-B");

  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {
    BOOST_REQUIRE( createFile(sessionKey, fileFullPath1) == 0);

    // To check the success of createFile function
    FileStat fileStat;
    BOOST_REQUIRE( getFilesInfo(sessionKey, fileFullPath1, fileStat) ==0  );

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_CASE(DeleteFile_Base)
{

  BOOST_TEST_MESSAGE("Testing file deletion UC F1.DE1-B");

  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {
    BOOST_REQUIRE( removeFile(sessionKey, fileFullPath1) == 0);

    // To check the success of removeFile function
    FileStat fileStat;
    BOOST_CHECK_THROW( getFilesInfo(sessionKey, fileFullPath1, fileStat), VishnuException );

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_CASE(HeadOfFile_Base)
{

  BOOST_TEST_MESSAGE("Testing file head display UC F1.DI1-B");

  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {
    // Create a file 1Mb
    createFile<1000>(localFilePath);

    // Copy file on remote host
    BOOST_REQUIRE( copyFile(sessionKey, localFilePath, fileFullPath1) == 0);

    string content;
    BOOST_REQUIRE( headOfFile(sessionKey, fileFullPath1, content) == 0);

    // To check the success of headOfFile function
    BOOST_CHECK( content.substr(0,8) == "abcdefgh" );

    // Cleanup
    BOOST_CHECK( removeFile(sessionKey, fileFullPath1) == 0);
    BOOST_CHECK( removeFile(sessionKey, localFilePath) == 0);

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_CASE(TailOfFile_Base)
{

  BOOST_TEST_MESSAGE("Testing file tail display UC F1.DI2-B");

  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {
    // Create a file 1Mb
    createFile<1000>(localFilePath);

    // Copy file on remote host
    BOOST_REQUIRE( copyFile(sessionKey, localFilePath, fileFullPath1) == 0);

    string content;
    BOOST_REQUIRE( tailOfFile(sessionKey, fileFullPath1, content) == 0);

    // To check the success of headOfFile function
    BOOST_CHECK( content.substr(content.size()-8,8) == "abcdefgh" );

    // Cleanup
    BOOST_CHECK( removeFile(sessionKey, fileFullPath1) == 0);
    BOOST_CHECK( removeFile(sessionKey, localFilePath) == 0);

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_CASE(ContentOfFile_Base)
{

  BOOST_TEST_MESSAGE("Testing file content display UC F1.DI3-B");

  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {
    // Create a file 1Mb
    createFile<1000>(localFilePath);

    // Copy file on remote host
    BOOST_REQUIRE( copyFile(sessionKey, localFilePath, fileFullPath1) == 0);

    string content;
    BOOST_REQUIRE( contentOfFile(sessionKey, fileFullPath1, content) == 0);

    // To check the success of contentOfFile function
    BOOST_CHECK( content.substr(8,8) == "abcdefgh" );

    // Cleanup
    BOOST_CHECK( removeFile(sessionKey, fileFullPath1) == 0);
    BOOST_CHECK( removeFile(sessionKey, localFilePath) == 0);

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_CASE(GetFileInfo_Base)
{

  BOOST_TEST_MESSAGE("Testing file info display UC F1.DI5-B");

  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {
    // Create a file 10Kb
    createFile<10>(localFilePath);

    // Copy file on remote host
    BOOST_REQUIRE( copyFile(sessionKey, localFilePath, fileFullPath1) == 0);

    FileStat stat;
    BOOST_REQUIRE( getFilesInfo(sessionKey, fileFullPath1, stat) == 0);

    // To check the success
    BOOST_CHECK( stat.getSize() == 10240 );
    BOOST_CHECK( stat.getOwner() == userLogin);
    BOOST_CHECK( stat.getPerms() == 0644);

    // Cleanup
    BOOST_CHECK( removeFile(sessionKey, fileFullPath1) == 0);
    BOOST_CHECK( removeFile(sessionKey, localFilePath) == 0);

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_CASE(ChangeFileRights_Base)
{

  BOOST_TEST_MESSAGE("Testing file rights change UC F1.CH1-B");

  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {
    // Create a file 10Kb
    createFile<10>(localFilePath);

    // Copy file on remote host
    BOOST_REQUIRE( copyFile(sessionKey, localFilePath, fileFullPath1) == 0);

    BOOST_REQUIRE( chMod(sessionKey, 600, fileFullPath1) == 0);

    // To check the success
    FileStat stat;
    BOOST_REQUIRE( getFilesInfo(sessionKey, fileFullPath1, stat) == 0);
    BOOST_CHECK( stat.getPerms() == 0600);

    // Cleanup
    BOOST_CHECK( removeFile(sessionKey, fileFullPath1) == 0);
    BOOST_CHECK( removeFile(sessionKey, localFilePath) == 0);

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_CASE(ChangeGroup_Base)
{

  BOOST_TEST_MESSAGE("Testing file group change UC F1.CH2-B");

  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {
    // Create a file 10Kb
    createFile<10>(localFilePath);

    // Copy file on remote host
    BOOST_REQUIRE( copyFile(sessionKey, localFilePath, fileFullPath1) == 0);

    BOOST_REQUIRE( chGrp(sessionKey, groupTest, fileFullPath1) == 0);

    // To check the success
    FileStat stat;
    BOOST_REQUIRE( getFilesInfo(sessionKey, fileFullPath1, stat) == 0);
    BOOST_CHECK( stat.getGroup() == groupTest);

    // Cleanup
    BOOST_CHECK( removeFile(sessionKey, fileFullPath1) == 0);
    BOOST_CHECK( removeFile(sessionKey, localFilePath) == 0);

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}



BOOST_AUTO_TEST_SUITE_END()


// THE END

