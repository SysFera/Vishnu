/**
 * \file ConfigurationServer.cpp
 * \brief This file implements the Class which manipulates VISHNU configuration data on server side.
 * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
 * \date 31/01/2011
 */

#include <boost/format.hpp>
#include "ConfigurationServer.hpp"
#include "MachineServer.hpp"
#include "LocalAccountServer.hpp"
#include "AuthAccountServer.hpp"
#include "AuthSystemServer.hpp"
#include "DbFactory.hpp"

using namespace vishnu;

/**
 * \brief Constructor
 * \param session The object which encapsulates session data
 */
ConfigurationServer::ConfigurationServer(SessionServer session):msessionServer(session) {
  DbFactory factory;
  mdatabaseVishnu = factory.getDatabaseInstance();
  mconfiguration = NULL;

}
/**
 * \brief Constructor
 * \param configuration The Configuration data structure
 * \param session The object which encapsulates session data
 */
ConfigurationServer::ConfigurationServer(UMS_Data::Configuration*& configuration, SessionServer session)
  :mconfiguration(configuration), msessionServer(session) {
  DbFactory factory;
  mdatabaseVishnu = factory.getDatabaseInstance();
}

/**
 * \brief Function to save a VISHNU configuration
 * \return raises an exception on error
 */
int
ConfigurationServer::save() {

  std::string sqlListofUsers = "SELECT userid, pwd, firstname, lastname, privilege, email, status "
                               " FROM users "
                               " WHERE not userid='"+ROOTUSERNAME+"'";

  std::string sqlListofMachines = "SELECT machineid, name, site, status, lang, description"
                                  " FROM machine, description "
                                  " WHERE machine.nummachineid = description.machine_nummachineid";

  std::string sqlListofLocalAccount = "SELECT machineid, userid, aclogin, home "
                                      " FROM account, machine, users"
                                      " WHERE account.machine_nummachineid=machine.nummachineid "
                                      "  AND account.users_numuserid=users.numuserid";

  std::string sqlListofAuthSystems = "SELECT authsystemid, name, uri, authlogin, authpassword, "
                                     "       userpwdencryption, authtype, authsystem.status, ldapauthsystem.ldapbase"
                                     " FROM authsystem, ldapauthsystem "
                                     " WHERE ldapauthsystem.authsystem_authsystemid = authsystem.numauthsystemid";

  std::string sqlListofAuthAccounts = "SELECT authsystemid, userid, aclogin "
                                      " FROM authaccount, authsystem, users"
                                      " WHERE authaccount.authsystem_authsystemid=authsystem.numauthsystemid "
                                      "  AND authaccount.users_numuserid=users.numuserid";

  std::vector<std::string>::iterator ii;
  std::vector<std::string> results;
  UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
  mconfiguration= ecoreFactory->createConfiguration();

  //Creation of the object user
  UserServer userServer = UserServer(msessionServer);
  userServer.init();
  //if the user exists
  if (userServer.exist()) {
    //if the user is an admin
    if (userServer.isAdmin()) {
      //To get the list of users from the database
      boost::scoped_ptr<DatabaseResult> ListofUsers (mdatabaseVishnu->getResult(sqlListofUsers.c_str()));

      if (ListofUsers->getNbTuples() != 0){
        for (size_t i = 0; i < ListofUsers->getNbTuples(); ++i) {
          results.clear();
          results = ListofUsers->get(i);
          ii = results.begin();

          UMS_Data::User_ptr user = ecoreFactory->createUser();
          user->setUserId(*ii);
          user->setPassword(*(++ii));
          user->setFirstname(*(++ii));
          user->setLastname(*(++ii));
          user->setPrivilege(convertToInt(*(++ii)));
          user->setEmail(*(++ii));
          //Add 1 on status because of the storage of EMF litteral on file which is shifted
          user->setStatus(1+convertToInt(*(++ii)));
          mconfiguration->getListConfUsers().push_back(user);
        }
      }

      //To get the list of machines from the database
      boost::scoped_ptr<DatabaseResult> ListofMachines (mdatabaseVishnu->getResult(sqlListofMachines.c_str()));

      if (ListofMachines->getNbTuples() != 0){
        for (size_t i = 0; i < ListofMachines->getNbTuples(); ++i) {
          results.clear();
          results = ListofMachines->get(i);
          ii = results.begin();

          UMS_Data::Machine_ptr machine = ecoreFactory->createMachine();
          machine->setMachineId(*ii);
          machine->setName(*(++ii));
          machine->setSite(*(++ii));
          //Add 1 on status because of the storage of EMF litteral on file which is shifted
          machine->setStatus(1+convertToInt(*(++ii)));
          machine->setLanguage(*(++ii));
          machine->setMachineDescription(*(++ii));
          mconfiguration->getListConfMachines().push_back(machine);
        }
      }

      //To get the list of local accounts from the database
      boost::scoped_ptr<DatabaseResult> ListofLocalAccount (mdatabaseVishnu->getResult(sqlListofLocalAccount.c_str()));

      if (ListofLocalAccount->getNbTuples() != 0){
        for (size_t i = 0; i < ListofLocalAccount->getNbTuples(); ++i) {
          results.clear();
          results = ListofLocalAccount->get(i);
          ii = results.begin();

          UMS_Data::LocalAccount_ptr localAccount = ecoreFactory->createLocalAccount();
          localAccount->setMachineId(*ii);
          localAccount->setUserId(*(++ii));
          localAccount->setAcLogin(*(++ii));
          localAccount->setHomeDirectory(*(++ii));
          mconfiguration->getListConfLocalAccounts().push_back(localAccount);
        }
      }

      //To get the list of user-authentication systems from the database
      boost::scoped_ptr<DatabaseResult> ListofAuthSystems (mdatabaseVishnu->getResult(sqlListofAuthSystems.c_str()));

      if (ListofAuthSystems->getNbTuples() != 0){
        for (size_t i = 0; i < ListofAuthSystems->getNbTuples(); ++i) {
          results.clear();
          results = ListofAuthSystems->get(i);
          ii = results.begin();

          UMS_Data::AuthSystem_ptr authSystem = ecoreFactory->createAuthSystem();
          authSystem->setAuthSystemId(*ii);
          authSystem->setName(*(++ii));
          authSystem->setURI(*(++ii));
          authSystem->setAuthLogin(*(++ii));
          authSystem->setAuthPassword(*(++ii));
          //Add 1 for all enum types because of the storage of EMF litteral on file which is shifted
          authSystem->setUserPasswordEncryption(1+convertToInt(*(++ii)));
          authSystem->setType(1+convertToInt(*(++ii)));
          authSystem->setStatus(1+convertToInt(*(++ii)));
          authSystem->setLdapBase(*(++ii));
          mconfiguration->getListConfAuthSystems().push_back(authSystem);
        }
      }

      //To get the list of user-authentication systems from the database
      boost::scoped_ptr<DatabaseResult> ListofAuthAccounts (mdatabaseVishnu->getResult(sqlListofAuthAccounts.c_str()));

      if (ListofAuthAccounts->getNbTuples() != 0){
        for (size_t i = 0; i < ListofAuthAccounts->getNbTuples(); ++i) {
          results.clear();
          results = ListofAuthAccounts->get(i);
          ii = results.begin();

          UMS_Data::AuthAccount_ptr authAccount = ecoreFactory->createAuthAccount();
          authAccount->setAuthSystemId(*ii);
          authAccount->setUserId(*(++ii));
          authAccount->setAcLogin(*(++ii));
          mconfiguration->getListConfAuthAccounts().push_back(authAccount);
        }
      }
    } //End if the user is an admin
    else {
      UMSVishnuException e (ERRCODE_NO_ADMIN);
      throw e;
    }
  }//End //if the user exists
  else {
    UMSVishnuException e (ERRCODE_UNKNOWN_USER);
    throw e;
  }
  return 0;
}

