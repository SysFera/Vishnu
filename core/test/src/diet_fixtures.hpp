/*
 * diet_fixtures.hpp
 *
 * Author: hguemar
 *
 */

#ifndef DIET_FIXTURES_HPP_
#define DIET_FIXTURES_HPP_

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <csignal>

#include <boost/assign/list_inserter.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/filesystem.hpp>
#include <boost/process/all.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>
#include "diet_config_tests.h"
#include "utils.hpp"

namespace ba = boost::assign;
namespace bf = boost::filesystem;
namespace bp = boost::process;
namespace bs = boost::system;

class setDIETEnvFixture {
public:
    setDIETEnvFixture() {
        BOOST_TEST_MESSAGE( "== Test setup [BEGIN]: setting environment ==" );

        // Set env regarding DIET compiled libraries
        bp::environment::iterator i_c;
        if (getenv(ENV_LIBRARY_PATH_NAME)) {
            std::string dietLibPath = std::string(ENV_LIBRARY_PATH)
                                      + std::string(getenv(ENV_LIBRARY_PATH_NAME));
            setenv(ENV_LIBRARY_PATH_NAME, dietLibPath.c_str(), 1);

            BOOST_TEST_MESSAGE( "== Test setup [END]: setting environment ==" );
        }

    }

    ~setDIETEnvFixture() {
        BOOST_TEST_MESSAGE( "== Test teardown [BEGIN]: unsetting environment ==" );
        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME*2));
        BOOST_TEST_MESSAGE( "== Test teardown [END]: unsetting environment ==" );
    }

};


class createTmpDirsFixture : public setDIETEnvFixture {
public:
    createTmpDirsFixture() {
        BOOST_TEST_MESSAGE( "== Test setup [BEGIN]: creating directories ==" );
				//To be implemented if necessary
        BOOST_TEST_MESSAGE( "== Test setup [END]: creating directories ==" );
    }

    ~createTmpDirsFixture() {
        BOOST_TEST_MESSAGE( "== Test teardown [BEGIN]: deleting directories ==" );
				//To be implemented if necessary
        BOOST_TEST_MESSAGE( "== Test teardown [END]: deleting directories ==" );
    }

};


/* Diet test fixture (aka test context)
 * basically setup the naming service before starting our test
 * and then cleanup after test has been executed
 */
class DispatcherFixture : public createTmpDirsFixture {
    boost::scoped_ptr<bp::child> processNamingService;

public:
    DispatcherFixture() : processNamingService(NULL) {
        BOOST_TEST_MESSAGE( "== Test setup [BEGIN]: Launching Dispatcher ==" );

        std::string exec;
        try {
            exec = bp::find_executable_in_path(DISPATCHER_COMMAND, BIN_DIR);
        } catch (bs::system_error& e) {
            BOOST_TEST_MESSAGE( "can't find " << DISPATCHER_COMMAND << ": " << e.what() );
            return;
        }

        BOOST_TEST_MESSAGE( DISPATCHER_COMMAND << " found: " << exec );

        // setup omniNames environment
        bp::context ctx;
        ctx.process_name = DISPATCHER_COMMAND;

#ifndef DEBUG_TESTS
        // redirect output to /dev/null
        ctx.streams[bp::stdout_id] = bp::behavior::null();
        ctx.streams[bp::stderr_id] = bp::behavior::null();
#endif
        // setup dispatcher arguments
				char cfg[] = DISPATCHER_CONFIG;
				BOOST_TEST_MESSAGE( "=== Dispatcher CONFIG == "<<  DISPATCHER_CONFIG);
        std::vector<std::string> args = ba::list_of(cfg);
        bp::child c = bp::create_child(exec, args, ctx);
        processNamingService.reset(utils::copy_child(c));
        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME));
        BOOST_TEST_MESSAGE( "== Test setup [END]:  Launching Dispatcher ==" );
    }

    ~DispatcherFixture() {
        BOOST_TEST_MESSAGE( "== Test teardown [BEGIN]: Stopping Dispatcher ==" );

        if (processNamingService) {
            processNamingService->terminate();
            processNamingService->wait();
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME));
        BOOST_TEST_MESSAGE( "== Test teardown [END]: Stopping Dispatcher ==" );
    }
};


