#include "TMSVishnuException.hpp"


TMSVishnuException::TMSVishnuException(const TMSVishnuException& e):UserException(e){
  mtype = VishnuException::TMS;
  initMsg();
}

TMSVishnuException::TMSVishnuException(int msg, std::string msgComp):UserException(msg, msgComp){
  mtype = VishnuException::TMS;
  initMsg();
}

TMSVishnuException::TMSVishnuException():UserException(){
  mtype = VishnuException::TMS;
  initMsg();
}

void
TMSVishnuException::initMsg(){

  mp.insert(std::pair<int, std::string>(ERRCODE_UNKNOWN_BATCH_SCHEDULER, std::string("The backend resource management system type is unknown")));
  mp.insert(std::pair<int, std::string>(ERRCODE_BATCH_SCHEDULER_ERROR, std::string("The backend resource management system indicates an error")));
  mp.insert(std::pair<int, std::string>(ERRCODE_UNKNOWN_JOBID, std::string("The job id is unknown")));
  mp.insert(std::pair<int, std::string>(ERRCODE_PERMISSION_DENIED, std::string("Permission denied")));
  mp.insert(std::pair<int, std::string>(ERRCODE_ALREADY_TERMINATED, std::string("The job is already terminated")));
  mp.insert(std::pair<int, std::string>(ERRCODE_ALREADY_CANCELED, std::string("The job is already canceled")));
  mp.insert(std::pair<int, std::string>(ERRCODE_JOB_IS_NOT_TERMINATED, std::string("The job is not terminated")));
  mp.insert(std::pair<int, std::string>(ERRCODE_ALREADY_DOWNLOADED, std::string("The job is already downloaded")));
  mp.insert(std::pair<int, std::string>(ERRCODE_UNKNOWN_WORKID, std::string("The work id is unknown")));
}