/**
 * \brief Function to restore a VISHNU configuration
 * \param vishnuId The identifier of the vishnu instance
 * \return raises an exception on error
 */
int ConfigurationServer::restore(int vishnuId) {
  std::string sqlcode = "";
  std::string sqlCodeDescMachine = "";
  std::string sqlcodeAuthSystem = "";
  std::string sqlcodeLdapAuthSystem = "";
  std::string cleanAllModelInfo  = "DELETE FROM parameter_value;"
                                   "DELETE FROM work; "
                                   "DELETE FROM project_machine;"
                                   "DELETE FROM user_role; "
                                   "DELETE FROM project_role_permissions;"
                                   "DELETE FROM project_member_project_role; "
                                   "DELETE FROM project_member; "
                                   "DELETE FROM project_role;"
                                   "DELETE FROM project_application; "
                                   "DELETE FROM notification;"
                                   "DELETE FROM application_parameter; "
                                   "DELETE FROM application_version; "
                                   "DELETE FROM application; "
                                   "DELETE FROM project; "
                                   "DELETE FROM acl_entry;"
                                   "DELETE FROM acl_object_identity; "
                                   "DELETE FROM acl_class; "
                                   "DELETE FROM acl_sid; "
                                   "DELETE FROM role; "
                                   "DELETE FROM global_project_role_permissions;"
                                   "DELETE FROM global_project_role; "
                                   "DELETE FROM permission; "
                                   "DELETE FROM test_report; "
                                   "DELETE FROM job; "
                                   "DELETE FROM permission_module; ";

  //Creation of the object user
  UserServer userServer = UserServer(msessionServer);
  userServer.init();
  //if the userid is the super vishnu admin userid
  if (userServer.getData().getUserId().compare(ROOTUSERNAME) == 0) {
    //if the user exists
    if (userServer.exist()) {

      mdatabaseVishnu->process(cleanAllModelInfo+
                               "DELETE FROM users WHERE not userid='"+ROOTUSERNAME+"';"
                               "DELETE FROM machine;"
                               "DELETE FROM account;"
                               "DELETE FROM authsystem; "
                               "DELETE FROM authaccount;");

      //To get all users
      for(unsigned int i = 0; i < mconfiguration->getListConfUsers().size(); i++) {
        UMS_Data::User_ptr user = mconfiguration->getListConfUsers().get(i);
        //userServer.add(user);
        sqlcode.append(userToSql(user, vishnuId));
      }

      //To get all machines
      for(unsigned int i = 0; i < mconfiguration->getListConfMachines().size(); i++) {
        UMS_Data::Machine_ptr machine = mconfiguration->getListConfMachines().get(i);
        sqlcode.append(machineToSql(machine, vishnuId));
      }

      //To insert machines and users
      mdatabaseVishnu->process(sqlcode.c_str());

      //To get machines description
      for(unsigned int i = 0; i < mconfiguration->getListConfMachines().size(); i++) {
        UMS_Data::Machine_ptr machine = mconfiguration->getListConfMachines().get(i);
        sqlCodeDescMachine.append(machineDescToSql(machine));
      }

      //To insert machines description
      mdatabaseVishnu->process(sqlCodeDescMachine.c_str());

      //To insert localAccount
      for(unsigned int i = 0; i < mconfiguration->getListConfLocalAccounts().size(); i++) {
        UMS_Data::LocalAccount_ptr localAccount = mconfiguration->getListConfLocalAccounts().get(i);
        LocalAccountServer localAccountServer = LocalAccountServer (localAccount, msessionServer);
        localAccountServer.add();
      }

      //To get all user-authentication systems
      for(unsigned int i = 0; i < mconfiguration->getListConfAuthSystems().size(); i++) {
        UMS_Data::AuthSystem_ptr authsystem = mconfiguration->getListConfAuthSystems().get(i);
        sqlcodeAuthSystem.append(authSystemToSql(authsystem, vishnuId));
      }

      //If authSystem has been defined
      if (!sqlcodeAuthSystem.empty()) {
        //To insert user-authentication systems
        mdatabaseVishnu->process(sqlcodeAuthSystem.c_str());

        //To get all ldap systems in a second time in order to be
        //sure that recording has been done before
        for(unsigned int i = 0; i < mconfiguration->getListConfAuthSystems().size(); i++) {
          UMS_Data::AuthSystem_ptr authsystem = mconfiguration->getListConfAuthSystems().get(i);
          sqlcodeLdapAuthSystem.append(ldapAuthSystemToSql(authsystem));
        }
        //If ldapsystem has been defined
        if (!sqlcodeLdapAuthSystem.empty()) {
          mdatabaseVishnu->process(sqlcodeLdapAuthSystem.c_str());
        }

        //To insert authAccount
        for(unsigned int i = 0; i < mconfiguration->getListConfAuthAccounts().size(); i++) {
          UMS_Data::AuthAccount_ptr authAccount = mconfiguration->getListConfAuthAccounts().get(i);
          AuthAccountServer authAccountServer = AuthAccountServer (authAccount, msessionServer);
          authAccountServer.add();
        }
      }
    } //End if the user exists
    else {
      UMSVishnuException e (ERRCODE_UNKNOWN_USER);
      throw e;
    }
  }//End if the userid is the super vishnu admin userid
  else {
    UMSVishnuException e (ERRCODE_ROOT_USER_ONLY);
    throw e;
  }
  return 0;
}

