/**
 * \file ims_automTest
 * \brief Contains IMS API test implementation
 * References: VISHNU_D5_1b_IMS-PlanTests
 */
/*********************************************************
#####Tests prerequisites:#######
- All ums and tms prerequisites must be considered
- The Cmake variable TEST_LOCAL_HOSTNAME, which is the name of the
local machine on which the tests will be launched,
must be defined.

- The Cmake variable TEST_ROOT_LOGIN which is the name of the user unix
account of local machine must be defined

*********************************************************/

//UMS forward Headers
#include "UMS_Data_forward.hpp"
//IMS forward Headers
#include "IMS_Data_forward.hpp"
#include "IMS_fixtures.hpp"
#include "vishnuTestUtils.hpp"
#include "utilVishnu.hpp"

#include "TMS_Data.hpp"
using namespace TMS_Data;

// C++ Headers
#include <iostream>
#include <sstream>
#include <cmath>

// Boost Headers
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

// namespaces declaration and  aliases
using namespace std;
using namespace UMS_Data;
using namespace IMS_Data;
using namespace vishnu;
namespace bpt= boost::posix_time;
namespace bfs= boost::filesystem;

static const string adminId = "root";
static const string adminPwd = "vishnu_user";
static const string userId = "user_1";
static const string userPwd = "toto";
static const string sqlPath = "IMSSQLPATH";
static const string machineId="machine_1";
static const string badMachineId="unknown_name";
static const string sshCmd =" ssh -o PasswordAuthentication=no ";

BOOST_FIXTURE_TEST_SUITE(cleaning_call, IMSSeDFixture)

//To clean the table process
BOOST_AUTO_TEST_CASE(cleaning_call) {

  BOOST_TEST_MESSAGE("Cleaning call");
  VishnuConnection vc(adminId, adminPwd);
  int ret;
  // get the session key and the machine identifier
  string sessionKey=vc.getSessionKey();
  try {
    //Clean of the table process
    BOOST_CHECK_EQUAL(restore(sqlPath + "/IMScleanProcesses.sql"), 0);

    if (restore(sqlPath + "/IMScleanProcesses.sql") != 0) {
      BOOST_TEST_MESSAGE("Database update failed for restore(sqlPath + /IMScleanProcesses.sql)");
    }
  }
  catch (VishnuException& e) {
    BOOST_MESSAGE("FAILED\n");
    BOOST_MESSAGE(e.what());
    BOOST_CHECK(false);
  }
}
BOOST_AUTO_TEST_SUITE_END()
// THE END
