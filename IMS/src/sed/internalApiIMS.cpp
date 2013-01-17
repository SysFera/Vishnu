#include "internalApiIMS.hpp"
#include <exception>
#include "VishnuException.hpp"
#include "SystemException.hpp"
#include "IMSMapper.hpp"
#include "MapperRegistry.hpp"
#include <iostream>
#include "SessionServer.hpp"
#include <ecore.hpp> // Ecore metamodel
#include <ecorecpp.hpp> // EMF4CPP utils
#include "IMS_Data.hpp"
#include "data/ProcessServer.hpp"
#include "data/MetricServer.hpp"
#include "data/ObjectIdServer.hpp"
#include "data/SysInfoServer.hpp"
#include "data/ThresholdServer.hpp"
#include "controller/process/ProcessCtl.hpp"
#include "data/ExportServer.hpp"
#include "data/ExportFactory.hpp"

using namespace std;
using namespace vishnu;

int
solveExport(diet_profile_t* pb){

  string sessionKey;
  string oldSessionId;
  string filename ;
  string options ;
  string content;
  int mapperkey;
  string cmd;
  string error;
  string retErr = "";

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), oldSessionId);
  diet_string_get(diet_parameter(pb,2), filename);
  diet_string_get(diet_parameter(pb,3), options);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  IMS_Data::ExportOp_ptr expOp = NULL;

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_export_commands");
    mapper->code(string(oldSessionId), mapperkey);
    mapper->code(string(filename), mapperkey);
    mapper->code(string(options), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Getting options
    if(!parseEmfObject(string(options), expOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_export: Curent restart option object is not well built");
    }
    // Creating the process server with the options
    ExportServer* exp = ExportFactory::getExporter(userServer, expOp);

    // Exporting and setting the results in content
    exp->exporte(oldSessionId, content);

    // Setting out diet param
    diet_string_set(diet_parameter(pb,4), content.c_str());
    diet_string_set(diet_parameter(pb,5), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);
  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,4), "");
    diet_string_set(diet_parameter(pb,5), retErr.c_str());
  }
  if (expOp) {
    delete expOp;
  }
  return 0;
}

int
solveCurMetric(diet_profile_t* pb){
  string sessionKey  ;
  string curOpSer;
  string mid;
  string curSer;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), mid);
  diet_string_get(diet_parameter(pb,2), curOpSer);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  IMS_Data::CurMetricOp_ptr curOp = NULL;

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_metric_current_value");
    mapper->code(string(mid), mapperkey);
    mapper->code(string(curOpSer), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Getting options
    if(!parseEmfObject(string(curOpSer), curOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_getCurentMetricValue: Curent metric option object is not well built");
    }
    // Creating the process server with the options
    MetricServer met(userServer, curOp, string(""));

    // Listing the old metric
    IMS_Data::ListMetric* res;
    res = met.getCurMet();
    // Serializing the results
    ::ecorecpp::serializer::serializer _ser;
    curSer = _ser.serialize_str(const_cast<IMS_Data::ListMetric_ptr>(res));

    // Setting out diet param
    diet_string_set(diet_parameter(pb,3), curSer.c_str());
    diet_string_set(diet_parameter(pb,4), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);
  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,3), "");
    diet_string_set(diet_parameter(pb,4), retErr.c_str());

  }
  if (curOp) {
    delete curOp;
  }
  return 0;
}

int
solveOldMetric(diet_profile_t* pb){
  string sessionKey  ;
  string histOpSer;
  string mid;
  string histSer;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), mid);
  diet_string_get(diet_parameter(pb,2), histOpSer);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  IMS_Data::MetricHistOp_ptr histOp = NULL;

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_metric_history");
    mapper->code(string(mid), mapperkey);
    mapper->code(string(histOpSer), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Getting options
    if(!parseEmfObject(string(histOpSer), histOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_getMetricHistory: Metric history option object is not well built");
    }
    // Creating the process server with the options
    MetricServer met(userServer, histOp, string(""));

    // Listing the old metric
    IMS_Data::ListMetric* res;
    res = met.getHistMet(string(mid));

    // Serializing the results
    ::ecorecpp::serializer::serializer _ser;
    histSer = _ser.serialize_str(const_cast<IMS_Data::ListMetric_ptr>(res));

    // Setting out diet param
    diet_string_set(diet_parameter(pb,3), histSer.c_str());
    diet_string_set(diet_parameter(pb,4), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,3), "");
    diet_string_set(diet_parameter(pb,4), retErr.c_str());

  }
  if (histOp) {
    delete histOp;
  }
  return 0;
}

int
solvePS(diet_profile_t* pb){
  string sessionKey  ;
  string processOpSer;
  string processSer;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), processOpSer);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  IMS_Data::ProcessOp_ptr processOp = NULL;

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_processes");
    mapper->code(string(processOpSer), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Getting options
    if(!parseEmfObject(string(processOpSer), processOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_getProcesses: Process option object is not well built");
    }

    // Creating the process server with the options
    ProcessServer proc(processOp, userServer);

    // Listing the processes
    IMS_Data::ListProcesses* res;
    res = proc.list();

    // Serializing the results
    ::ecorecpp::serializer::serializer _ser;
    processSer = _ser.serialize_str(const_cast<IMS_Data::ListProcesses_ptr>(res));

    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), processSer.c_str());
    diet_string_set(diet_parameter(pb,3), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), "");
    diet_string_set(diet_parameter(pb,3), retErr.c_str());
  }
  if (processOp) {
    delete processOp;
  }
  return 0;
}

