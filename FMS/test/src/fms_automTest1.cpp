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
BOOST_FIXTURE_TEST_SUITE(CreateFile, FMSSeDFixture)



/*****************************************************************************/
/******************************* F I L E S ***********************************/
/*****************************************************************************/

// All tests of category 1,2,3 for FILES only

BOOST_AUTO_TEST_CASE(CreateFile_Base)
{

  /*std::string remoteBaseDir1 = "";//FMSDIR1;
  std::string remoteBaseDir2 = "";//FMSDIR2;
  std::string baseDirFullPath1 = m_test_fms_host1 + sep + remoteBaseDir1;
  std::string baseDirFullPath2 = m_test_fms_host1 + sep + remoteBaseDir2;
  std::string fileFullPath1 = baseDirFullPath1 + slash + newFileName;
  std::string fileFullPath2 = baseDirFullPath2 + slash + newFileName;
  std::string dirFullPath1 = baseDirFullPath1 + slash + newDirName;
  std::string recursiveDirFullPath1 = dirFullPath1 + slash +  newSubDirName;
  std::string dirFullPath2 = baseDirFullPath2 + slash + newDirName;*/
  
  BOOST_TEST_MESSAGE("Testing file creation UC F1.CR1-B");
  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {

    if(isFoundInDir(sessionKey,baseDirFullPath1,newFileName)){
      RmFileOptions rmOptions;
      rmOptions.setIsRecursive (true);
      BOOST_REQUIRE( rm(sessionKey,fileFullPath1 ,rmOptions) == 0);

    }

    BOOST_REQUIRE( touch(sessionKey, fileFullPath1) == 0);

    // To check the success of touch function
    FileStat fileStat;
    BOOST_CHECK( stat(sessionKey, fileFullPath1, fileStat) ==0  );

    // Cleanup
    BOOST_CHECK( rm(sessionKey, fileFullPath1) == 0);

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_CASE(CreateFile_Exceptions)
{
  /*std::string remoteBaseDir1 = "";//FMSDIR1;
  std::string remoteBaseDir2 = "";//FMSDIR2;
  std::string baseDirFullPath1 = m_test_fms_host1 + sep + remoteBaseDir1;
  std::string baseDirFullPath2 = m_test_fms_host1 + sep + remoteBaseDir2;
  std::string fileFullPath1 = baseDirFullPath1 + slash + newFileName;
  std::string fileFullPath2 = baseDirFullPath2 + slash + newFileName;
  std::string dirFullPath1 = baseDirFullPath1 + slash + newDirName;
  std::string recursiveDirFullPath1 = dirFullPath1 + slash +  newSubDirName;
  std::string dirFullPath2 = baseDirFullPath2 + slash + newDirName;*/
  
  BOOST_TEST_MESSAGE("Testing file creation errors UC F1.CR1-E");
  VishnuConnection vc(userId, userPwd);
  string sessionKey=vc.getSessionKey();

  try {
    // E1 case
    string invalidDir = "rkvh";
    string invalidFullPath = baseDirFullPath1 + slash + invalidDir + slash + newFileName;
    BOOST_CHECK_THROW( touch(sessionKey, invalidFullPath), VishnuException);
    // E2 case
    string noAccessDir = "/root";
    string noAccessFullPath = m_test_fms_host1 + sep + noAccessDir;
    BOOST_CHECK_THROW( touch(sessionKey, noAccessFullPath), VishnuException);
    // E3 case
    string invalidMachineId = "tt";
    string invalidMachineFullPath = invalidMachineId + sep + remoteBaseDir1;
    BOOST_CHECK_THROW( touch(sessionKey, invalidMachineFullPath), VishnuException);

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_SUITE_END()
// THE END
