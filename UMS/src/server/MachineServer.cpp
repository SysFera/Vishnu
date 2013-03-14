/**
* \file MachineServer.cpp
* \brief This file implements the Class which manipulates VISHNU machine data on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/

#include "MachineServer.hpp"
#include "DbFactory.hpp"
#include "utilVishnu.hpp"
#include "utilServer.hpp"
#include <boost/format.hpp>


using namespace vishnu;

/**
* \brief Constructor
* \fn MachineServer(UMS_Data::Machine*& machine)
* \param machine The machine data structure
*/
MachineServer::MachineServer(UMS_Data::Machine*& machine):
mmachine(machine)
{
  DbFactory factory;
  mdatabaseVishnu = factory.getDatabaseInstance();
}

/**
* \brief Constructor
* \fn MachineServer(UMS_Data::Machine*& machine, SessionServer& session)
* \param machine The machine data structure
* \param session The object which encapsulates session data
*/
MachineServer::MachineServer(UMS_Data::Machine*& machine, SessionServer& session):
mmachine(machine), msessionServer(session)
{
  DbFactory factory;
  mdatabaseVishnu = factory.getDatabaseInstance();
}

/**
* \brief Function to add a new VISHNU machine
* \fn int add(int vishnuId)
* \param vishnuId The identifier of the vishnu instance
* \return raises an exception on error
*/
int
MachineServer::add(int vishnuId) {
  std::string sqlUpdate = "update machine set ";
  std::string idMachineGenerated;

  UserServer userServer = UserServer(msessionServer);
  userServer.init();

  //if the user exists
  if (userServer.exist()) {
    //if the user is an admin
    if (userServer.isAdmin()) {
      //Generation of machineid
      idMachineGenerated = vishnu::getObjectId(vishnuId,
                                               "formatidmachine",
                                               MACHINE,
                                               mmachine->getName());

      //if the machine id is generated
      if (idMachineGenerated.size() != 0) {
        mmachine->setMachineId(idMachineGenerated);

        //if the machineId does not exist
        if (getAttribut("where machineid='"+mmachine->getMachineId()+"'","count(*)") == "1") {
          //To active the machine status
          mmachine->setStatus(ACTIVE_STATUS);

          sqlUpdate+="name='"+mmachine->getName()+"',";
          sqlUpdate+="site='"+mmachine->getSite()+"',";
          sqlUpdate+="status="+convertToString(mmachine->getStatus())+",";
          sqlUpdate+="sshpublickey='"+mmachine->getSshPublicKey()+"' ";
          sqlUpdate+="where machineid='"+mmachine->getMachineId()+"';";
          mdatabaseVishnu->process(sqlUpdate);

          mdatabaseVishnu->process("insert into description (machine_nummachineid, lang, description) values ("+getAttribut("where machineid='"+mmachine->getMachineId()+"'")+",'"+ mmachine->getLanguage()+"','"+mmachine->getMachineDescription()+"')");

        }//if the machine id is generated
        else {
          SystemException e (ERRCODE_SYSTEM, "There is a problem to parse the formatidmachine");
          throw e;
        }
      }//END if the formatidmachine is defined
      else {
        SystemException e (ERRCODE_SYSTEM, "The formatidmachine is not defined");
        throw e;
      }
    } //End if the user is an admin
    else {
      UMSVishnuException e (ERRCODE_NO_ADMIN);
      throw e;
    }
  }//End if the user exists
  else {
    UMSVishnuException e (ERRCODE_UNKNOWN_USER);
    throw e;
  }
  return 0;
} //END: add()

