/**
 * \file current_session_id.cpp
 * This file defines the VISHNU get current session_id command
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 */



#include "common.hpp"
#include "cliUtil.hpp"
#include "utils.hpp"
#include "sessionUtils.hpp"
#include "GenericCli.hpp"
#include "UserException.hpp"

namespace po = boost::program_options;

using namespace std;
using namespace vishnu;


int main (int ac, char* av[]){



  /**************** Describe options *************/
  try{
  boost::shared_ptr< Options> opt(new Options(av[0]) );

  // get the sessionId
  std::string sessionId=getLastSessionId(getppid());

  // DIET call
  if(false==sessionId.empty()){
    std::cout << "current sessionId: " <<  sessionId << "\n";
    return VISHNU_OK;
  }

  errorUsage(av[0],"cannot retrieve sessionId");
  return ERRCODE_CLI_ERROR_RUNTIME;

  } catch(VishnuException& e){// catch all Vishnu runtime error
    std::string  msg = e.getMsg()+" ["+e.getMsgComp()+"]";
    errorUsage(av[0], msg,EXECERROR);
    //check the bad session key
    if (checkBadSessionKeyError(e)){
      removeBadSessionKeyFromFile(getppid());
    }
    return e.getMsgI() ;
  } catch(std::exception& e){// catch all std runtime error
    errorUsage(av[0],e.what());
    return ERRCODE_CLI_ERROR_RUNTIME;
  }


}// end of main
