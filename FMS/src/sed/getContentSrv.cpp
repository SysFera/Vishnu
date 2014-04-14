#include <string>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <boost/scoped_ptr.hpp>
#include <sys/types.h>
#include "FileFactory.hpp"
#include "DIET_client.h"
#include "UserServer.hpp"
#include "MachineServer.hpp"
#include "FMSMapper.hpp"
#include "MapperRegistry.hpp"

/* get Content  Vishnu callback function.
 client parameters. Returns an error message if something gone wrong. */
/* Returns the n first line of the file to the client application. */
int contentFile(diet_profile_t* profile) {
  std::string localPath, localUser, userKey, acLogin, machineName;
  std::string path = "";
  std::string user = "";
  std::string host = "";
  std::string sessionKey = "";
  std::string cmd = "";

  diet_string_get(profile, 0, sessionKey);
  diet_string_get(profile, 1, path);
  diet_string_get(profile, 2, user);
  diet_string_get(profile, 3, host);

  // reset the profile to handle result
  diet_profile_reset(profile, 2);

  localUser = user;
  localPath = path;
  SessionServer sessionServer (sessionKey);

  try {
    int mapperkey;
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(vishnu::FMSMAPPERNAME);
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
    boost::scoped_ptr<File> file(ff.getFileServer(sessionServer,localPath, acLogin, userKey));

    diet_string_set(profile, 0, "success");
    diet_string_set(profile, 1, file->getContent());

    //To register the command
    sessionServer.finish(cmd, vishnu::FMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& err) {
    try {
      sessionServer.finish(cmd, vishnu::FMS, vishnu::CMDFAILED);
    } catch (VishnuException& fe) {
      err.appendMsgComp(fe.what());
    }
    diet_string_set(profile, 0, "error");
    diet_string_set(profile, 1, err.what());
  }
  return 0;
}