template <const char *config,  class parentFixture>
class DietAgentFixture : public parentFixture
{
    boost::scoped_ptr<bp::child> processAgent;

public:
    DietAgentFixture() : processAgent(NULL) {
        BOOST_TEST_MESSAGE( "== Test setup [BEGIN]:  Launching DIET Agent (config file: "
                            << config << ") ==" );

        std::string exec;
        try {
            exec = bp::find_executable_in_path("dietAgent", DIETAGENT_DIR);
        } catch (bs::system_error& e) {
            BOOST_TEST_MESSAGE( "can't find dietAgent: " << e.what() );
            return;
        }

        BOOST_TEST_MESSAGE( "dietAgent found: " << exec );

        // setup dietAgent environment
        bp::context ctx;
        ctx.process_name = "dietAgent";
        bp::environment::iterator i_c;
        i_c = ctx.env.find(ENV_LIBRARY_PATH_NAME);
        if (i_c != ctx.env.end()) {
            i_c->second = std::string(ENV_LIBRARY_PATH) + i_c->second;
        } else {
            ctx.env[ENV_LIBRARY_PATH_NAME] = ENV_LIBRARY_PATH;
        }

#ifndef DEBUG_TESTS
        // redirect output to /dev/null
        ctx.streams[bp::stdout_id] = bp::behavior::null();
        ctx.streams[bp::stderr_id] = bp::behavior::null();
#endif

        // setup dietAGent arguments
        std::vector<std::string> args = ba::list_of(config);

        // launch diet Agent
        const bp::child c = bp::create_child(exec, args, ctx);

        processAgent.reset(utils::copy_child(c));
        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME));
        BOOST_TEST_MESSAGE( "== Test setup [END]: Launching DIET Agent ==" );
    }

    ~DietAgentFixture() {
        BOOST_TEST_MESSAGE( "== Test teardown [BEGIN]: Stopping DIET Agent ==" );
        if (processAgent) {
            processAgent->terminate();
            processAgent->wait();
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME));
        BOOST_TEST_MESSAGE( "== Test teardown [END]: Stopping DIET Agent ==" );
    }
};


template <const char *config,  class parentFixture>
class DietMADAGFixture : public parentFixture
{
    boost::scoped_ptr<bp::child> processMADAG;

public:
    DietMADAGFixture() : processMADAG(NULL) {
        BOOST_TEST_MESSAGE( "== Test setup [BEGIN]:  Launching DIET maDagAgent (config file: "
                            << config << ") ==" );

        std::string exec;
        try {
            exec = bp::find_executable_in_path("maDagAgent", DIETMADAG_DIR);
        } catch (bs::system_error& e) {
            BOOST_TEST_MESSAGE( "can't find maDagAgent: " << e.what() );
            return;
        }

        BOOST_TEST_MESSAGE( "maDagAgent found: " << exec );

        // setup maDagAgent environment
        bp::context ctx;
        ctx.process_name = "maDagAgent";
        bp::environment::iterator i_c;
        i_c = ctx.env.find(ENV_LIBRARY_PATH_NAME);
        if (i_c != ctx.env.end()) {
            i_c->second = std::string(ENV_LIBRARY_PATH) + i_c->second;
        } else {
            ctx.env[ENV_LIBRARY_PATH_NAME] = ENV_LIBRARY_PATH;
        }

        // redirect output to /dev/null
        ctx.streams[bp::stdout_id] = bp::behavior::null();
        ctx.streams[bp::stderr_id] = bp::behavior::null();


        // setup maDagAgent arguments
        std::vector<std::string> args = ba::list_of(config);

        // launch diet maDagAgent
        const bp::child c = bp::create_child(exec, args, ctx);

        processMADAG.reset(utils::copy_child(c));
        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME));
        BOOST_TEST_MESSAGE( "== Test setup [END]: Launching DIET maDagAgent ==" );
    }

    ~DietMADAGFixture() {
        BOOST_TEST_MESSAGE( "== Test teardown [BEGIN]: Stopping DIET maDagAgent ==" );
        if (processMADAG) {
            processMADAG->terminate();
            processMADAG->wait();
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME));
        BOOST_TEST_MESSAGE( "== Test teardown [END]: Stopping DIET maDagAgent ==" );
    }
};


// generic SeD fixture
template <const char *name, const char *binDir, const char *config, class AgentParent>
class DietSeDFixture : public AgentParent
{
    boost::scoped_ptr<bp::child> processSeD;

public:
    DietSeDFixture() : processSeD(NULL) {
        BOOST_TEST_MESSAGE( "== Test setup [BEGIN]: Launching "
                            <<  name << " ==");

        std::string exec;
        try {
            exec = bp::find_executable_in_path(name, binDir);
        } catch (bs::system_error& e) {
            BOOST_TEST_MESSAGE( "can't find " << name << ": "
                                << e.what() );
            BOOST_TEST_MESSAGE( "search path: " << binDir );
            return;
        }

        BOOST_TEST_MESSAGE( "SeD found: " << exec );

        // setup SeD environment
        bp::context ctx;
        ctx.process_name = name;
        bp::environment::iterator i_c;
        i_c = ctx.env.find(ENV_LIBRARY_PATH_NAME);
        if (i_c != ctx.env.end()) {
            i_c->second = std::string(ENV_LIBRARY_PATH) + i_c->second;
        } else {
            ctx.env[ENV_LIBRARY_PATH_NAME] = ENV_LIBRARY_PATH;
        }
#ifndef DEBUG_TESTS
        // redirect output to /dev/null
        ctx.streams[bp::stdout_id] = bp::behavior::null();
        ctx.streams[bp::stderr_id] = bp::behavior::null();
#endif
        // launch SeD
        std::vector<std::string> sedArgs = ba::list_of(std::string(config));
        const bp::child sed = bp::create_child(exec, sedArgs, ctx);
        processSeD.reset(utils::copy_child(sed));

        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME*2));
        BOOST_TEST_MESSAGE( "== Test setup [END]: launching "
                            << name << " ==" );
    }


    ~DietSeDFixture()
    {
        BOOST_TEST_MESSAGE( "== Test teardown [BEGIN]: Stopping "
                            << name << " ==" );
        if( processSeD ) {
            try {
                processSeD->terminate();
                // FIXME: currently processSeD->wait() crashes, we need to set the signal handler of SIGCHLD to SID_DFL
                signal(SIGCHLD, SIG_DFL);
            } catch (...) {
                BOOST_TEST_MESSAGE( "== Problem while stopping "
                                    << name << " ==" );
            }
        }

        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME*2));
        BOOST_TEST_MESSAGE( "== Test teardown [END]: Stopping "
                            << name << " ==" );
    }
};

