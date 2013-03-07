/**
 * \file stop.cpp
 * This file defines the VISHNU command to stop a vishnu process
 * \author Eugène PAMBA CAPO-CHICHI(eugene.capochichi@sysfera.com)
 */


#include "CLICmd.hpp"
#include "utilVishnu.hpp"
#include "cliError.hpp"
#include "cliUtil.hpp"
#include "api_ums.hpp"
#include "api_ims.hpp"
#include "sessionUtils.hpp"
#include <boost/bind.hpp>

#include "GenericCli.hpp"

using namespace std;
using namespace vishnu;

struct StopFunc {

  std::string mmid;
  IMS_Data::SupervisorOp mop;

  StopFunc(std::string mid, const IMS_Data::SupervisorOp& op):
    mmid(mid), mop(op)
  {};

  int operator()(std::string sessionKey) {
    return stop(sessionKey, mmid, mop);
  }
};


boost::shared_ptr<Options>
makeStopOpt(string pgName,
            boost::function1<void, string>& fname,
            string& configFile) {

  boost::shared_ptr<Options> opt(new Options(pgName));

  // Environement option
  opt->add("configFile,c",
           "VISHNU configuration file",
           ENV,
           configFile);

  opt->add( "processName,n",
            "represents the name of the element",
            CONFIG,
            fname,1);

  return opt;
}


int main (int argc, char* argv[]){

  /******* Parsed value containers ****************/
  string configFile;
  string machineId;

   /********** EMF data ************/
  IMS_Data::SupervisorOp op;

  /******** Callback functions ******************/
  boost::function1<void,string> fname(boost::bind(&IMS_Data::SupervisorOp::setName,boost::ref(op),_1));

  /**************** Describe options *************/
  boost::shared_ptr<Options> opt=makeStopOpt(argv[0], fname, configFile);



  opt->add( "machineId,i",
            "represents the id of the machine",
            HIDDEN,
            machineId,1);

  opt->setPosition("machineId",1);

  bool isEmpty;
  //To process list options
  GenericCli().processListOpt(opt, isEmpty, argc, argv);

  //call of the api function
  StopFunc stopFunc(machineId, op);
  return GenericCli().run(stopFunc, configFile, argc, argv);

}
