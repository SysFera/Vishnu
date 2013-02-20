/**
 * \file get_processes.cpp
 * This file defines the VISHNU command to get the processes
 * \author Coulomb Kevin (kevin.coulomb@sysfera.com)
 */


#include "CLICmd.hpp"
#include "utilVishnu.hpp"
#include "cliError.hpp"
#include "cliUtil.hpp"
#include "api_ums.hpp"
#include "api_ims.hpp"
#include "sessionUtils.hpp"
#include "displayer.hpp"
#include <boost/bind.hpp>

#include "GenericCli.hpp"

namespace po = boost::program_options;

using namespace std;
using namespace vishnu;

struct GetProcessesFunc {

  IMS_Data::ProcessOp mop; 

  GetProcessesFunc(const IMS_Data::ProcessOp& op):
   mop(op)
  {};

  int operator()(std::string sessionKey) {
    IMS_Data::ListProcesses processes;
    int res = getProcesses(sessionKey, processes, mop);
    displayListProc(&processes);
    return res;
  }
};

boost::shared_ptr<Options>
makeGProcOp(string pgName, 
	     boost::function1<void, string>& fmid,
	     string& configFile){
  boost::shared_ptr<Options> opt(new Options(pgName));

  // Environement option
  opt->add("configFile,c",
           "The diet config file",
           ENV,
           configFile);

  // All cli options
  opt->add("machineId,p",
	   "The id of the machine",
	   CONFIG,
	   fmid);
  return opt;
}

int main (int argc, char* argv[]){
  
  /******* Parsed value containers ****************/
  string configFile;

  /********** EMF data ************/
  IMS_Data::ProcessOp op;

  /******** Callback functions ******************/
  boost::function1<void,string> fmid(boost::bind(&IMS_Data::ProcessOp::setMachineId,boost::ref(op),_1));

  /**************** Describe options *************/
  boost::shared_ptr<Options> opt = makeGProcOp(argv[0], fmid, configFile);

  bool isEmpty;
  //To process list options
  GenericCli().processListOpt(opt, isEmpty, argc, argv);

  //call of the api function
  GetProcessesFunc getProcessesFunc(op);
  return GenericCli().run(getProcessesFunc, configFile, argc, argv);
}
