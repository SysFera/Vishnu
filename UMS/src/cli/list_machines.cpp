/**
 * \file list_machines.cpp
 * This file defines the VISHNU list machine command
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 */


#include "common.hpp"
#include "cliUtil.hpp"
#include "utils.hpp"
#include "listMachineUtils.hpp"
#include "sessionUtils.hpp"
#include "utilVishnu.hpp"
#include <boost/bind.hpp>

#include "GenericCli.hpp"

namespace po = boost::program_options;

using namespace std;
using namespace vishnu;

struct ListMachineFunc {

  UMS_Data::ListMachines mlsMachine;
  UMS_Data::ListMachineOptions mlistOptions;
  bool mfull;

  ListMachineFunc(UMS_Data::ListMachines lsMachine, UMS_Data::ListMachineOptions listOptions, bool full):
    mlsMachine(lsMachine), mlistOptions(listOptions), mfull(full)
  {};

  int operator()(std::string sessionKey) {
    int res = listMachines(sessionKey,mlsMachine,mlistOptions);
    // Display the list
    if(mfull) {
      cout << mlsMachine << endl;
    }
    else {
      for(unsigned int i = 0; i < mlsMachine.getMachines().size(); i++) {
        cout << mlsMachine.getMachines().get(i) << endl;
      }
    }

    return res;
  }
};

int main (int ac, char* av[]) {
  /******* Parsed value containers ****************/
  string configFile;

  /********** EMF data ************/
  UMS_Data::ListMachines lsMachine;

  UMS_Data::ListMachineOptions listOptions;

  /******** Callback functions ******************/
  boost::function1<void,string> fUserId( boost::bind(&UMS_Data::ListMachineOptions::setUserId,boost::ref(listOptions),_1));
  boost::function1<void,string> fMachineId( boost::bind(&UMS_Data::ListMachineOptions::setMachineId,boost::ref(listOptions),_1));

  /**************** Describe options *************/
  boost::shared_ptr<Options> opt= makeListMachineOptions(av[0],fUserId, configFile, fMachineId);


  opt->add("listAllmachine,a",
           "An option for listing all VISHNU machines",
           CONFIG);

  bool isEmpty;
  //To process list options
  GenericCli().processListOpt(opt, isEmpty, ac, av);

  /********  Process **************************/
  if (opt->count("listAllmachine")){

    listOptions.setListAllMachine(true);
  }

  bool full = false;
  // Display the list
  if(isEmpty || opt->count("listAllmachine")) {
    full = true;
  }

  ListMachineFunc listFunc(lsMachine,listOptions, full);
  return GenericCli().run(listFunc, configFile, ac, av);
}// end of main