#ifdef USE_LOG_SERVICE
template <const char *config>
class LogServiceFixture : public DispatcherFixture {
    boost::scoped_ptr<bp::child> process;

public:
    LogServiceFixture() : process(NULL) {
        BOOST_TEST_MESSAGE( "== Test setup [BEGIN]: Launching LogService ==" );
        BOOST_TEST_MESSAGE( LOGSERVICE_COMMAND  << " found: " << LOGCENTRAL_PATH);

        // setup LogService environment
        bp::context ctx;
        ctx.process_name = LOGSERVICE_COMMAND;

        // redirect output to /dev/null
        ctx.streams[bp::stdout_id] = bp::behavior::null();
        ctx.streams[bp::stderr_id] = bp::behavior::null();

        // setup LogService arguments
        std::vector<std::string> args = ba::list_of(std::string("-config"))
                                        (std::string(config));

        // launch LogService
        bp::child c = bp::create_child(LOGCENTRAL_PATH, args, ctx);
        process.reset(utils::copy_child(c));
        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME));
        BOOST_TEST_MESSAGE( "== Test setup [END]:  Launching LogService ==" );
    }

    ~LogServiceFixture() {
        BOOST_TEST_MESSAGE( "== Test teardown [BEGIN]: Stopping LogService ==" );
        if (process) {
            process->terminate();
            process->wait();
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME));
        BOOST_TEST_MESSAGE( "== Test teardown [END]: Stopping LogService ==" );
    }
};


template <const char *config>
class DIETLogToolFixture : public LogServiceFixture<config> {
    boost::scoped_ptr<bp::child> process;

public:
    DIETLogToolFixture() : process(NULL) {
        BOOST_TEST_MESSAGE( "== Test setup [BEGIN]: Launching DIETLogTool ==" );

        std::string exec;
        try {
            exec = bp::find_executable_in_path(DIETLOGTOOL_COMMAND, DIETLOGTOOL_PATH);
        } catch (bs::system_error& e) {
            BOOST_TEST_MESSAGE( "can't find " << DIETLOGTOOL_COMMAND << ": " << e.what() );
            return;
        }

        BOOST_TEST_MESSAGE( DIETLOGTOOL_COMMAND << " found: " << exec );

        // setup LogService environment
        bp::context ctx;
        ctx.process_name = DIETLOGTOOL_COMMAND;

        // redirect output to /dev/null
        ctx.streams[bp::stdout_id] = bp::behavior::null();
        ctx.streams[bp::stderr_id] = bp::behavior::null();

        // setup LogService arguments
        std::vector<std::string> args= ba::list_of("");

        // launch DIETLogTool
        bp::child c = bp::create_child(exec, args, ctx);
        process.reset(utils::copy_child(c));
        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME));
        BOOST_TEST_MESSAGE( "== Test setup [END]:  Launching DIETLogTool ==" );
    }

    ~DIETLogToolFixture() {
        BOOST_TEST_MESSAGE( "== Test teardown [BEGIN]: Stopping DIETLogTool ==" );
        if (process) {
            process->terminate();
            process->wait();
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME));
        BOOST_TEST_MESSAGE( "== Test teardown [END]: Stopping DIETLogTool ==" );
    }
};
#endif // USE_LOG_SERVICE

char SimpleAddSeD[] = "SimpleAddSeD";
char ConfigSimpleAddSeD[] = SIMPLE_ADD_SED_CONFIG;
char ConfigSimpleAddSeDLA[] = SIMPLE_ADD_SED_CONFIG_LA;
char SimpleAddSeDBinDir[] = BIN_DIR;

char AllDataTransferAddSeD[] = "transfers_server";
char AllDataTransferBinDir[] = EXAMPLES_DIR "/allDataTransfers";


char DynamicAddRemoveServiceAddSeD[] = "server_dyn_add_rem";
char DynamicAddRemoveServiceBinDir[] = EXAMPLES_DIR "/dyn_add_rem";

char GRPCAddSeD[] = "gridrpc_server";
char GRPCBinDir[] = EXAMPLES_DIR "/GridRPC";



#ifdef USE_LOG_SERVICE
char LogServiceConfig[] = LOGSERVICE_CONFIG;
typedef LogServiceFixture<LogServiceConfig>  DietLogServfixture;
typedef DIETLogToolFixture<LogServiceConfig> LogServiceFixtureConf;
#endif // USE_LOG_SERVICE


#endif /* DIET_FIXTURES_HPP_ */