/**
 * \brief Destructor
*/
ConfigurationServer::~ConfigurationServer() {
  delete mconfiguration;
}
/**
 * \brief Function to get Configuration data structure
 * \return  The LocalAccount data structure
 */
UMS_Data::Configuration*
ConfigurationServer::getData() {
  return mconfiguration;
}

/**
 * \brief Function to get the sql code of users from a VISHNU configuration
 * \param vishnuId The identifier of the vishnu instance
 * \return the sql code containing the sql code of users
 */
std::string
ConfigurationServer::userToSql(UMS_Data::User_ptr user, int vishnuId) {

  std::string sqlInsert = (boost::format("INSERT INTO users (vishnu_vishnuid, userid, pwd, firstname, lastname,"
                                         " privilege, email, passwordstate, status)"
                                         " VALUES (%1%, '%2%', '%3%', '%4%', '%5%', %6%, '%7%', %8%, %9%);")
                           %vishnuId
                           %user->getUserId()
                           %user->getPassword()
                           %user->getFirstname()
                           %user->getLastname()
                           %user->getPrivilege()
                           %user->getEmail()
                           %vishnu::STATUS_ACTIVE
                           %convertToString(user->getStatus()-1)).str(); //Remove 1 on status because of EMF litteral storage
  return sqlInsert;
}