int
solveSetSysInfo(diet_profile_t* pb){
  string sessionKey  ;
  string sys;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;


  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), sys);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  IMS_Data::SystemInfo_ptr sysinf = NULL;
  try {
    // Getting options
    if(!parseEmfObject(string(sys), sysinf)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_setSysInfo: system info object is not well built");
    }
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_set_system_info");
    mapper->code(string(sys), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Creating the process server with the options
    SysInfoServer sysser(userServer);

    // Listing the old metric
    sysser.setSysInfo(sysinf);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), retErr.c_str());
  }
  if (sysinf) {
    delete sysinf;
  }
  return 0;
}

int
solveGetThreshold(diet_profile_t* pb){
  string sessionKey  ;
  string treeOpSer;
  string treeSer;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;
  std::string empty("");

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), treeOpSer);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  IMS_Data::ThresholdOp_ptr treeOp = NULL;

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_system_threshold");
    mapper->code(string(treeOpSer), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Getting options
    if(!parseEmfObject(string(treeOpSer), treeOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_getThreshold: threshold option object is not well built");
    }

    // Creating the process server with the options
    ThresholdServer tree(userServer, *treeOp);

    // Listing the processes
    IMS_Data::ListThreshold* res;
    res = tree.getThreshold();

    // Serializing the results
    ::ecorecpp::serializer::serializer _ser;
    treeSer = _ser.serialize_str(const_cast<IMS_Data::ListThreshold_ptr>(res));

    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), treeSer.c_str());
    diet_string_set(diet_parameter(pb,3), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters

    diet_string_set(diet_parameter(pb,2), empty.c_str());
    diet_string_set(diet_parameter(pb,3), retErr.c_str());
  }
  if (treeOp) {
    delete treeOp;
  }
  return 0;
}

int
solveGetUpFreq(diet_profile_t* pb){
  string sessionKey  ;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_update_frequency");
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Creating the process server with the options
    MetricServer met(userServer, string(""));

    // Listing the old metric
    int res;
    res = met.checkUpFreq();

    // Setting out diet param
    diet_string_set(diet_parameter(pb,1), convertToString(res).c_str());
    diet_string_set(diet_parameter(pb,2), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);
  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,1), "");
    diet_string_set(diet_parameter(pb,2), retErr.c_str());
  }
  return 0;
}

int
solveSetThreshold(diet_profile_t* pb){
  string sessionKey  ;
  string tree;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;


  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), tree);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  IMS_Data::Threshold_ptr treeinf = NULL;
  try {
    // Getting options
    if(!parseEmfObject(string(tree), treeinf)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_setThreshold: system info object is not well built");
    }
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_set_system_threshold");
    mapper->code(string(tree), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Creating the process server with the options
    ThresholdServer treeser(userServer);

    // Listing the old metric
    treeser.setThreshold(treeinf);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), retErr.c_str());
  }
  if (treeinf) {
    delete treeinf;
  }
  return 0;
}

int
solveSetUID(diet_profile_t* pb){
  string sessionKey  ;
  string fmt;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), fmt);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_define_user_identifier");
    mapper->code(string(fmt), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Creating the process server with the options
    ObjectIdServer ob(userServer);

    // Listing the old metric
    ob.setUID(fmt);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), retErr.c_str());
  }
  return 0;
}

int
solveSetJID(diet_profile_t* pb){
  string sessionKey  ;
  string fmt;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), fmt);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_define_job_identifier");
    mapper->code(string(fmt), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Creating the process server with the options
    ObjectIdServer ob(userServer);

    // Listing the old metric
    ob.setTID(fmt);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), retErr.c_str());
  }
  return 0;
}

int
solveSetTID(diet_profile_t* pb){
  string sessionKey  ;
  string fmt;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), fmt);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_define_transfer_identifier");
    mapper->code(string(fmt), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Creating the process server with the options
    ObjectIdServer ob(userServer);

    // Listing the old metric
    ob.setFID(fmt);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), retErr.c_str());
  }
  return 0;
}

int
solveSetMID(diet_profile_t* pb){
  string sessionKey  ;
  string fmt;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), fmt);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_define_machine_identifier");
    mapper->code(string(fmt), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Creating the process server with the options
    ObjectIdServer ob(userServer);

    // Listing the old metric
    ob.setMID(fmt);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), retErr.c_str());
  }
  return 0;
}

int
solveSetAID(diet_profile_t* pb){
  string sessionKey  ;
  string fmt;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), fmt);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_define_auth_identifier");
    mapper->code(string(fmt), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Creating the process server with the options
    ObjectIdServer ob(userServer);

    // Listing the old metric
    ob.setAID(fmt);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), retErr.c_str());
  }
  return 0;
}