/**
* \brief Function to update a VISHNU machine
* \fn int update()
* \return raises an exception on error
*/
int
MachineServer::update() {

  std::string sqlCommand = "";



  UserServer userServer = UserServer(msessionServer);
  userServer.init();

  //if the user exists
  if (userServer.exist()) {
    //if the user is an admin
    if (userServer.isAdmin()) {

      //if the machine to update exists
      if (getAttribut("where machineid='"+mmachine->getMachineId()+"'").size() != 0) {

        //if a new machine name has been defined
        if (mmachine->getName().size() != 0) {
          sqlCommand.append("UPDATE machine SET name='"+mmachine->getName()+"'\
          where machineId='"+mmachine->getMachineId()+"';");
        }

        //if a new site has been defined
        if (mmachine->getSite().size() != 0) {
          sqlCommand.append("UPDATE machine SET site='"+mmachine->getSite()+"'\
          where machineId='"+mmachine->getMachineId()+"';");
        }

        //If a new status has been defined
        if (mmachine->getStatus() != UNDEFINED_VALUE) {
          sqlCommand.append("UPDATE machine SET status="+convertToString(mmachine->getStatus())+
          " where machineId='"+mmachine->getMachineId()+"';");
        }

        //if a new ssh public key has been defined
        if (mmachine->getSshPublicKey().size() != 0) {
          sqlCommand.append("UPDATE machine SET sshpublickey='"+mmachine->getSshPublicKey()+"'"
          " where machineId='"+mmachine->getMachineId()+"';");
        }

        //if a new language has been defined
        if (mmachine->getLanguage().size() != 0) {
          sqlCommand.append("UPDATE description SET lang='"+mmachine->getLanguage()+"'"
          " where machine_nummachineid='"+getAttribut("where machineid='"+mmachine->getMachineId()+"'")+"';");
        }

        //if a new machine description has been defined
        if (mmachine->getMachineDescription().size() != 0) {
          sqlCommand.append("UPDATE description SET description='"+mmachine->getMachineDescription()+"'"
          " where machine_nummachineid='"+getAttribut("where machineid='"+mmachine->getMachineId()+"'")+"';");
        }

        //If there is a change
        if (!sqlCommand.empty()) {
          mdatabaseVishnu->process(sqlCommand.c_str());
        }

      } //End if the machine to update exists
      else {
        UMSVishnuException e (ERRCODE_UNKNOWN_MACHINE);
        throw e;
      }

    } //End if the user is an admin
    else {
        UMSVishnuException e (ERRCODE_NO_ADMIN);
        throw e;
    }
  }//End if the user exists
  else {
    UMSVishnuException e (ERRCODE_UNKNOWN_USER);
    throw e;
  }
  return 0;
} //END: update()

/**
* \brief Function to delete a VISHNU machine
* \fn int deleteMachine()
* \return raises an exception on error
*/
int
MachineServer::deleteMachine() {

  UserServer userServer = UserServer(msessionServer);
  userServer.init();
  //if the user exists
  if (userServer.exist()) {
    //if the user is an admin
    if (userServer.isAdmin()) {
      //if the machine to update exists
      if (getAttribut("where machineid='"+mmachine->getMachineId()+"'").size() != 0) {
        mdatabaseVishnu->process("DELETE FROM machine where machineid='"+mmachine->getMachineId()+"'");
      } //End if the machine to update exists
      else {
        UMSVishnuException e (ERRCODE_UNKNOWN_MACHINE);
        throw e;
      }
    } //End if the user is an admin
    else {
      UMSVishnuException e (ERRCODE_NO_ADMIN);
      throw e;
    }
  }//End if the user exists
  else {
    UMSVishnuException e (ERRCODE_UNKNOWN_USER);
    throw e;
  }
  return 0;
} //END: deleteMachine()

/**
* \fn ~MachineServer()
* \brief Destructor
*/
MachineServer::~MachineServer() {
}

/**
* \brief Function to get machine information
* \fn UMS_Data::Machine* getData()
* \return  The user data structure
*/
UMS_Data::Machine*
MachineServer::getData() {
  return mmachine;
}

/**
* \brief Function to get machine information from the database vishnu
* \fn getAttribut(std::string condition, std::string attrname);
* \param condition The condition of the select request
* \param attrname the name of the attribut to get
* \return the value of the attribut or empty string if no results
*/

std::string
MachineServer::getAttribut(std::string condition, std::string attrname) {

  std::string sqlCommand("SELECT "+attrname+" FROM machine "+condition);
  boost::scoped_ptr<DatabaseResult> result(mdatabaseVishnu->getResult(sqlCommand.c_str()));
  return result->getFirstElement();
}

/**
* \brief Function to get the content of the public ssh key
* \fn std::string getPublicKey()
* \return The content of the ssh public key
*/
std::string
MachineServer::getPublicKey() {
  return msshpublickey;
}

/**
* \brief Function to get the machine
* \return The name of the machine
*/
std::string
MachineServer::getMachineName() {

  std::string  machineName = getAttribut("where machineid='"+getData()->getMachineId()+"'", "name");

  return machineName;
}

/**
* \brief Function to check the machineId
* \return raises an exception
*/
void MachineServer::checkMachine() {

  if(getAttribut("where machineid='"+mmachine->getMachineId()+"'").empty()){
    throw UMSVishnuException(ERRCODE_UNKNOWN_MACHINE,
                             (boost::format("The machine id %1% does not exist")%mmachine->getMachineId()).str());
  }
  if(getAttribut("where status=1 and  machineid='"+mmachine->getMachineId()+"'").size() == 0) {
    throw UMSVishnuException(ERRCODE_MACHINE_LOCKED);
  }
}