/**
 * \brief Function to get the sql code of machines from a VISHNU configuration
 * \param machine The machine object
 * \param vishnuId The identifier of the vishnu instance
 * \return the sql code containing the sql code of machines
 */
std::string
ConfigurationServer::machineToSql(UMS_Data::Machine_ptr machine, int vishnuId) {

  std::string sqlInsert = (boost::format("INSERT INTO machine (vishnu_vishnuid, name, site, machineid, status)"
                                         " VALUES (%1%, '%2%', '%3%', '%4%', '%5%');")
                           %vishnuId
                           %machine->getName()
                           %machine->getSite()
                           %machine->getMachineId()
                           %convertToString(machine->getStatus()-1)).str(); //Remove 1 on status because of EMF litteral storage


  return sqlInsert;
}

/**
 * \brief Function to get the sql code of machines description from a VISHNU configuration
 * \return the sql code containing the sql code of machines description
 */
std::string
ConfigurationServer::machineDescToSql(UMS_Data::Machine_ptr machine) {

  UMS_Data::Machine* machinetmp = new UMS_Data::Machine();
  MachineServer machineServer = MachineServer(machinetmp);
  std::string res;
  res = "insert into description (machine_nummachineid, lang, "
        "description) values "
        "("+machineServer.getAttribut("where machineid='"+machine->getMachineId()+"';")+","
        "'"+ machine->getLanguage()+"','"+machine->getMachineDescription()+"');";

  delete machinetmp;
  return res;
}

/**
 * \brief Function to get the sql code of user-authentication system from a VISHNU configuration
 * \param authSystem The authSystem object
 * \param vishnuId The identifier of the vishnu instance
 * \return the sql code containing the sql code of authentication systems
 */
std::string
ConfigurationServer::authSystemToSql(UMS_Data::AuthSystem_ptr authsystem, int vishnuId) {
  std::string sqlInsert= "insert into authsystem (vishnu_vishnuid, "
                         "authsystemid, name, uri, authlogin, authpassword, userpwdencryption, authtype, status) values ";
  //Remove 1 on enum types because of the storage of EMF litteral on file which is shifted of 1
  std::cerr << sqlInsert << "\n";
  return (sqlInsert + "(" + convertToString(vishnuId)+", "
          "'"+authsystem->getAuthSystemId()+"','"+authsystem->getName()+"','"
          + authsystem->getURI()+"','"+authsystem->getAuthLogin()+"', '"+
          authsystem->getAuthPassword() + "',"
          +convertToString(authsystem->getUserPasswordEncryption()-1)+ ","
          +convertToString(authsystem->getType()-1) +","
          +convertToString(authsystem->getStatus()-1)+");");

}

/**
 * \brief Function to get the sql code of machines description from a VISHNU configuration
 * \param authSystem The authSystem object
 * \return the sql code containing the sql code of authentication systems based on ldap
 */
std::string
ConfigurationServer::ldapAuthSystemToSql(UMS_Data::AuthSystem_ptr authsystem) {

  AuthSystemServer authSystemServer(authsystem);

  //If the Ldap base is defined and the type is ldap
  if ((authsystem->getLdapBase().size() != 0)
      //Remove 1 on enum types because of the storage of EMF litteral on file which is shifted of 1
      && ((authsystem->getType()-1) == LDAPTYPE) ) { // LDAP

    std::string numAuth = authSystemServer.getAttribut("where authsystemid='"+authsystem->getAuthSystemId()+"'");
    return (" insert into ldapauthsystem (authsystem_authsystemid, ldapbase) values "
            "("+numAuth+", '"+authsystem->getLdapBase()+"');");
  }

  return "";
}
