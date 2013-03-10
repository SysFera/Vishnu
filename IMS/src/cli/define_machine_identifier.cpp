/**
 * \file define_machine_identifier.cpp
 * This file defines the VISHNU command to define the machine identifier
 * \author Coulomb Kevin (kevin.coulomb@sysfera.com)
 */


#include "CLICmd.hpp"
#include "utilVishnu.hpp"
#include "cliError.hpp"
#include "cliUtil.hpp"
#include "api_ums.hpp"
#include "api_ims.hpp"
#include "sessionUtils.hpp"

#include "GenericCli.hpp"
#include "defineIdentifierUtils.hpp"

using namespace std;
using namespace vishnu;

int main (int argc, char* argv[]){

  /******* Parsed value containers ****************/
  string configFile;
  string newMachineFormat;

  boost::shared_ptr<Options> opt(makeDefineIdentifierOptions(argv[0], configFile, newMachineFormat));

  bool isEmpty;
  //To process list options
  GenericCli().processListOpt(opt, isEmpty, argc, argv);

  //call of the api function
  DefineIdentifierFunc<MACHINE> machineIdFunc(newMachineFormat);
  return GenericCli().run(machineIdFunc, configFile, argc, argv);

}