int
solveSetWID(diet_profile_t* pb){
  string sessionKey  ;
  string fmt;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), fmt);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_define_work_identifier");
    mapper->code(string(fmt), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Creating the process server with the options
    ObjectIdServer ob(userServer);

    // Listing the old metric
    ob.setWID(fmt);
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), retErr.c_str());
  }
  return 0;
}

int
solveLoadShed(diet_profile_t* pb){
  string sessionKey  ;
  string mid ;
  string type;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;


  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), mid);
  diet_string_get(diet_parameter(pb,2), type);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_load_shed");
    mapper->code(string(mid), mapperkey);
    mapper->code(string(type), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Creating the process server with the options
    ProcessCtl proc(mid, userServer);

    // Load shedding
    proc.loadShed(convertToInt(std::string(type)));
    // Setting out diet param
    diet_string_set(diet_parameter(pb,3), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,3), retErr.c_str());
  }
  return 0;
}

int
solveSetUpFreq(diet_profile_t* pb){
  string sessionKey  ;
  string freq;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;


  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), freq);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_set_update_frequency");
    mapper->code(string(freq), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Creating the process server with the options
    MetricServer met(userServer, string(""));

    // Listing the old metric
    met.setUpFreq(convertToInt(string(freq)));
    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), retErr.c_str());
  }
  return 0;
}


int
solveRestart(diet_profile_t* pb){
  string sessionKey;
  string mid       ;
  string op        ;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), mid);
  diet_string_get(diet_parameter(pb,2), op);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  IMS_Data::SupervisorOp_ptr reOp = NULL;

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_restart");
    mapper->code(string(mid), mapperkey);
    mapper->code(string(op), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Getting options
    if(!parseEmfObject(string(op), reOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_restart: restart option object is not well built");
    }

    // Creating the process server with the options
    ProcessCtl ctl(string(mid), userServer);

    // Listing the old metric
    ctl.restart(reOp, mid);

    // Setting out diet param
    diet_string_set(diet_parameter(pb,3), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);
  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,3), retErr.c_str());
  }
  if (reOp) {
    delete reOp;
  }
  return 0;
}

int
solveStop(diet_profile_t* pb){
  string sessionKey;
  string mid       ;
  string op        ;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), mid);
  diet_string_get(diet_parameter(pb,2), op);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  IMS_Data::SupervisorOp_ptr opObj = NULL;

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_stop");
    mapper->code(string(mid), mapperkey);
    mapper->code(string(op), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Getting options
    if(!parseEmfObject(string(op), opObj)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_stop: stop option object is not well built");
    }

    // Creating the process server with the options
    ProcessCtl ctl(std::string(mid), userServer);

    // Listing the old metric
    ctl.stop(opObj);

    // Setting out diet param
    diet_string_set(diet_parameter(pb,3), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);
  } catch (VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,3), retErr.c_str());
  }
  if (opObj) {
    delete opObj;
  }
  return 0;
}

int
solveGetSysInfo(diet_profile_t* pb){
  string sessionKey  ;
  string sysOpSer;
  string sysSer;
  string error;
  string retErr = "";
  int mapperkey;
  string cmd;

  diet_string_get(diet_parameter(pb,0), sessionKey);
  diet_string_get(diet_parameter(pb,1), sysOpSer);

  SessionServer sessionServer = SessionServer(string(sessionKey));
  UserServer userServer = UserServer(sessionServer);
  IMS_Data::SysInfoOp_ptr sysOp = NULL;

  try {
    userServer.init();
    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(IMSMAPPERNAME);
    mapperkey = mapper->code("vishnu_get_system_info");
    mapper->code(string(sysOpSer), mapperkey);
    cmd = mapper->finalize(mapperkey);
    sessionServer.check();

    // Getting options
    if(!parseEmfObject(string(sysOpSer), sysOp)) {
      throw UserException(ERRCODE_INVALID_PARAM, "solve_getSysInfo: sys info option object is not well built");
    }

    // Creating the process server with the options
    SysInfoServer sys(userServer, *sysOp);

    // Listing the processes
    IMS_Data::ListSysInfo* res;
    res = sys.getSysInfo();

    // Serializing the results
    ::ecorecpp::serializer::serializer _ser;
    sysSer = _ser.serialize_str(const_cast<IMS_Data::ListSysInfo_ptr>(res));

    // Setting out diet param
    diet_string_set(diet_parameter(pb,2), sysSer.c_str());
    diet_string_set(diet_parameter(pb,3), retErr.c_str());

    // Finishing the command as a success
    sessionServer.finish(cmd, IMS, CMDSUCCESS);

  }catch(VishnuException& e){
    try{
      // Finishing the command as an error
      sessionServer.finish(cmd, IMS, CMDFAILED);
    }catch(VishnuException& fe){
      error = fe.what();
    }
    e.appendMsgComp(error);
    retErr = e.buildExceptionString();
    // Setting diet output parameters
    diet_string_set(diet_parameter(pb,2), "");
    diet_string_set(diet_parameter(pb,3), retErr.c_str());
  }
  if (sysOp) {
    delete sysOp;
  }
  return 0;
}
