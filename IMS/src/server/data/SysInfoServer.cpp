#include "SysInfoServer.hpp"

#include <string>
#include <vector>

#include "DbFactory.hpp"
#include "IMSVishnuException.hpp"

SysInfoServer::SysInfoServer(const UserServer session):msession(session) {
  DbFactory factory;
  mdatabase = factory.getDatabaseInstance();
  mvishnuId = 1;
}

SysInfoServer::SysInfoServer(const UserServer session, IMS_Data::SysInfoOp op):msession(session)  {
  DbFactory factory;
  mdatabase = factory.getDatabaseInstance();
  mop = op;
  mvishnuId = 1;
}

SysInfoServer::~SysInfoServer() {
}

IMS_Data::ListSysInfo_ptr
SysInfoServer::getSysInfo() {
  std::string req = "SELECT diskspace, machineid, memory from machine WHERE vishnu_vishnuid='"+convertToString(mvishnuId)+"'";
  std::vector<std::string> results = std::vector<std::string>();
  std::vector<std::string>::iterator iter;

  if(mop.getMachineId().compare("")) {
    std::string reqnmid = "SELECT nummachineid from machine where  machineid ='"+mop.getMachineId()+"'";
    boost::scoped_ptr<DatabaseResult> result(mdatabase->getResult(reqnmid.c_str()));
    if(result->getNbTuples() == 0) {
      throw IMSVishnuException(ERRCODE_INVPROCESS, "Unknown machine id");
    }
    req += " AND  machineid ='"+mop.getMachineId()+"'";
  }
  IMS_Data::IMS_DataFactory_ptr ecoreFactory = IMS_Data::IMS_DataFactory::_instance();
  IMS_Data::ListSysInfo_ptr mlistObject = ecoreFactory->createListSysInfo();

  try {
    boost::scoped_ptr<DatabaseResult> result(mdatabase->getResult(req.c_str()));
      for (size_t i = 0; i < result->getNbTuples(); i++){
	results.clear();
	results = result->get(i);
	iter = results.begin();
	IMS_Data::SystemInfo_ptr sys = ecoreFactory->createSystemInfo();
        if ((*(iter)).empty()) {
          sys->setDiskSpace(-1);
        } else {
          sys->setDiskSpace(convertToInt(*(iter)));
        }
        if ((*(iter+2)).empty()) {
          sys->setMemory(-1);
        } else {
          sys->setMemory(convertToInt(*(iter+2)));
        }
	sys->setMachineId(*(iter+1));
	mlistObject->getSysInfo().push_back(sys);
      }
  } catch (SystemException& e) {
    throw (e);
  }
  return mlistObject;
}

void
SysInfoServer::setSysInfo(IMS_Data::SystemInfo_ptr sys) {
  bool added = false;
  if (!msession.isAdmin()){
    throw UMSVishnuException(ERRCODE_NO_ADMIN, "set system info is an admin function. A user cannot call it");
  }
  // No update needed
  if (sys->getMemory()==0 && sys->getDiskSpace()==0) {
    return;
  }
  if (sys->getMachineId().compare("")==0) {
    throw UserException(ERRCODE_INVALID_PARAM, "Error missing the machine id. ");
  }
  std::string reqnmid = "SELECT nummachineid from machine where  machineid ='"+sys->getMachineId()+"'";
  boost::scoped_ptr<DatabaseResult> result(mdatabase->getResult(reqnmid.c_str()));
  if(result->getNbTuples() == 0) {
    throw IMSVishnuException(ERRCODE_INVPROCESS, "Unknown machine id");
  }

  std::string request = "update machine set ";
  if (sys->getDiskSpace() < 0 || sys->getMemory() < 0) {
    throw UserException(ERRCODE_INVALID_PARAM, "Invalid negative value");
  }
  if (sys->getDiskSpace()>0) {
    request += "  diskspace ="+convertToString(sys->getDiskSpace());
    added = true;
  }
  if (sys->getMemory()>0) {
    if (added) {
      request += ",";
    }
    request += "  memory ="+convertToString(sys->getMemory());
  }
  request += " where  machineid ='"+sys->getMachineId()+"'";

  request += " AND vishnu_vishnuid=";
  request += convertToString(mvishnuId);

  try{
    mdatabase->process(request.c_str());
  }catch(SystemException& e){
    e.appendMsgComp(" Error inserting new system states ");
    throw(e);
  }
}
