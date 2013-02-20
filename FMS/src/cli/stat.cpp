/**
 * \file stat.cpp
 * This file defines the VISHNU  get file infos  command 
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 */

#include "CLICmd.hpp"
#include "utilVishnu.hpp"
#include "cliError.hpp"
#include "cliUtil.hpp"
#include "api_ums.hpp"
#include "api_fms.hpp"
#include "FMS_Data.hpp"
#include "sessionUtils.hpp"
#include <boost/bind.hpp>
#include "FMSDisplayer.hpp"
#include "GenericCli.hpp"
#include "remoteCommandUtils.hpp"


namespace po = boost::program_options;

using namespace std;
using namespace vishnu;
using namespace FMS_Data;

struct GetFileInfoFunc {

  std::string mpath;

  GetFileInfoFunc(const std::string& path):mpath(path){}

  int operator()(const std::string& sessionKey) {
  
    FileStat fileStat;
  
    int res = stat(sessionKey,mpath,fileStat);
      //To dispaly the file information
      std::cout << fileStat << std::endl;
    return res;
  }
};



int main (int ac, char* av[]){
  
  /******* Parsed value containers ****************/
  string configFile;
  string path;

  //buid options and parse 
  
  ParseRemoteCommandOptions (ac,av,configFile,path);
  GetFileInfoFunc apiFunc(path);
  return GenericCli().run(apiFunc, configFile, ac, av);
}

