/**
 * \file tmssed.cpp
 * \brief This file contains the VISHNU TMS sed main function.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date April 2011
 */

#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <sys/types.h>
#include <boost/shared_ptr.hpp>

#include "MachineServer.hpp"
#include "ServerTMS.hpp"
#include "ExecConfiguration.hpp"
#include "DbConfiguration.hpp"
#include "MonitorTMS.hpp"

//For ZMQ
#include "zmq.hpp"
#include "DIET_client.h"
#include "Server.hpp"


/**
 * \brief To show how to use the sed
 * \fn int usage(char* cmd)
 * \param cmd The name of the program
 * \return Always 1
 */
int
usage(char* cmd) {
  std::cout << "\nUsage: " << cmd << " vishnu_config.cfg\n\n";
  return 1;
}

/**
 * \brief The main function
 * \param argc Number of parameter
 * \param argv List of argument
 * \param envp Array of environment variables
 * \return The result of the diet sed call
 */
int main(int argc, char* argv[], char* envp[]) {

  int res = 0;
  int vishnuId = 0;
  int interval = 1;
  ExecConfiguration config;
  DbConfiguration dbConfig(config);
  BatchType batchType ;
  std::string batchTypeStr;
  std::string machineId;
  std::string remoteBinDirectory;
  std::string defaultBatchConfig;
  string TMSTYPE = "tmssed";
  string cfg;

  string uri;

  if (argc != 2) {
      return usage(argv[0]);
    }

  // Read the configuration
  try {
    config.initFromFile(argv[1]);
    config.getRequiredConfigValue<int>(vishnu::VISHNUID, vishnuId);
    config.getRequiredConfigValue<int>(vishnu::INTERVALMONITOR, interval);
    config.getConfigValue<std::string>(vishnu::DEFAULTBATCHCONFIGFILE, defaultBatchConfig);
    config.getRequiredConfigValue<std::string>(vishnu::URI, uri);

    if (interval < 0) {
        throw UserException(ERRCODE_INVALID_PARAM, "The Monitor interval value is incorrect");
      }
    dbConfig.check();
    config.getRequiredConfigValue<std::string>(vishnu::BATCHTYPE, batchTypeStr);
    if (batchTypeStr == "TORQUE") {
#ifndef HAVE_TORQUE_2_3
        std::cerr << "\nError: The support of TORQUE is not enabled in this server!\n";
        exit(1);
#endif
        batchType = TORQUE;
      } else if (batchTypeStr == "PBS") {
#ifndef HAVE_PBSPRO_10_4
        std::cerr << "\nError: The support of PBS is not enabled in this server!\n";
        exit(1);
#endif
        batchType = PBSPRO;
      } else if (batchTypeStr == "LOADLEVELER") {
#ifndef HAVE_LOADLEVELER_2_5
        std::cerr << "\nError: The support of LOADLEVELER is not enabled in this server!\n";
        exit(1);
#endif
        batchType = LOADLEVELER;
      } else if (batchTypeStr == "SLURM") {
#if !( HAVE_SLURM_2_2 || HAVE_SLURM_2_3)
        std::cerr << "\nError: The support of SLURM is not enabled in this server!\n";
        exit(1);
#endif
        batchType = SLURM;

      } else if (batchTypeStr == "LSF") {
#ifndef HAVE_LSF_7_0
        std::cerr << "\nError: The support of LSF is not enabled in this server!\n";
        exit(1);
#endif
        batchType = LSF;
      } else if (batchTypeStr == "SGE") {
#ifndef HAVE_SGE_11
        std::cerr << "\nError: The support of SGE is not enabled in this server!\n";
        exit(1);
#endif
        batchType = SGE;
      } else {
        std::cerr << "\nError: invalid batch type parameter. Supported batch schedulers are 'TORQUE', 'LOADLEVELER', 'SLURM', 'LSF', 'SGE' and 'PBS')\n";
        exit(1);
      }
    config.getRequiredConfigValue<std::string>(vishnu::MACHINEID, machineId);
    if (!config.getConfigValue<std::string>(vishnu::REMOTEBINDIR, remoteBinDirectory)) {
        remoteBinDirectory = ExecConfiguration::getCurrentBinaryDir();
      }
  } catch (UserException& e) {
    std::cerr << "\n" << e.what() << "\n\n";
    exit(1);
  }catch (std::exception& e) {
    std::cerr << "\n" << argv[0] << " : "<< e.what() << "\n\n";
    exit(1);
  }

  // Fork a child for UMS monitoring
  pid_t pid = pid = fork();
  if (pid > 0) {

      try {
        //Check if machineId is authorized
        if (0 == machineId.compare(AUTOMATIC_SUBMIT_JOB_KEYWORD)){
            std::cerr << "\n" << AUTOMATIC_SUBMIT_JOB_KEYWORD
                      << " is not authorized as machine identifier. "
                      << "It is a TMS keyword.\n\n";
            exit(1);
          }
        if (0 == machineId.compare(LIST_JOBS_ON_MACHINES_KEYWORD)) {
            std::cerr << "\n" << LIST_JOBS_ON_MACHINES_KEYWORD
                      << " is not authorized as machine identifier. "
                      << "It is a TMS keyword.\n\n";
            exit(1);
          }

        //Initialize the TMS Server
        boost::shared_ptr<ServerTMS> server (ServerTMS::getInstance());
        res = server->init(vishnuId, dbConfig, machineId,
                           batchType, remoteBinDirectory, defaultBatchConfig);

        std::vector<std::string> ls = server.get()->getServices();
        registerSeD(TMSTYPE, config, cfg, ls);

        UMS_Data::UMS_DataFactory_ptr ecoreFactory =
            UMS_Data::UMS_DataFactory::_instance();
        UMS_Data::Machine_ptr machine = ecoreFactory->createMachine();
        machine->setMachineId(machineId);

        MachineServer machineServer(machine);
        machineServer.checkMachine();
        delete machine;

        // Initialize the DIET SeD
        if (!res) {
            ZMQServerStart(server, uri);
            unregisterSeD(TMSTYPE, config);
          } else {
            std::cerr << "\nThere was a problem during services initialization\n\n";
            exit(1);
          }
      } catch (VishnuException& e) {
        std::cerr << e.what() << "\n";
        exit(1);
      }

    }  else if (pid == 0) {
      // Initialize the TMS Monitor (Opens a connection to the database)
      MonitorTMS monitor(interval);
      dbConfig.setDbPoolSize(1);
      monitor.init(vishnuId, dbConfig, machineId, batchType);
      monitor.run();
    } else {
      std::cerr << "\nThere was a problem to initialize the server\n\n";
      exit(1);
    }
  return res;
}
