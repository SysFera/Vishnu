#include <string>
#include <stdexcept>
#include <iostream>
#include <cstring>

#include <sys/types.h>

#include "FileFactory.hpp"

#include "DIET_client.h"
#include "UserServer.hpp"
#include "MachineServer.hpp"
#include <boost/scoped_ptr.hpp>

#include "FMSMapper.hpp"

using namespace std;


/// DIET profile construction.
//diet_profile_desc_t* getContentProfile() {
//  diet_profile_desc_t* result = diet_profile_desc_alloc("FileContent", 3, 3, 5);
//
//  diet_generic_desc_set(diet_param_desc(result, 0), DIET_STRING, DIET_CHAR);
//  diet_generic_desc_set(diet_param_desc(result, 1), DIET_STRING, DIET_CHAR);
//  diet_generic_desc_set(diet_param_desc(result, 2), DIET_STRING, DIET_CHAR);
//  diet_generic_desc_set(diet_param_desc(result, 3), DIET_PARAMSTRING, DIET_CHAR);
//  diet_generic_desc_set(diet_param_desc(result, 4), DIET_STRING, DIET_CHAR);
//  diet_generic_desc_set(diet_param_desc(result, 5), DIET_STRING, DIET_CHAR);
//
//  return result;
//}

/* get Content  DIET callback function.
 client parameters. Returns an error message if something gone wrong. */
/* Returns the n first line of the file to the client application. */
int contentFile(diet_profile_t* profile) {
  std::string localPath, localUser, userKey, acLogin, machineName;
  std::string path = "";
  std::string user = "";
  std::string host = "";
  std::string sessionKey = "";
  std::string finishError ="";
  std::string cmd = "";
  std::string result = "";
  std::string errMsg = "";
  int mapperkey;


  diet_string_get(profile, 0, sessionKey);
  diet_string_get(profile, 1, path);
  diet_string_get(profile, 2, user);
  diet_string_get(profile, 3, host);


  localUser = user;
  localPath = path;
  SessionServer sessionServer (sessionKey);

  try {

    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(FMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_content_of_file");
    mapper->code(host + ":" + path, mapperkey);
    cmd = mapper->finalize(mapperkey);


    // check the sessionKey

    sessionServer.check();
   //
    UMS_Data::Machine_ptr machine = new UMS_Data::Machine();
    machine->setMachineId(host);
    MachineServer machineServer(machine);

    // check the machine
    machineServer.checkMachine();

    // get the machineName
    machineName = machineServer.getMachineName();
    delete machine;

    // get the acLogin
    acLogin = UserServer(sessionServer).getUserAccountLogin(host);

    FileFactory ff;
    ff.setSSHServer(machineName);
    boost::scoped_ptr<File> file (ff.getFileServer(sessionServer,localPath, acLogin, userKey));

	result = file->getContent();

	//To register the command
	sessionServer.finish(cmd, FMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& err) {
	try {
	  sessionServer.finish(cmd, FMS, vishnu::CMDFAILED);
	} catch (VishnuException& fe) {
	  finishError =  fe.what();
	  finishError +="\n";
	}
	err.appendMsgComp(finishError);
	result = "";
	errMsg = err.buildExceptionString();
  }
  diet_string_set(profile, 4, result.c_str());
  diet_string_set(profile, 5, errMsg.c_str());
  return 0;
}
