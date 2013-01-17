/**
* \file UMS/src/sed/internalApi.cpp
* \brief This file implements the internal api of UMS
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/

#include "internalApi.hpp"
#include <string>
#include "utilVishnu.hpp"
#include "utilServer.hpp"
#include "ServerUMS.hpp"
#include "vishnu_version.hpp"
#include "VersionManager.hpp"

using namespace vishnu;

/**
* \brief Function to solve the service sessionConnect
* \fn    void solveSessionConnect(diet_profile_t* pb);
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveSessionConnect(diet_profile_t* pb) {

  std::string userId;
  std::string password;
  std::string clientKey;
  std::string clientHostname;
  std::string options;
  std::string version;
  std::string empty("");
  std::string errorInfo;

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), userId);
  diet_string_get(diet_parameter(pb,1), password);
  diet_string_get(diet_parameter(pb,2), clientKey);
  diet_string_get(diet_parameter(pb,3), clientHostname);
  diet_string_get(diet_parameter(pb,4), options);
  diet_string_get(diet_parameter(pb,5), version);

  UserServer userServer = UserServer(userId, password);
  MachineClientServer machineClientServer =  MachineClientServer(clientKey, clientHostname);
  SessionServer sessionServer("");

  ConnectOptions_ptr connectOpt = NULL;
  Version_ptr versionClient = NULL;
  UMS_Data::Version_ptr versionServer = NULL;

  try {

    //To parse the object serialized
    if(!parseEmfObject(version, versionClient)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    versionServer = vishnu::parseVersion(VISHNU_VERSION);
    if (versionServer == NULL) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM, "The format of the VISHNU VERSION of the server is incorrect");
    }
    VersionManager versionManager(versionClient, versionServer);
    if (!versionManager.isCompatible()) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM, versionManager.getError());
    }
    //To parse the object serialized
    if(!parseEmfObject(options, connectOpt)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    sessionServer.connectSession(userServer, machineClientServer, connectOpt);

    //To serialize the user object
    ::ecorecpp::serializer::serializer _ser;
    UMS_Data::Session session = sessionServer.getData();
    std::string sessionSerializedUpdate = _ser.serialize_str(const_cast<UMS_Data::Session_ptr>(&session));

    //OUT Parameters
    diet_string_set(diet_parameter(pb,6), sessionSerializedUpdate.c_str());
    diet_string_set(diet_parameter(pb,7), empty.c_str());

  } catch (VishnuException& e) {
      errorInfo =  e.buildExceptionString();
      //OUT Parameters
      diet_string_set(diet_parameter(pb,6), empty.c_str());
      diet_string_set(diet_parameter(pb,7), errorInfo.c_str());
  }
  delete connectOpt;
  delete versionClient;
  delete versionServer;
  return 0;
}
/**
* \brief Function to solve the service sessionReconnect
* \fn    void solveSessionReconnect
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveSessionReconnect(diet_profile_t* pb) {

  std::string userId;
  std::string password;
  std::string clientKey;
  std::string clientHostname;
  std::string sessionId;
  std::string version;
  std::string empty("");
  std::string errorInfo;

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), userId);
  diet_string_get(diet_parameter(pb,1), password);
  diet_string_get(diet_parameter(pb,2), clientKey);
  diet_string_get(diet_parameter(pb,3), clientHostname);
  diet_string_get(diet_parameter(pb,4), sessionId);
  diet_string_get(diet_parameter(pb,5), version);

  UserServer userServer = UserServer(userId, password);
  MachineClientServer machineClientServer =  MachineClientServer(clientKey, clientHostname);


  SessionServer sessionServer = SessionServer(empty);
  sessionServer.getData().setSessionId(sessionId);
  Version_ptr versionClient = NULL;
  UMS_Data::Version_ptr versionServer = NULL;

  try {
      //To parse the object serialized
      if(!parseEmfObject(version, versionClient)) {
        throw UMSVishnuException(ERRCODE_INVALID_PARAM);
      }
      versionServer = vishnu::parseVersion(VISHNU_VERSION);
      if (versionServer == NULL) {
        throw UMSVishnuException(ERRCODE_INVALID_PARAM, "The parameter version of the server is mal formed");
      }
      VersionManager versionManager(versionClient, versionServer);
      if (!versionManager.isCompatible()) {
        throw UMSVishnuException(ERRCODE_INVALID_PARAM, versionManager.getError());
      }

      sessionServer.reconnect(userServer, machineClientServer, sessionId);
      //To serialize the user object
      ::ecorecpp::serializer::serializer _ser;
      UMS_Data::Session session = sessionServer.getData();
      std::string sessionSerializedUpdate = _ser.serialize_str(const_cast<UMS_Data::Session_ptr>(&session));

      //OUT Parameters
      diet_string_set(diet_parameter(pb,6), sessionSerializedUpdate.c_str());
      diet_string_set(diet_parameter(pb,7), empty.c_str());

  } catch (VishnuException& e) {
      errorInfo =  e.buildExceptionString();
      diet_string_set(diet_parameter(pb,6), empty.c_str());
      diet_string_set(diet_parameter(pb,7), errorInfo.c_str());
  }
  delete versionClient;
  delete versionServer;
  return 0;
}
/**
* \brief Function to solve the service sessionClose
* \fn    int solveSessionClose(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveSessionClose(diet_profile_t* pb) {
  std::string sessionKey;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameter
  diet_string_get(diet_parameter(pb,0), sessionKey);
  SessionServer sessionServer = SessionServer(sessionKey);

  try {
     //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_close");
    cmd = mapper->finalize(mapperkey);

    sessionServer.close();

    //OUT Parameter
    diet_string_set(diet_parameter(pb,1), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& e) {
       try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT parameter
      diet_string_set(diet_parameter(pb,1), errorInfo.c_str());
  }
  return 0;
}

/**
* \brief Function to solve the service userCreate
* \fn    int solveUserCreate(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveUserCreate(diet_profile_t* pb) {
  std::string sessionKey;
  std::string userSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), userSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);
  UserServer userServer = UserServer(sessionServer);

  User_ptr user = NULL;

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_add_user");
    mapper->code(userSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(userSerialized, user)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    userServer.init();
    userServer.add(user,
                   ServerUMS::getInstance()->getVishnuId(),
                   ServerUMS::getInstance()->getSendmailScriptPath());

    //To serialize the user object
    ::ecorecpp::serializer::serializer _ser;
    std::string userSerializedUpdate = _ser.serialize_str(user);

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), userSerializedUpdate.c_str());
    diet_string_set(diet_parameter(pb,3), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS, user->getUserId());

  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), empty.c_str());
      diet_string_set(diet_parameter(pb,3), errorInfo.c_str());
  }
  delete user;
  return 0;
}

/**
* \brief Function to solve the service solveUserUpdate
* \fn    int solveUserUpdate(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveUserUpdate(diet_profile_t* pb) {
  std::string sessionKey;
  std::string userSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";


  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), userSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);
  UserServer userServer = UserServer(sessionServer);

  User_ptr user = NULL;

  try {
     //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_update_user");
    mapper->code(userSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(userSerialized, user)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    };

    userServer.init();
    userServer.update(user);

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  delete user;
  return 0;
}
/**
* \brief Function to solve the service solveUserDelete
* \fn    int solveUserDelete(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveUserDelete(diet_profile_t* pb) {
  std::string sessionKey;
  std::string userId;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), userId);

  SessionServer sessionServer = SessionServer(sessionKey);
  UserServer userServer = UserServer(sessionServer);

  UMS_Data::User user;
  user.setUserId(userId);

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_delete_user");
    mapper->code(userId, mapperkey);
    cmd = mapper->finalize(mapperkey);

    userServer.init();
    userServer.deleteUser(user);

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      //OUT parameter
      errorInfo =  e.buildExceptionString();
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  return 0;
}
/**
* \brief Function to solve the service solveUserPasswordChange
* \fn    int solveUserPasswordChange(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveUserPasswordChange(diet_profile_t* pb) {

  std::string userId;
  std::string password;
  std::string newPassword;
  std::string version;
  std::string empty("");
  std::string errorInfo;

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), userId);
  diet_string_get(diet_parameter(pb,1), password);
  diet_string_get(diet_parameter(pb,2), newPassword);
  diet_string_get(diet_parameter(pb,3), version);

  UserServer userServer = UserServer(userId, password);
  Version_ptr versionClient = NULL;
  UMS_Data::Version_ptr versionServer = NULL;

  try {
    //To parse the object serialized
    if(!parseEmfObject(version, versionClient)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }
    versionServer = vishnu::parseVersion(VISHNU_VERSION);
    if (versionServer == NULL) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM, "The format of the VISHNU VERSION of the server is incorrect");
    }
    VersionManager versionManager(versionClient, versionServer);
    if (!versionManager.isCompatible()) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM, versionManager.getError());
    }
    userServer.changePassword(newPassword);
    //OUT Parameter
    diet_string_set(diet_parameter(pb,4), empty.c_str());

  } catch (VishnuException& e) {
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,4), errorInfo.c_str());
  }
  return 0;
}

/**
* \brief Function to solve the service solveUserPasswordReset
* \fn    int solveUserPasswordReset(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveUserPasswordReset(diet_profile_t* pb) {
  std::string sessionKey;
  std::string userId;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), userId);

  SessionServer sessionServer = SessionServer(sessionKey);
  UserServer userServer = UserServer(sessionServer);

  UMS_Data::User user;
  user.setUserId(userId);

  try {
     //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_reset_password");
    mapper->code(userId, mapperkey);
    cmd = mapper->finalize(mapperkey);

    userServer.init();
    userServer.resetPassword(user, ServerUMS::getInstance()->getSendmailScriptPath());

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), (user.getPassword()).c_str());
    diet_string_set(diet_parameter(pb,3), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), empty.c_str());
      diet_string_set(diet_parameter(pb,3), errorInfo.c_str());
  }
  return 0;
}

/**
* \brief Function to solve the service solveMachineCreate
* \fn    int solveMachineCreate(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveMachineCreate(diet_profile_t* pb) {
  std::string sessionKey;
  std::string machineSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), machineSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);

  Machine_ptr machine = NULL;

  try {
    std::string msgComp = "The ssh public key file content is invalid";

    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_add_machine");
    mapper->code(machineSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(machineSerialized, machine, msgComp)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM, msgComp);
    }

    MachineServer machineServer = MachineServer(machine, sessionServer);
    machineServer.add(ServerUMS::getInstance()->getVishnuId());

    //To serialize the user object
    ::ecorecpp::serializer::serializer _ser;
    std::string machineSerializedUpdate = _ser.serialize_str(machine);

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), machineSerializedUpdate.c_str());
    diet_string_set(diet_parameter(pb,3), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS, machine->getMachineId());
  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), empty.c_str());
      diet_string_set(diet_parameter(pb,3), errorInfo.c_str());
  }
  delete machine;
  return 0;
}
/**
* \brief Function to solve the service solveMachineUpdate
* \fn    int solveMachineUpdate(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveMachineUpdate(diet_profile_t* pb) {

  std::string sessionKey;
  std::string machineSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), machineSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);

  Machine_ptr machine = NULL;

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_update_machine");
    mapper->code(machineSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(machineSerialized, machine)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    MachineServer machineServer = MachineServer(machine, sessionServer);
    machineServer.update();

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  delete machine;
  return 0;
}
/**
* \brief Function to solve the service solveMachineDelete
* \fn    int solveMachineDelete(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveMachineDelete(diet_profile_t* pb) {

  std::string sessionKey;
  std::string machineId;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), machineId);

  UMS_Data::Machine* machine = new UMS_Data::Machine();
  machine->setMachineId(machineId);

  SessionServer sessionServer = SessionServer(sessionKey);
  MachineServer machineServer = MachineServer(machine, sessionServer);

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_delete_machine");
    mapper->code(machineId, mapperkey);
    cmd = mapper->finalize(mapperkey);

    machineServer.deleteMachine();

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  delete machine;
  return 0;
}

/**
* \brief Function to solve the service solveLocalAccountCreate
* \fn    int solveLocalAccountCreate(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveLocalAccountCreate(diet_profile_t* pb) {
  std::string sessionKey;
  std::string laccountSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), laccountSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);

  LocalAccount_ptr localAccount = NULL;

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_add_local_account");
    mapper->code(laccountSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(laccountSerialized, localAccount)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    LocalAccountServer localAccountServer = LocalAccountServer(localAccount, sessionServer);
    localAccountServer.add();

    //OUT Parameters
    diet_string_set(diet_parameter(pb,2), localAccountServer.getPublicKey().c_str());
    diet_string_set(diet_parameter(pb,3), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameters
      diet_string_set(diet_parameter(pb,2), empty.c_str());
      diet_string_set(diet_parameter(pb,3), errorInfo.c_str());
  }
  delete localAccount;
  return 0;
}

/**
* \brief Function to solve the service solveLocalAccountUpdate
* \fn    int solveLocalAccountUpdate(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveLocalAccountUpdate(diet_profile_t* pb) {
  std::string sessionKey;
  std::string laccountSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), laccountSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);
  LocalAccount_ptr localAccount = NULL;

  try {

     //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_update_local_account");
    mapper->code(laccountSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(laccountSerialized, localAccount)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    LocalAccountServer localAccountServer = LocalAccountServer(localAccount, sessionServer);
    localAccountServer.update();

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  delete localAccount;
  return 0;
}

/**
* \brief Function to solve the service solveLocalAccountDelete
* \fn    int solveLocalAccountDelete(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveLocalAccountDelete(diet_profile_t* pb) {

  std::string sessionKey;
  std::string userId;
  std::string machineId;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), userId);
  diet_string_get(diet_parameter(pb,2), machineId);

  SessionServer sessionServer = SessionServer(sessionKey);
  UMS_Data::LocalAccount *localAccount = new UMS_Data::LocalAccount();
  localAccount->setUserId(userId);
  localAccount->setMachineId(machineId);

  LocalAccountServer localAccountServer = LocalAccountServer(localAccount, sessionServer);

  try {
     //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_delete_local_account");
    mapper->code(userId, mapperkey);
    mapper->code(machineId, mapperkey);
    cmd = mapper->finalize(mapperkey);

    localAccountServer.deleteLocalAccount();

    //OUT Parameter
    diet_string_set(diet_parameter(pb,3), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,3), errorInfo.c_str());
  }

  delete localAccount;
  return 0;
}


/**
* \brief Function to solve the service solveConfigurationSave
* \fn    int solveConfigurationSave(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveConfigurationSave(diet_profile_t* pb) {

  std::string sessionKey;
  std::string empty("");
  std::string configurationSerialized("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameter
  diet_string_get(diet_parameter(pb,0), sessionKey);

  SessionServer sessionServer = SessionServer(sessionKey);
  ConfigurationServer configurationServer = ConfigurationServer(sessionServer);

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_save_configuration");
    cmd = mapper->finalize(mapperkey);

    configurationServer.save();
    ::ecorecpp::serializer::serializer _ser;
    configurationSerialized =  _ser.serialize_str(configurationServer.getData());

    //OUT Parameters
    diet_string_set(diet_parameter(pb,1), configurationSerialized.c_str());
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameters
      diet_string_set(diet_parameter(pb,1), configurationSerialized.c_str());
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  return 0;
}

/**
* \brief Function to solve the service solveConfigurationRestore
* \fn    int solveConfigurationRestore(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveConfigurationRestore(diet_profile_t* pb) {

  std::string sessionKey;
  std::string configurationSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), configurationSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);
  Configuration_ptr configuration = NULL;

  try {

    std::string msgComp = "The file content is invalid";

    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_restore_configuration");
    mapper->code(configurationSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    if(!parseEmfObject(configurationSerialized, configuration, msgComp)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM, msgComp);
    }

    ConfigurationServer configurationServer = ConfigurationServer(configuration, sessionServer);
    configurationServer.restore(ServerUMS::getInstance()->getVishnuId());

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& e) {
      try {
          sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
          finishError =  fe.what();
          finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  return 0;
}


/**
* \brief Function to solve the service solveOptionValueSet
* \fn    int solveOptionValueSet(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveOptionValueSet(diet_profile_t* pb) {
  std::string sessionKey;
  std::string optionValueSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), optionValueSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);

  UMS_Data::OptionValue_ptr optionValue = NULL;

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_configure_option");
    mapper->code(optionValueSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(optionValueSerialized, optionValue)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    OptionValueServer optionValueServer = OptionValueServer(optionValue, sessionServer);
    optionValueServer.configureOption();

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  delete optionValue;
  return 0;
}

/**
* \brief Function to solve the service solveOptionValueSetDefault
* \fn    int solveOptionValueSetDefault(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveOptionValueSetDefault(diet_profile_t* pb) {
  std::string sessionKey;
  std::string optionValueSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), optionValueSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);
  UMS_Data::OptionValue_ptr optionValue = NULL;

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_configure_default_option");
    mapper->code(optionValueSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(optionValueSerialized, optionValue)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    OptionValueServer optionValueServer = OptionValueServer(optionValue, sessionServer);
    optionValueServer.configureOption(true);

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& e) {
      try {
          sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
          finishError =  fe.what();
          finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  delete optionValue;
  return 0;
}

/**
* \brief Function to solve the service solveGenerique
* \fn int solveGenerique(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
template <class QueryParameters, class List, class QueryType>
int
solveGenerique(diet_profile_t* pb) {

  std::string sessionKey;
  std::string optionValueSerialized;
  std::string listSerialized = "";
  std::string empty = "";
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), optionValueSerialized);

  SessionServer sessionServer  = SessionServer(sessionKey);

  QueryParameters* options = NULL;
  List* list = NULL;

  try {
    //To parse the object serialized
    if(!parseEmfObject(optionValueSerialized, options)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    QueryType query(options, sessionServer);

    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code(query.getCommandName());
    mapper->code(optionValueSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    list = query.list();

    ::ecorecpp::serializer::serializer _ser;
    listSerialized =  _ser.serialize_str(list);

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), listSerialized.c_str());
    diet_string_set(diet_parameter(pb,3), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& e) {
      try {
          sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
          finishError =  fe.what();
          finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), listSerialized.c_str());
      diet_string_set(diet_parameter(pb,3), errorInfo.c_str());
  }
  delete options;
  delete list;
  return 0;
}

/**
* \brief Function to solve the service solveListUsers
* \fn    int solveListUsers(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveListUsers(diet_profile_t* pb) {
  return solveGenerique<UMS_Data::ListUsersOptions, UMS_Data::ListUsers, ListUsersServer>(pb);
}

/**
* \brief Function to solve the service solveListMachines
* \fn int solveListMachines(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveListMachines(diet_profile_t* pb) {

  return solveGenerique<UMS_Data::ListMachineOptions, UMS_Data::ListMachines, ListMachinesServer>(pb);
}

/**
* \brief Function to solve the service solveListLocalAccount
* \fn int solveListLocalAccount(diet_profile_t*& pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveListLocalAccount(diet_profile_t* pb) {

  return solveGenerique<UMS_Data::ListLocalAccOptions, UMS_Data::ListLocalAccounts, ListLocalAccountsServer>(pb);
}

/**
* \brief Function to solve the service solveListOptions
* \fn int solveListOptions(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveListOptions(diet_profile_t* pb) {

  return solveGenerique<UMS_Data::ListOptOptions, UMS_Data::ListOptionsValues, ListOptionsValuesServer>(pb);
}
/**
* \brief Function to solve the service solveListHistoryCmd
* \fn int solveListHistoryCmd(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveListHistoryCmd(diet_profile_t* pb) {

  return solveGenerique<UMS_Data::ListCmdOptions, UMS_Data::ListCommands, ListCommandsServer>(pb);
}
/**
* \brief Function to solve the service solveListLocalAccount
* \fn int solveListSessions(diet_profile_t*& pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveListSessions(diet_profile_t* pb) {

  return solveGenerique<UMS_Data::ListSessionOptions, UMS_Data::ListSessions, ListSessionsServer>(pb);
}


/**
* \brief Function to solve the service solveRestore
* \fn    int solveRestore(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveRestore(diet_profile_t* pb) {

  std::string sqlcode;
  std::string errorInfo;
  diet_string_get(diet_parameter(pb,0), sqlcode);

  DbFactory factory;
  try {
    Database* db = factory.getDatabaseInstance();
    db->process(sqlcode);
  }
  catch (VishnuException& e) {
    errorInfo =  e.buildExceptionString();
  }
  diet_string_set(diet_parameter(pb,1), errorInfo.c_str());
  return 0;
}

/**
* \brief Function to solve the service solveSystemAuthCreate
* \fn    int solveSystemAuthCreate(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveSystemAuthCreate(diet_profile_t* pb) {
  std::string sessionKey;
  std::string authSystemSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), authSystemSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);

  AuthSystem_ptr authSystem = NULL;

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_add_auth_system");
    mapper->code(authSystemSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(authSystemSerialized, authSystem)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    AuthSystemServer authSystemServer(authSystem, sessionServer);
    authSystemServer.add(ServerUMS::getInstance()->getVishnuId());

    //To serialize the user object
    ::ecorecpp::serializer::serializer _ser;
    std::string authSystemSerializedUpdate = _ser.serialize_str(authSystem);

    //OUT Parameters
    diet_string_set(diet_parameter(pb,2), authSystemSerializedUpdate.c_str());
    diet_string_set(diet_parameter(pb,3), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameters
      diet_string_set(diet_parameter(pb,2), empty.c_str());
      diet_string_set(diet_parameter(pb,3), errorInfo.c_str());
  }
  delete authSystem;
  return 0;
}

/**
* \brief Function to solve the service solveSystemAuthUpdate
* \fn    int solveSystemAuthUpdate(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveSystemAuthUpdate(diet_profile_t* pb) {
  std::string sessionKey;
  std::string authSystemSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), authSystemSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);
  AuthSystem_ptr authSystem = NULL;

  try {

     //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_update_auth_system");
    mapper->code(authSystemSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(authSystemSerialized, authSystem)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    AuthSystemServer authSystemServer(authSystem, sessionServer);
    authSystemServer.update();

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  delete authSystem;
  return 0;
}

/**
* \brief Function to solve the service solveSystemAuthDelete
* \fn    int solveSystemAuthDelete(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveSystemAuthDelete(diet_profile_t* pb) {
  std::string sessionKey;
  std::string authSystemId;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), authSystemId);

  UMS_Data::AuthSystem_ptr authSystem = new UMS_Data::AuthSystem();
  authSystem->setAuthSystemId(authSystemId);

  SessionServer sessionServer = SessionServer(sessionKey);
  AuthSystemServer authSystemServer (authSystem, sessionServer);

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_delete_auth_system");
    mapper->code(authSystemId, mapperkey);
    cmd = mapper->finalize(mapperkey);

    authSystemServer.deleteAuthSystem();

    //OUT Parameter
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  delete authSystem;
  return 0;
}

/**
* \brief Function to solve the service solveSystemAuthList
* \fn    int solveSystemAuthList(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveSystemAuthList(diet_profile_t* pb) {

  return solveGenerique<UMS_Data::ListAuthSysOptions, UMS_Data::ListAuthSystems, ListAuthSystemsServer>(pb);
}

/**
* \brief Function to solve the service solveAccountAuthCreate
* \fn    int solveAccountAuthCreate(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveAccountAuthCreate(diet_profile_t* pb) {
  std::string sessionKey;
  std::string accountSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), accountSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);

  AuthAccount_ptr authAccount = NULL;

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_add_auth_account");
    mapper->code(accountSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(accountSerialized, authAccount)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    AuthAccountServer authAccountServer(authAccount, sessionServer);
    authAccountServer.add();

    //OUT Parameters
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameters
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  delete authAccount;
  return 0;
}

/**
* \brief Function to solve the service solveAccountAuthUpdate
* \fn    int solveAccountAuthUpdate(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveAccountAuthUpdate(diet_profile_t* pb) {
  std::string sessionKey;
  std::string accountSerialized;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), accountSerialized);

  SessionServer sessionServer = SessionServer(sessionKey);

  AuthAccount_ptr authAccount = NULL;

  try {
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_update_auth_account");
    mapper->code(accountSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //To parse the object serialized
    if(!parseEmfObject(accountSerialized, authAccount)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }

    AuthAccountServer authAccountServer(authAccount, sessionServer);
    authAccountServer.update();

    //OUT Parameters
    diet_string_set(diet_parameter(pb,2), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameters
      diet_string_set(diet_parameter(pb,2), errorInfo.c_str());
  }
  delete authAccount;
  return 0;
}

/**
* \brief Function to solve the service solveAccountAuthDelete
* \fn    int solveAccountAuthDelete(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveAccountAuthDelete(diet_profile_t* pb) {
  std::string sessionKey;
  std::string userId;
  std::string authSystemId;
  std::string empty("");
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), authSystemId);
  diet_string_get(diet_parameter(pb,2), userId);

  SessionServer sessionServer = SessionServer(sessionKey);
  UMS_Data::AuthAccount *authAccount = new UMS_Data::AuthAccount();
  authAccount->setUserId(userId);
  authAccount->setAuthSystemId(authSystemId);

  AuthAccountServer authAccountServer = AuthAccountServer(authAccount, sessionServer);

  try {
     //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(UMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_delete_auth_account");
    mapper->code(userId, mapperkey);
    mapper->code(authSystemId, mapperkey);
    cmd = mapper->finalize(mapperkey);

    authAccountServer.deleteAuthAccount();

    //OUT Parameter
    diet_string_set(diet_parameter(pb,3), empty.c_str());
    //To save the connection
    sessionServer.finish(cmd, UMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& e) {
      try {
        sessionServer.finish(cmd, UMS, vishnu::CMDFAILED);
      } catch (VishnuException& fe) {
        finishError =  fe.what();
        finishError +="\n";
      }
      e.appendMsgComp(finishError);
      errorInfo =  e.buildExceptionString();
      //OUT Parameter
      diet_string_set(diet_parameter(pb,3), errorInfo.c_str());
  }

  delete authAccount;
  return 0;
}

/**
* \brief Function to solve the service solveAccountAuthList
* \fn    int solveAccountAuthList(diet_profile_t* pb)
* \param pb is a structure which corresponds to the descriptor of a profile
* \return raises an exception on error
*/
int
solveAccountAuthList(diet_profile_t* pb) {

  return solveGenerique<UMS_Data::ListAuthAccOptions, UMS_Data::ListAuthAccounts, ListAuthAccountsServer>(pb);
}
