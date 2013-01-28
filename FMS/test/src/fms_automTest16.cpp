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

// Vishnu Headers

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
BOOST_FIXTURE_TEST_SUITE(CancelFileTransfer, FMSSeDFixture)

// All tests of category 4

BOOST_AUTO_TEST_CASE(CancelFileTransfer_Base)
{
  std::string newFileName = "Test_FMS_File";
  std::string newDirName = "Test_FMS_Dir";
  std::string newSubDirName = "Test_FMS_Sub_Dir";
  std::string baseDirFullPath1 = m_test_fms_host1 + ":" + m_test_fms_dir1;
  std::string baseDirFullPath2 = m_test_fms_host1 + ":" + m_test_fms_dir2;
  std::string fileFullPath1 = baseDirFullPath1 + "/" + newFileName;
  std::string fileFullPath2 = baseDirFullPath2 + "/" + newFileName;
  std::string dirFullPath1 = baseDirFullPath1 + "/" + newDirName;
  std::string recursiveDirFullPath1 = dirFullPath1 + "/" +  newSubDirName;
  std::string dirFullPath2 = baseDirFullPath2 + "/" + newDirName;
  std::string localFilePath = m_test_fms_working_dir + "/" + newFileName;
  
  BOOST_TEST_MESSAGE("Testing file transfer cancel UC F2.CA1-B");
  VishnuConnection vc(m_test_fms_user_login, m_test_fms_user_pwd);
  string sessionKey=vc.getSessionKey();

  try {
    FileTransfer transferInfo;
    createFile<100000>(localFilePath);
    // local to remote
    BOOST_MESSAGE("Checking local to remote cancel");
    BOOST_REQUIRE( acp(sessionKey, localFilePath, baseDirFullPath1, transferInfo) == 0);
    // Wait two seconds
    bpt::seconds sleepTime(2);
    boost::this_thread::sleep(sleepTime);
    // Check list
    FileTransferList transferList;
    LsTransferOptions transferOpts;
    BOOST_REQUIRE( listFileTransfers(sessionKey, transferList, transferOpts) == 0);
    bool transferFound = false;
    for (unsigned int i=0; i < transferList.getFileTransfers().size(); ++i) {
      if (transferList.getFileTransfers().get(i)->getTransferId() == transferInfo.getTransferId()) {
        transferFound = true;
        break;
      }
    }
    BOOST_CHECK_MESSAGE( transferFound, "The transfer was not found - id=" + transferInfo.getTransferId() );
    // Cancel
    StopTransferOptions stopOpts;
    stopOpts.setTransferId(transferInfo.getTransferId());
    BOOST_REQUIRE( stopFileTransfer(sessionKey, stopOpts) == 0 );
    // Check
    transferOpts.setTransferId(transferInfo.getTransferId());
    BOOST_REQUIRE(listFileTransfers(sessionKey, transferList, transferOpts) == 0);
    BOOST_CHECK_EQUAL(transferList.getFileTransfers().get(0)->getStatus(), STATUS_CANCELED);
    bool isRemoteCopyFound1 = isFoundInDir(sessionKey, baseDirFullPath1, newFileName);
    // Cleanup
    if(isRemoteCopyFound1) {
      BOOST_CHECK( rm(sessionKey, fileFullPath1) == 0);
    }
    vishnu::deleteFile(localFilePath.c_str());

  } catch (VishnuException& e) {
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}

BOOST_AUTO_TEST_SUITE_END()
// THE END
