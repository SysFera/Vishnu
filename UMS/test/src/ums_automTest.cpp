#include <boost/test/unit_test.hpp>

// EMF INCLUDE
//#include <ecore.hpp> // Ecore metamodel
//#include <ecorecpp.hpp> // EMF4CPP utils
// Generated code
#include "UMS_Data.hpp"
#include "UMS_Data_forward.hpp"
#include <iostream>
#include "UMS_fixtures.hpp"
#include "api_ums.hpp"
#include "diet_config_tests.h"
#include"DIET_client.h"
#include "UMS_test_utils.hpp"

//BOOST_AUTO_TEST_SUITE( test_suite )

BOOST_FIXTURE_TEST_SUITE( test_suite, UMSSeDFixture )
using namespace std;
using namespace UMS_Data;
using namespace vishnu;


BOOST_AUTO_TEST_CASE( my_test )
{
  int argc = 2;
  char* argv[argc];
  string dietClientConfigPath = CONFIG_DIR + string("/client_testing.cfg");
  argv[0]= (char*)"./automTest";
  argv[1]= (char*) dietClientConfigPath.c_str();
  if (diet_initialize(dietClientConfigPath.c_str(), argc, argv)) {
    BOOST_TEST_MESSAGE( "Error in diet_initialize... (using config: "
                        << dietClientConfigPath << ")" );
  }

  // CREATE DATA MODEL
  UMS_DataFactory_ptr ecoreFactory = UMS_DataFactory::_instance();
  UMS_DataPackage_ptr ecorePackage = UMS_DataPackage::_instance();

  string sqlScript = UMSSQLPATH;
  string umsAuthType = UMSAUTHENTYPE;

  ////
  // Parameters
  ////
  int i;
  // connect
  int                	  idl  = 4        ;
  string             	  key  = ""       ;
  string                  key2 = ""       ;

  string          pwd  = UMSADMINVISHNUPWD  ;
  string          uid  = UMSADMINVISHNULOGIN;

  string          pwdUMSDb  = "admin"  ;
  string          uidUMSDb  = "admin_1";

  string             	  sid  = "1"      ;
  string             	  sub  = ""       ;
  SessionCloseType   	  sct  = 1        ;
  ConnectOptions 	  cop  ;//= ecoreFactory->createConnectOptions();
  ListSessions_ptr   	  li   = ecoreFactory->createListSessions();
  ListSessionOptions      opt  ;//= ecoreFactory->createListSessionOptions();
  Session                 sess ;
  Session                 sess2 ;

  string 	     	  pwdu = UMSUSERVISHNUPWD;
  string 	     	  uidu = UMSUSERVISHNULOGIN;
  string          uiduUMSDb = "user_1";
  string          pwduUMSDb = "toto";

  string                  rootUMSDb= "root";
  string                  pwdrUMSDb = "vishnu_user";

  string                  root = UMSROOTVISHNULOGIN;
  string                  pwdr = UMSROOTVISHNUPWD;

  // connect as
  string const&      	  subs = "user_1";
  // user
  User_ptr           	  use  = ecoreFactory->createUser();
  PrivilegeType      	  pri  = 1         ;
  string             	  rec  = string("");
  string             	  cu   = "toto_1"  ;
  string             	  pass = "user_1"  ;
  string             	  fina = "toto"    ;
  string             	  lana = "dupont"  ;
  string             	  mail = "cl3m3ntlebgkidechyr@hotmail.fr";
  ListUsers_ptr      	  liu  = ecoreFactory->createListUsers();
  ListUsersOptions      liuo;
  // local account
  ListLocalAccounts_ptr   lia  = ecoreFactory->createListLocalAccounts();
  ListLocalAccOptions     lioa ;//= ecoreFactory->createListLocalAccOptions();
  LocalAccount            lacc ;//= ecoreFactory->createLocalAccount();
  string                  mid  = "machine_1" ;
  string                  accL = "toto"      ;
  string                  ssh  = "/usr/local";
  string                  home = "/home/toto";
  // machine
  ListMachines_ptr        lim  = ecoreFactory->createListMachines();
  ListMachineOptions      liom ;//= ecoreFactory->createListMachineOptions();
  Machine                 ma   ;//= ecoreFactory->createMachine();
  string                  maid = "machine_2";
  string                  mana = "ulysse"   ;
  string                  site = "paris"    ;
  string                  desc = "calcul"   ;
  string                  lang = "fr"       ;
  // Option value
  string                  oval = "42"     ;
  string                  ona  = "VISHNU_TIMEOUT"     ;
  OptionValue             opva ;//= ecoreFactory->createOptionValue();
  ListOptOptions          lioo ;//= ecoreFactory->createListOptOptions();
  ListOptionsValues_ptr   liov = ecoreFactory->createListOptionsValues();
  // Init
  string                  path = "/tmp/vishnu.cfg";
  // Command history
  ListCommands_ptr        lic  = ecoreFactory->createListCommands();
  ListCmdOptions          lico ;//= ecoreFactory->createListCmdOptions();
  // Configuration
  Configuration           conf ;//= ecoreFactory->createConfiguration();

  // auth account
  ListAuthAccounts_ptr    liaa  = ecoreFactory->createListAuthAccounts();
  ListAuthAccOptions      liaao;//= ecoreFactory->createListLocalAccOptions();
  AuthAccount             aacc ;//= ecoreFactory->createLocalAccount();

  // auth system
  ListAuthSystems_ptr     lias  = ecoreFactory->createListAuthSystems();
  ListAuthSysOptions      liaso;//= ecoreFactory->createListLocalAccOptions();
  AuthSystem              asys ;//= ecoreFactory->createLocalAccount();
  string authsysid;

// list user to connect
  ListUsers_ptr      	  liuc  = ecoreFactory->createListUsers();


  string np;
  // Setting value
  cop.setClosePolicy(sct);
  cop.setSessionInactivityDelay(idl);
  cop.setSubstituteUserId(sub);

  ///////////
  // TESTS //
  ///////////
  BOOST_REQUIRE(restore    (sqlScript+"/cleanall.sql")==0);

  BOOST_REQUIRE(restore    (sqlScript+"/UMSinitTest.sql")==0);

try {

  BOOST_MESSAGE(" UMS Authentication Type : "+ umsAuthType);

  if (umsAuthType.compare("UMS") != 0) {
    BOOST_REQUIRE(restore    (sqlScript+"/UMSinitAuthSystem.sql")==0);
  }

  // Connect normal call
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing normal connection U1-B1" );

  BOOST_CHECK  (connect    (uid, pwd, sess, cop )==0);
  BOOST_CHECK  (listSessions(sess.getSessionKey(), *li , opt      )==0);
  BOOST_MESSAGE("Sess.GetSessionKey() generated : " << sess.getSessionKey() );

  // Connect with bad uid
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing with bad uid U1-E1" );
  BOOST_CHECK_THROW  (connect    ("bad", pwd, sess, cop), VishnuException);
  BOOST_CHECK_THROW  (listSessions(sess.getSessionKey()  , *li , opt     ), VishnuException);

  // Connect with bad pwd
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing bad pwd U1-E2");
  BOOST_CHECK_THROW  (connect    (uid, "bad", sess, cop), VishnuException);
  BOOST_CHECK_THROW  (listSessions(sess.getSessionKey(), *li   , opt     ), VishnuException);

  //BOOST_CHECK  (connect      (uidu, pwdu, sess, cop )==0);
//  // Connect with timeout
//  sct = 0;
//  cop.setClosePolicy(sct);
//  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
//  BOOST_MESSAGE(" Testing timeout U1.1-B1" );
//  BOOST_CHECK  (connect    (uid, pwd, sess, cop )==0);
//  sleep(10);
//  BOOST_CHECK_THROW  (listSessions(sess.getSessionKey(), *li , opt      ), VishnuException);

  // Connect with bad uid
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing with bad uid U1.1-E1" );
  BOOST_CHECK_THROW  (connect    ("bad", pwd, sess, cop), VishnuException);
  BOOST_CHECK_THROW  (listSessions(sess.getSessionKey()  , *li , opt     ), VishnuException);

  // Connect with bad pwd
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing bad pwd U1.1-E2");
  BOOST_CHECK_THROW  (connect    (uid, "bad", sess, cop), VishnuException);
  BOOST_CHECK_THROW  (listSessions(sess.getSessionKey(), *li   , opt     ), VishnuException);

  // Connect with bad closure policy
  sct = 3;
  cop.setClosePolicy(sct);
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing unknown closure mode U1.1-E3");
  BOOST_CHECK_THROW  (connect(uid, pwd, sess, cop ), VishnuException);
  sct = 0;
  cop.setClosePolicy(sct);

  if (umsAuthType.compare("LDAP") != 0) {
    // Connect with a temporary password
    BOOST_MESSAGE(" Testing temporary pwd U1.1-E4");
    BOOST_CHECK  (connect    (uid, pwd, sess, cop         )==0);
    BOOST_CHECK    (resetPassword(sess.getSessionKey(), uidUMSDb, np       )==0);
    BOOST_CHECK    (changePassword(uidUMSDb, np, pwdUMSDb       )==0);
    BOOST_CHECK  (listSessions(sess.getSessionKey(), *li , opt              )==0);
  }
  // Connect as an other user
  cop.setSubstituteUserId(subs);
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing another user session U1.1-E5");
  BOOST_CHECK  (connect    (uid, pwd, sess, cop         )==0);
  BOOST_CHECK  (listSessions(sess.getSessionKey(), *li , opt              )==0);
  cop = *(ecoreFactory->createConnectOptions());

  /*sct = 0;
  cop.setClosePolicy(sct);
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing connect on disconnect U1.1-B2" );
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  BOOST_CHECK(listSessions(sess.getSessionKey(), *li, opt)==0);*/

  //netrc's test setting values
  string homebefore = getenv("HOME");
  string netrcpath;

  // Connect with netrc normal call
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing normal connection using the .netrc file U1.1-B2" );
  BOOST_REQUIRE(setenv("HOME", CONFIG_DIR, 1)==0);
  netrcpath = string(getenv("HOME")) + "/.netrc";
  BOOST_REQUIRE (system(string("chmod 600 "+ netrcpath).c_str()) != -1);
  BOOST_CHECK  (connect    ("", "", sess, cop )==0);
  BOOST_CHECK  (listSessions(sess.getSessionKey(), *li , opt      )==0);
  BOOST_MESSAGE("Sess.GetSessionKey() generated : " << sess.getSessionKey() );
  BOOST_REQUIRE(setenv("HOME", homebefore.c_str(), 1)==0);

  // Connect with netrc file's bad path
  BOOST_MESSAGE(" Testing connection with bad netrc file path U1.1-E3" );
  BOOST_CHECK(setenv("HOME", "/tmp", 1)==0);
  BOOST_CHECK_THROW (connect("", "", sess, cop ), VishnuException);
  BOOST_REQUIRE(setenv("HOME", homebefore.c_str(), 1)==0);

  //Connect with netrc file's bad permission
  BOOST_MESSAGE(" Testing connection with bad netrc file permissions U1.1-E4" );
  BOOST_REQUIRE(setenv("HOME", CONFIG_DIR, 1)==0);
  netrcpath = string(getenv("HOME")) + "/.netrc";
  BOOST_REQUIRE (system(string("chmod 700 "+ netrcpath).c_str()) != -1);
  BOOST_CHECK_THROW (connect("", "", sess, cop ), VishnuException);
  BOOST_REQUIRE (system(string("chmod 600 "+ netrcpath).c_str()) != -1);
  BOOST_REQUIRE(setenv("HOME", homebefore.c_str(), 1)==0);

  //Connect with netrc file with no vishnu machine defined
  BOOST_MESSAGE(" Testing connection with no vishnu machine on netrc file U1.1-E5" );
  BOOST_REQUIRE(setenv("HOME", CONFIG_DIR, 1)==0);
  netrcpath = string(getenv("HOME")) + "/.netrc";
  BOOST_REQUIRE (system(string("chmod 600 "+ netrcpath).c_str()) != -1);
  replaceAllOccurences(netrcpath, "vishnu", "vishnu1");
  BOOST_CHECK_THROW (connect("", "", sess, cop ), VishnuException);
  BOOST_REQUIRE(setenv("HOME", homebefore.c_str(), 1)==0);
  replaceAllOccurences(netrcpath, "vishnu1", "vishnu");

  //Connect with .netrc file when the login is not defined
  std::string oldContent;
  BOOST_MESSAGE(" Testing connection with no login defined on netrc file U1.1-E6" );
  BOOST_REQUIRE(setenv("HOME", CONFIG_DIR, 1)==0);
  netrcpath = string(getenv("HOME")) + "/.netrc";
  BOOST_REQUIRE (system(string("chmod 600 "+ netrcpath).c_str()) != -1);
  addLineToFile(netrcpath, "machine vishnu password vishnu_user", oldContent);
  BOOST_CHECK_THROW (connect("", "", sess, cop ), VishnuException);
  BOOST_REQUIRE(setenv("HOME", homebefore.c_str(), 1)==0);
  putOnFile(netrcpath, oldContent);

  //Connect with .netrc file when the password is before the login
  BOOST_MESSAGE(" Testing connection with the password defined before the login on netrc file U1.1-E6" );
  BOOST_REQUIRE(setenv("HOME", CONFIG_DIR, 1)==0);
  netrcpath = string(getenv("HOME")) + "/.netrc";
  BOOST_REQUIRE (system(string("chmod 600 "+ netrcpath).c_str()) != -1);
  addLineToFile(netrcpath, "machine vishnu password vishnu_user login root", oldContent);
  BOOST_CHECK_THROW (connect("", "", sess, cop ), VishnuException);
  BOOST_REQUIRE(setenv("HOME", homebefore.c_str(), 1)==0);
  putOnFile(netrcpath, oldContent);

  //Connect with .netrc file when the password is not defined
  BOOST_MESSAGE(" Testing connection with no password defined on netrc file U1.1-E7" );
  BOOST_REQUIRE(setenv("HOME", CONFIG_DIR, 1)==0);
  netrcpath = string(getenv("HOME")) + "/.netrc";
  BOOST_REQUIRE (system(string("chmod 600 "+ netrcpath).c_str()) != -1);
  addLineToFile(netrcpath, "machine vishnu login root", oldContent);
  BOOST_CHECK_THROW (connect("", "", sess, cop ), VishnuException);
  BOOST_REQUIRE(setenv("HOME", homebefore.c_str(), 1)==0);
  putOnFile(netrcpath, oldContent);

  // Connect with a list of user
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing normal connection U1-B1" );
  User_ptr u1  = ecoreFactory->createUser();
  u1->setUserId   (uid)  ;
  u1->setPassword (pwd);
  liuc->getUsers().push_back(u1);
  BOOST_CHECK  (connect    (*liuc, sess, cop )==0);
  BOOST_CHECK  (listSessions(sess.getSessionKey(), *li , opt      )==0);
  BOOST_MESSAGE("Sess.GetSessionKey() generated : " << sess.getSessionKey() );

  // Connect with a list of user bad user
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing normal connection U1-B1" );
  liuc  = ecoreFactory->createListUsers();
  u1  = ecoreFactory->createUser();
  u1->setUserId   ("bad")  ;
  u1->setPassword (pass);
  liuc->getUsers().push_back(u1);
  BOOST_CHECK_THROW  (connect    (*liuc, sess, cop ), VishnuException);

  // Connect with a list of user bad pwd
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing normal connection U1-B1" );
  liuc  = ecoreFactory->createListUsers();
  u1  = ecoreFactory->createUser();
  u1->setUserId   (cu)  ;
  u1->setPassword ("bad");
  liuc->getUsers().push_back(u1);
  BOOST_CHECK_THROW  (connect    (*liuc, sess, cop ), VishnuException);


   // ReConnect normal call
   // -> connect
   BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
   BOOST_MESSAGE(" Testing normal reconnection U1.5-B-1" );
   BOOST_CHECK  (connect    (uid, pwd, sess, cop )==0);

   li   = ecoreFactory->createListSessions();

   BOOST_CHECK  (listSessions(sess.getSessionKey(), *li , opt      )==0);
   // -> and then reconnect normal
   if (li->getSessions().size() &&
       (li->getSessions())[0]){
     rec = li->getSessions()[0]->getSessionId();
     BOOST_CHECK(reconnect  (uid, pwd, rec, sess)==0);
     BOOST_CHECK(listSessions(sess.getSessionKey(), *li , opt     )==0);
   }else{
     BOOST_MESSAGE("FAILURE INVALID SESSION KEY TO RECONNECT");
  }

  // Reconnect with bad user id
  BOOST_REQUIRE(restore  (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing error uid reconnect U1.5-E1");
  BOOST_CHECK_THROW  (reconnect("bad", pwd, sid, sess), VishnuException);

  // Reconnect with bad password
  BOOST_REQUIRE(restore  (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing error pwd reconnect U1.5-E2");
  BOOST_CHECK_THROW  (reconnect(uid, "bad", sid, sess), VishnuException);

  // Test normal close
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing normal close U1.2B");
  BOOST_CHECK  (connect    (uid, pwd, sess, cop )==0);
  BOOST_CHECK  (listSessions(sess.getSessionKey(), *li , opt      )==0);
  BOOST_CHECK  (close      (sess.getSessionKey()                )==0);
  BOOST_CHECK_THROW  (listSessions(sess.getSessionKey(), *li,  opt      ), VishnuException);

  // Test close with bad sid
  BOOST_MESSAGE(" Testing close a bad session U1.2E1");
  BOOST_CHECK_THROW(close("toto"), VishnuException);

  // Test closing an already closed session
  BOOST_MESSAGE(" Testing close a closed session U1.2E2");
  BOOST_CHECK_THROW(close(sess.getSessionKey()), VishnuException);

  // Add user
  BOOST_MESSAGE(" Testing adding a user U4-B"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK(connect(uid, pwd, sess, cop)==0);
  use->setUserId   (cu)  ;
  use->setPassword (pass);
  use->setFirstname(fina);
  use->setLastname (lana);
  use->setPrivilege(pri) ;
  use->setEmail    (mail);
  BOOST_CHECK(addUser(sess.getSessionKey(), *use)==0);
  BOOST_CHECK(close        (sess.getSessionKey()     )==0);
//   // Login already in db
//   BOOST_MESSAGE(" Testing adding the same user twice U4-E"    );
//   BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
//   BOOST_CHECK	 (connect      (uid, pwd, sess, cop )==0);
//   BOOST_CHECK	 (addUser(sess.getSessionKey(), *use           )==0);
//   BOOST_CHECK_THROW	 (addUser(sess.getSessionKey(), *use           ), VishnuException);
//   BOOST_CHECK	 (close        (sess.getSessionKey()                )==0);

  // Not admin
  BOOST_MESSAGE(" Testing adding whereas not admin U4-E"    );
  BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK	 (connect      (uidu, pwdu, sess, cop )==0);
  BOOST_CHECK_THROW	 (addUser(sess.getSessionKey(), *use           ), VishnuException);
  BOOST_CHECK_THROW	 (addUser(sess.getSessionKey(), *use           ), VishnuException);
  BOOST_CHECK	 (close        (sess.getSessionKey()                )==0);

  // Add user bad email
  BOOST_MESSAGE(" Testing adding a user with a bad email U4-E"    );
  BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect      (uid, pwd, sess, cop )==0);
  use->setEmail("cl3m3ntlebgkidechyrhotmail.fr");
  BOOST_CHECK_THROW  (addUser(sess.getSessionKey(), *use           ), VishnuException);
  BOOST_CHECK  (close        (sess.getSessionKey()                )==0);
  use->setEmail(mail);

   // Update valid
  BOOST_MESSAGE(" Testing valid update user U4.1-B"    );
  BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect      (uid, pwd, sess, cop )==0);
  BOOST_CHECK  (addUser(sess.getSessionKey(), *use           )==0);
  use->setEmail("cl3m3ntlebgkidechyrGRAVE@hotmail.fr");
  BOOST_CHECK (updateUser   (sess.getSessionKey(), *use           )==0);
  use->setEmail(mail);
  BOOST_CHECK  (close        (sess.getSessionKey()                )==0);

  // Update not an admin
  BOOST_MESSAGE(" Testing valid update user U4.1-B"    );
  BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect      (uid, pwd, sess, cop )==0);
  BOOST_CHECK  (addUser(sess.getSessionKey(), *use           )==0);
  use->setEmail("cl3m3ntlebgkidechyrGRAVE@hotmail.fr");
  BOOST_CHECK  (connect      (uidu, pwdu, sess, cop )==0);
  BOOST_CHECK_THROW (updateUser   (sess.getSessionKey(), *use           ), VishnuException);
  use->setEmail(mail);
  BOOST_CHECK  (close        (sess.getSessionKey()                )==0);

  // Login invalid to update
  BOOST_MESSAGE(" Testing bad update parameter bad user id U4.1-E"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql"     )==0);
  BOOST_CHECK  (connect      (uid, pwd, sess, cop)==0);
  BOOST_CHECK	 (addUser(sess.getSessionKey(), *use	  )==0);
  use->setUserId("bad");
  BOOST_CHECK_THROW	 (updateUser   (sess.getSessionKey(), *use	  ), VishnuException);
  BOOST_CHECK	 (close        (sess.getSessionKey()               )==0);
  use->setUserId(cu);

  // Update user fails : bad email
  BOOST_MESSAGE(" Testing update a user with a bad email U4.1-E"    );
  BOOST_REQUIRE(restore   (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect   (uid, pwd, sess, cop )==0);
  use->setEmail("cl3m3ntlebgkidechyrhotmail.fr");
  BOOST_CHECK_THROW  (updateUser(sess.getSessionKey(), *use           ), VishnuException);
  BOOST_CHECK  (close     (sess.getSessionKey()                )==0);
  use->setEmail(mail);

  // Delete user
  BOOST_MESSAGE(" Testing delete normal U4.2B"    );
  BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK	 (connect      (uid, pwd, sess, cop )==0);
  use  = ecoreFactory->createUser();
  use->setUserId   (cu)  ;
  use->setPassword (pass);
  use->setFirstname(fina);
  use->setLastname (lana);
  use->setPrivilege(pri) ;
  use->setEmail    (mail);
  BOOST_CHECK	 (addUser(sess.getSessionKey(), *use	   )==0);
  BOOST_CHECK	 (deleteUser   (sess.getSessionKey(), use->getUserId() 	   )==0);
  BOOST_CHECK	 (close        (sess.getSessionKey()                )==0);

  // Delete user not admin
  BOOST_MESSAGE(" Testing delete normal U4.2B"    );
  BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK	 (connect      (uid, pwd, sess, cop )==0);
  use  = ecoreFactory->createUser();
  use->setUserId   (cu)  ;
  use->setPassword (pass);
  use->setFirstname(fina);
  use->setLastname (lana);
  use->setPrivilege(pri) ;
  use->setEmail    (mail);
  BOOST_CHECK	 (addUser(sess.getSessionKey(), *use	   )==0);
  BOOST_CHECK	 (connect      (uidu, pwdu, sess, cop )==0);
  BOOST_CHECK_THROW	 (deleteUser   (sess.getSessionKey(), use->getUserId() 	   ), VishnuException);
  BOOST_CHECK	 (close        (sess.getSessionKey()                )==0);

  // Delete user  bad uid
  BOOST_MESSAGE(" Testing delete bad uid U4.2E"    );
  BOOST_REQUIRE(restore   (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK	 (connect   (uid, pwd, sess, cop )==0);
  BOOST_CHECK_THROW	 (deleteUser(sess.getSessionKey(), cu            ), VishnuException);
  BOOST_CHECK	 (close     (sess.getSessionKey()                )==0);


  if (umsAuthType.compare("LDAP") != 0) {
    uid = uidUMSDb;
    pwd = pwdUMSDb;
    // Change pwd ok
    BOOST_MESSAGE(" Testing change password normal U1.3.3"    );
    BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql"       )==0);
    BOOST_CHECK	 (connect       (uid, pwd , sess, cop)==0);
    BOOST_CHECK	 (changePassword(uid , pwd, "newPwd")==0);
    BOOST_CHECK	 (changePassword(uid , "newPwd", pwd)==0);
    BOOST_CHECK	 (close         (sess.getSessionKey()                )==0);

    // Change pwd bad uid
    BOOST_MESSAGE(" Testing change password bad uid U1.3.3E"    );
    BOOST_REQUIRE(restore	(sqlScript+"/clean_session.sql"  )==0);
    BOOST_CHECK	 (connect	(uid  , pwd, sess, cop )==0);
    BOOST_CHECK	 (addUser (sess.getSessionKey()  , *use           )==0);
    BOOST_CHECK_THROW	 (changePassword("bad", pass, "newPwd"), VishnuException);
    BOOST_CHECK	 (close         (sess.getSessionKey()                  )==0);

    // Change pwd bad pwd
    BOOST_MESSAGE(" Testing change password bad pwd U1.3.3E"    );
    BOOST_REQUIRE(restore	(sqlScript+"/clean_session.sql")==0);
    BOOST_CHECK	 (connect	(uid, pwd , sess, cop)==0);
    BOOST_CHECK	 (addUser (sess.getSessionKey(), *use           )==0);
    BOOST_CHECK_THROW	 (changePassword(cu, "bad", "newPwd"), VishnuException);
    BOOST_CHECK	 (close         (sess.getSessionKey()                )==0);

    // Reset pwd ok
    BOOST_MESSAGE(" Testing reset password normal UA2-B"    );
    BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
    BOOST_CHECK	 (connect      (uid, pwd, sess, cop )==0);
    BOOST_CHECK    (resetPassword(sess.getSessionKey(), uid, np       )==0);
    BOOST_CHECK    (changePassword(uid, np, pwd       )==0);
    BOOST_CHECK	 (close        (sess.getSessionKey()                )==0);

    // Reset pwd bad uid
    BOOST_MESSAGE(" Testing reset password bad uid UA2-E"    );
    BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql" )==0);
    BOOST_CHECK	 (connect      (uid, pwd  , sess, cop)==0);
    BOOST_CHECK	 (addUser(sess.getSessionKey(), *use            )==0);
    BOOST_CHECK_THROW	 (resetPassword(sess.getSessionKey(), "bad", np          ), VishnuException);
    BOOST_CHECK	 (close        (sess.getSessionKey()                 )==0);

    pwd  = UMSADMINVISHNUPWD  ;
    uid  = UMSADMINVISHNULOGIN;
  }
  // Add local account
  BOOST_MESSAGE(" Testing add local account success U4-B"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  lacc.setUserId       (uidUMSDb);
  lacc.setMachineId    (mid);
  lacc.setAcLogin     (accL);
  lacc.setSshKeyPath   (ssh);
  lacc.setHomeDirectory(home);
  BOOST_CHECK(addLocalAccount(sess.getSessionKey(), lacc, key2)==0);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Add local account bad machine id
  BOOST_MESSAGE(" Testing add local account bad machine U4-E"    );
  BOOST_REQUIRE(restore        (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect        (uid, pwd , sess, cop)==0);
  lacc.setMachineId("bad");
  BOOST_CHECK_THROW	 (addLocalAccount(sess.getSessionKey(), lacc, key2  ), VishnuException);
  BOOST_CHECK	 (close          (sess.getSessionKey()        	   )==0);
  lacc.setMachineId(mid);

  // Add local account bad acc login
  BOOST_MESSAGE(" Testing add local account bad user id U4-E"    );
  BOOST_REQUIRE(restore	 (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect	 (uid, pwd, sess, cop )==0);
  lacc.setUserId("bad");
  BOOST_CHECK_THROW	 (addLocalAccount(sess.getSessionKey(), lacc, key2    ), VishnuException);
  BOOST_CHECK	 (close          (sess.getSessionKey()      	     )==0);
  lacc.setUserId(uidUMSDb);

  // Update local account
  BOOST_MESSAGE(" Testing update local account success U4.1-B"    );
  BOOST_REQUIRE(restore	  (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect	  (uid, pwd , sess, cop)==0);
  lacc.setSshKeyPath("/usr/bin");
  lacc.setAcLogin("");  // to avoid changing acLogin
  BOOST_CHECK(updateLocalAccount(sess.getSessionKey(), lacc	      )==0);
  BOOST_CHECK(close             (sess.getSessionKey()      	      )==0);
  lacc.setSshKeyPath(ssh);

  // Update local account bad machine id
  BOOST_MESSAGE(" Testing update local account bad machine U4.1-E"    );
  BOOST_REQUIRE(restore           (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect           (uid, pwd , sess, cop)==0);
  //  BOOST_CHECK	 (addLocalAccount   (sess.getSessionKey(), lacc, key2  	)==0);
  lacc.setMachineId("bad");
  BOOST_CHECK_THROW  (updateLocalAccount(sess.getSessionKey(), lacc	        ), VishnuException);
  BOOST_CHECK	 (close             (sess.getSessionKey()        	)==0);
  lacc.setMachineId(mid);

  // Update local account bad user id
  BOOST_MESSAGE(" Testing update local account bad machine U4.1-E"    );
  BOOST_REQUIRE(restore           (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect           (uid, pwd , sess, cop)==0);
  //  BOOST_CHECK	 (addLocalAccount   (sess.getSessionKey(), lacc, key2  	)==0);
  lacc.setUserId("bad");
  BOOST_CHECK_THROW  (updateLocalAccount(sess.getSessionKey(), lacc	        ), VishnuException);
  BOOST_CHECK	 (close             (sess.getSessionKey()        	)==0);
  lacc.setUserId(mid);

  // Delete local account
  BOOST_MESSAGE(" Testing delete local account normal U4.2B"    );
  BOOST_REQUIRE(restore           (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect           (uid, pwd , sess, cop)==0);
  lacc.setUserId       (uidUMSDb);
  lacc.setMachineId    (mid);
  lacc.setAcLogin     (accL);
  lacc.setSshKeyPath   (ssh);
  lacc.setHomeDirectory(home);
  //  BOOST_CHECK	 (addLocalAccount   (sess.getSessionKey(), lacc, key2    )==0);
  BOOST_CHECK	 (deleteLocalAccount(sess.getSessionKey(), uidUMSDb , mid     )==0);
  BOOST_CHECK	 (close             (sess.getSessionKey()                )==0);

  // Delete local accountbad uid
  BOOST_MESSAGE(" Testing delete local account bad uid U4.2E"    );
  BOOST_REQUIRE(restore           (sqlScript+"/clean_session.sql" )==0);
  BOOST_CHECK  (connect           (uid, pwd  , sess, cop)==0);
  BOOST_CHECK	 (addLocalAccount   (sess.getSessionKey(), lacc, key2     )==0);
  BOOST_CHECK_THROW	 (deleteLocalAccount(sess.getSessionKey(), "bad", mid     ), VishnuException);
  BOOST_CHECK	 (close             (sess.getSessionKey()                 )==0);

  // Delete local accountbad uid
  BOOST_MESSAGE(" Testing delete local account bad machine"    );
  BOOST_REQUIRE(restore           (sqlScript+"/clean_session.sql"  )==0);
  BOOST_CHECK  (connect           (uid, pwd , sess  , cop)==0);
  //  BOOST_CHECK	 (addLocalAccount   (sess.getSessionKey(), lacc, key2      )==0);
  BOOST_CHECK_THROW	 (deleteLocalAccount(sess.getSessionKey(), uidUMSDb , "bad"     ), VishnuException);
  BOOST_CHECK	 (close             (sess.getSessionKey()                  )==0);

  // Test add machine normal
  BOOST_MESSAGE(" Testing add machine UA6.1B"    );
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect    (uid, pwd, sess, cop )==0);
  ma.setMachineId         (maid);
  ma.setName              (mana);
  ma.setSite              (site);
  ma.setMachineDescription(desc);
  ma.setLanguage          (lang);
  ma.setSshPublicKey      (sqlScript+"/id_rsa.pub");
  BOOST_CHECK	 (addMachine (sess.getSessionKey(), ma            )==0);
  BOOST_CHECK	 (close      (sess.getSessionKey()                )==0);

  // Machine already exist
//   BOOST_MESSAGE(" Testing add machine twice the same UA6.1E"    );
//   BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
//   BOOST_CHECK  (connect    (uid, pwd, sess, cop )==0);
//   BOOST_CHECK	 (addMachine (sess.getSessionKey(), ma            )==0);
//   BOOST_CHECK_THROW	 (addMachine (sess.getSessionKey(), ma            ), VishnuException);
//   BOOST_CHECK	 (close      (sess.getSessionKey()                )==0);

  // Test update machine normal
  BOOST_MESSAGE(" Testing update machine UA6.4B"    );
  BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect      (uid, pwd, sess, cop )==0);
  BOOST_CHECK	 (addMachine   (sess.getSessionKey(), ma            )==0);
  ma.setName("Machina");
  BOOST_CHECK	 (updateMachine(sess.getSessionKey(), ma            )==0);
  BOOST_CHECK	 (close        (sess.getSessionKey()                )==0);
  ma.setName(mana);

  // Test update machine bad mid
  BOOST_MESSAGE(" Testing update machine bad machine id UA6.4E"    );
  BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect      (uid, pwd, sess, cop )==0);
  BOOST_CHECK	 (addMachine   (sess.getSessionKey(), ma            )==0);
  ma.setMachineId("bad");
  BOOST_CHECK_THROW	 (updateMachine(sess.getSessionKey(), ma            ), VishnuException);
  BOOST_CHECK	 (close        (sess.getSessionKey()                )==0);
  ma.setMachineId(maid);

  // Test delete machine normal
  BOOST_MESSAGE(" Testing update machine UA6.2B"    );
  BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect      (uid, pwd , sess, cop)==0);
  BOOST_CHECK	 (addMachine   (sess.getSessionKey(), ma            )==0);
  BOOST_CHECK	 (deleteMachine(sess.getSessionKey(), ma.getMachineId()          )==0);
  BOOST_CHECK	 (close        (sess.getSessionKey()                )==0);

  // Test delete machine bad mid
  BOOST_MESSAGE(" Testing delete machine bad machine id UA6.2E"    );
  BOOST_REQUIRE(restore      (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect      (uid, pwd, sess, cop )==0);
  BOOST_CHECK	 (addMachine   (sess.getSessionKey(), ma            )==0);
  ma.setMachineId("bad");
  BOOST_CHECK_THROW	 (updateMachine(sess.getSessionKey(), ma            ), VishnuException);
  BOOST_CHECK	 (close        (sess.getSessionKey()                )==0);
  ma.setMachineId(maid);

  // Test list user
  liuo.setUserId ("");
  BOOST_REQUIRE(restore  (sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing normal list user UA5.2B" );
  BOOST_CHECK  (connect  (uid, pwd, sess, cop )==0);
  BOOST_CHECK  (listUsers(sess.getSessionKey(), *liu, liuo       )==0);
  BOOST_CHECK  (close    (sess.getSessionKey()                )==0);
  BOOST_CHECK (liu->getUsers().size()>0);
  BOOST_CHECK (liu->getUsers()[0]->getUserId() == "admin_1");

  // Test list user bad authsysid
  liuo.setUserId ("");
  liuo.setAuthSystemId ("lapin");
  BOOST_REQUIRE(restore  (sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing normal list user UA5.2B" );
  BOOST_CHECK  (connect  (uid, pwd, sess, cop )==0);
  BOOST_CHECK_THROW  (listUsers(sess.getSessionKey(), *liu, liuo       ), VishnuException);
  BOOST_CHECK  (close    (sess.getSessionKey()                )==0);

  // Test list user option user
  liuo.setUserId ("admin_1");
  liuo.setAuthSystemId ("");
  BOOST_REQUIRE(restore  (sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing list user with userid UA5.2B" );
  BOOST_CHECK  (connect  (uid, pwd, sess, cop )==0);
  liu = ecoreFactory->createListUsers();
  BOOST_CHECK  (listUsers(sess.getSessionKey(), *liu, liuo )==0);
  BOOST_CHECK  (close    (sess.getSessionKey()                )==0);
  BOOST_CHECK (liu->getUsers().size()>0);
  BOOST_CHECK (liu->getUsers()[0]->getUserId()=="admin_1");

  // Test list user
  liuo.setUserId ("");
  BOOST_REQUIRE(restore  (sqlScript+"/clean_session.sql"  )==0);
  BOOST_MESSAGE(" Testing bad key list user UA5.2E" );
  BOOST_CHECK  (connect  (uid  , pwd, sess, cop )==0);
  liu = ecoreFactory->createListUsers();
  BOOST_CHECK_THROW  (listUsers("bad", *liu, liuo       ), VishnuException);
  BOOST_CHECK  (close    (sess.getSessionKey()                  )==0);

  // Test list session
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql"  )==0);
  BOOST_MESSAGE(" Testing list session base U1.3.5B" );
  BOOST_CHECK  (connect    (uidu, pwdu, sess, cop )==0);
  li = ecoreFactory->createListSessions();
  BOOST_CHECK  (listSessions(sess.getSessionKey() , *li  , opt      )==0);
  BOOST_CHECK  (close      (sess.getSessionKey()                  )==0);
  BOOST_CHECK (li->getSessions().size() > 0);
  if ((li->getSessions().size()>0) && (li->getSessions()[0]->getSessionKey()!=sess.getSessionKey()))
    BOOST_MESSAGE(" key: " << li->getSessions()[0]->getSessionKey() );

  // Test list session for an admin
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql")==0);
  BOOST_MESSAGE(" Testing list session base for admin UA5.1B" );
  li = ecoreFactory->createListSessions();
  BOOST_CHECK  (connect    (uid, pwd, sess, cop )==0);
  BOOST_CHECK  (listSessions(sess.getSessionKey(), *li , opt      )==0);
  BOOST_CHECK  (close      (sess.getSessionKey()                )==0);
  BOOST_CHECK  (li->getSessions().size() > 0);
  if ((li->getSessions().size()>0) && (li->getSessions()[0]->getSessionKey()!=sess.getSessionKey()))
    BOOST_MESSAGE(" key: " << li->getSessions()[0]->getSessionKey() );

  // Test list session error
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql"   )==0);
  BOOST_MESSAGE(" Testing bad key list session base 1.3.5E" );
  li = ecoreFactory->createListSessions();
  BOOST_CHECK  (connect    (uidu , pwdu, sess, cop )==0);
  BOOST_CHECK_THROW  (listSessions("bad", *li  , opt      ), VishnuException);
  BOOST_CHECK  (close      (sess.getSessionKey()                   )==0);

  // Test list session opt
  opt.setUserId(uiduUMSDb);
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql"   )==0);
  BOOST_MESSAGE(" Testing list session base option 1.3.5B" );
  li = ecoreFactory->createListSessions();
  BOOST_CHECK  (connect    (uidu, pwdu, sess2, cop )==0);
  BOOST_CHECK  (connect    (uid , pwd	, sess , cop )==0);
  BOOST_CHECK  (listSessions(sess.getSessionKey() , *li 	, opt       )==0);
  BOOST_CHECK  (close      (sess.getSessionKey()                   )==0);
  BOOST_CHECK  (close      (sess2.getSessionKey()                  )==0);
  opt  = *(ecoreFactory->createListSessionOptions());
  BOOST_CHECK (li->getSessions().size() > 0);

  // Test list machine
  BOOST_REQUIRE(restore     (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing normal list machine UA6.3B" );
  BOOST_CHECK  (connect     (uid, pwd, sess, cop )==0);
  BOOST_CHECK  (listMachines(sess.getSessionKey(), *lim, liom      )==0);
  BOOST_CHECK  (close       (sess.getSessionKey()                 )==0);
  BOOST_CHECK (lim->getMachines().size() > 0);
  if (lim->getMachines().size()>0) {
    BOOST_CHECK(lim->getMachines()[0]->getMachineId()=="machine_1");
  }

  // Test list machine option mid
  liom.setMachineId(mid);
  BOOST_REQUIRE(restore     (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing normal list machine on a specific machine UA6.3B" );
  lim  = ecoreFactory->createListMachines();
  BOOST_CHECK  (connect     (uid, pwd, sess, cop )==0);
  BOOST_CHECK  (listMachines(sess.getSessionKey(), *lim, liom      )==0);
  BOOST_CHECK  (close       (sess.getSessionKey()                 )==0);
  BOOST_CHECK (lim->getMachines().size() > 0);
  if (lim->getMachines().size()>0) {
    BOOST_CHECK(lim->getMachines()[0]->getMachineId()=="machine_1");
  }

  // Test list machine option bad mid
  liom.setMachineId("bad");
  BOOST_REQUIRE(restore     (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing bad mid list machine on a specific machine UA6.3E" );
  lim  = ecoreFactory->createListMachines();
  BOOST_CHECK  (connect     (uid, pwd, sess, cop )==0);
  BOOST_CHECK_THROW  (listMachines(sess.getSessionKey(), *lim, liom      ), VishnuException);
  BOOST_CHECK  (close       (sess.getSessionKey()                 )==0);

  // Test list local account
  BOOST_REQUIRE(restore         (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing normal list local account U4.3B" );
  BOOST_CHECK  (connect         (uid, pwd, sess, cop )==0);
  BOOST_CHECK  (listLocalAccounts(sess.getSessionKey(), *lia, lioa      )==0);
  BOOST_CHECK  (close           (sess.getSessionKey()                 )==0);
  BOOST_CHECK (lia->getAccounts().size()>0);
  if (lia->getAccounts().size()>0) {
    BOOST_CHECK(lia->getAccounts()[0]->getMachineId()=="machine_1");
  }

  // Test list local account mid
  lioa.setMachineId(mid);
  BOOST_REQUIRE(restore         (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing normal list local account on a machine U4.3B" );
  BOOST_CHECK  (connect         (uid, pwd, sess, cop )==0);
  lia  = ecoreFactory->createListLocalAccounts();
  BOOST_CHECK  (listLocalAccounts(sess.getSessionKey(), *lia, lioa      )==0);
  BOOST_CHECK  (close           (sess.getSessionKey()                 )==0);
  BOOST_CHECK (lia->getAccounts().size()>0);
  if (lia->getAccounts().size()>0) {
    BOOST_CHECK(lia->getAccounts()[0]->getMachineId()=="machine_1");
  }

  // Test list local account bad mid
  lioa.setMachineId("bad");
  BOOST_REQUIRE(restore         (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing bad machine on list local account U4.3E" );
  BOOST_CHECK  (connect         (uid, pwd, sess, cop )==0);
  lia  = ecoreFactory->createListLocalAccounts();
  BOOST_CHECK_THROW  (listLocalAccounts(sess.getSessionKey(), *lia, lioa      ), VishnuException);
  BOOST_CHECK  (close           (sess.getSessionKey()                 )==0);

  // Test configure default option
  opva.setOptionName(ona);
  opva.setValue(oval);
  BOOST_REQUIRE(restore               (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing normal list local account UA7-B" );
  BOOST_CHECK  (connect               (uid, pwd , sess, cop )==0);
  BOOST_CHECK  (configureDefaultOption(sess.getSessionKey(), opva           )==0);
  BOOST_CHECK  (close                 (sess.getSessionKey()                 )==0);

  // Test configure option bad option name
  opva.setOptionName("bad");
  opva.setValue     (oval);
  BOOST_REQUIRE(restore        (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing bad name configure option U1.3.1E1" );
  BOOST_CHECK  (connect        (uid, pwd , sess, cop )==0);
  BOOST_CHECK_THROW  (configureDefaultOption(sess.getSessionKey(), opva           ), VishnuException);
  BOOST_CHECK  (close          (sess.getSessionKey()                 )==0);

  // Test configure option bad option value
  opva.setOptionName(ona);
  opva.setValue     ("-30");
  BOOST_REQUIRE(restore        (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing bad value configure option U1.3.1E2" );
  BOOST_CHECK  (connect        (uid, pwd , sess, cop )==0);
  BOOST_CHECK_THROW  (configureDefaultOption(sess.getSessionKey(), opva           ), VishnuException);
  BOOST_CHECK  (close          (sess.getSessionKey()                 )==0);

  // Test configure option
  opva.setOptionName(ona);
  opva.setValue("546");
  BOOST_REQUIRE(restore        (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing normal configure option U1.3.1-B" );
  BOOST_CHECK  (connect        (uid, pwd , sess, cop )==0);
  BOOST_CHECK  (configureOption(sess.getSessionKey(), opva           )==0);
  BOOST_CHECK  (close          (sess.getSessionKey()                 )==0);

  // Test configure option bad option name
  opva.setOptionName("bad");
  opva.setValue     (oval);
  BOOST_REQUIRE(restore        (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing bad name configure option U1.3.1E1" );
  BOOST_CHECK  (connect        (uid, pwd , sess, cop )==0);
  BOOST_CHECK_THROW  (configureOption(sess.getSessionKey(), opva           ), VishnuException);
  BOOST_CHECK  (close          (sess.getSessionKey()                 )==0);

  // Test configure option bad option value
  opva.setOptionName(ona);
  opva.setValue     ("-30");
  BOOST_REQUIRE(restore        (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing bad value configure option U1.3.1E2" );
  BOOST_CHECK  (connect        (uid, pwd , sess, cop )==0);
  BOOST_CHECK_THROW  (configureOption(sess.getSessionKey(), opva           ), VishnuException);
  BOOST_CHECK  (close          (sess.getSessionKey()                 )==0);

  // Test list option values
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing normal list option value U1.3.2B" );
  BOOST_CHECK  (connect    (uid, pwd , sess , cop)==0);
  liov  = ecoreFactory->createListOptionsValues();
  BOOST_CHECK  (listOptions(sess.getSessionKey(), *liov, lioo     )==0);
  BOOST_CHECK  (close      (sess.getSessionKey()                 )==0);
  BOOST_CHECK (liov->getOptionValues().size() > 0);
  if (liov->getOptionValues().size()>0) {
    BOOST_CHECK(liov->getOptionValues()[0]->getOptionName()==ona);
  }

  // Test list option values bad option name
  lioo.setOptionName("bad");
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing bad mid list option value U1.3.2E1" );
  BOOST_CHECK  (connect    (uid, pwd , sess , cop)==0);
  liov  = ecoreFactory->createListOptionsValues();
  BOOST_CHECK_THROW  (listOptions(sess.getSessionKey(), *liov, lioo     ), VishnuException);
  BOOST_CHECK  (close      (sess.getSessionKey()                 )==0);

  // Test list option values bad uid
  lioo.setUserId(mid);
  lioo.setUserId("bad");
  BOOST_REQUIRE(restore    (sqlScript+"/clean_session.sql" )==0);
  BOOST_MESSAGE(" Testing bad uid list option value U1.3.2E2" );
  BOOST_CHECK  (connect    (uid, pwd , sess , cop)==0);
  liov  = ecoreFactory->createListOptionsValues();
  BOOST_CHECK_THROW  (listOptions(sess.getSessionKey(), *liov, lioo     ), VishnuException);
  BOOST_CHECK  (close      (sess.getSessionKey()                 )==0);



  // Test Save configuration
  BOOST_MESSAGE(" Testing save conf"    );
  BOOST_REQUIRE(restore      	   (sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK	 (connect      	   (uid, pwd, sess, cop )==0);
  BOOST_CHECK	 (saveConfiguration(sess.getSessionKey(), conf          )==0);
  BOOST_CHECK	 (close            (sess.getSessionKey()                )==0);

  // Test restore configuration
  BOOST_MESSAGE(" Testing restore conf"    );
  BOOST_REQUIRE(restore      	      (sqlScript+"/clean_session.sql"   )==0);
  BOOST_CHECK	 (connect      	      (root, pwdr  , sess  , cop)==0);
  BOOST_MESSAGE("Configuration = "+conf.getFilePath());
  BOOST_CHECK	 (restoreConfiguration(sess.getSessionKey(), conf.getFilePath()            )==0);
  BOOST_CHECK    (changePassword(uid, pwd, pwd       )==0);
  BOOST_CHECK    (changePassword(root, pwdr, pwdr       )==0);
  BOOST_CHECK	 (close               (sess.getSessionKey()                   )==0);

   // Test restore configuration with webboard
  BOOST_MESSAGE(" Testing restore conf with webboard data initialization"    );
  BOOST_REQUIRE(restore             (sqlScript+"/cleanModelWithWebboard.sql"   )==0);
  BOOST_REQUIRE(restore             (sqlScript+"/UMSinitWebboardData.sql"   )==0);
  BOOST_CHECK  (connect             (root, pwdr  , sess  , cop)==0);
  BOOST_MESSAGE("Configuration = "+conf.getFilePath());
  BOOST_CHECK  (restoreConfiguration(sess.getSessionKey(), conf.getFilePath()            )==0);
  BOOST_CHECK    (changePassword(uid, pwd, pwd       )==0);
  BOOST_CHECK    (changePassword(root, pwdr, pwdr       )==0);
  BOOST_CHECK  (close               (sess.getSessionKey()                   )==0);

  // Test restore configuration bad path
  BOOST_MESSAGE(" Testing restore conf"    );
  BOOST_REQUIRE(restore      	      (sqlScript+"/clean_session.sql"   )==0);
  BOOST_CHECK	 (connect      	      (root, pwdr , sess  , cop)==0);
  BOOST_CHECK	 (saveConfiguration   (sess.getSessionKey(), conf             )==0);
  //  conf->setFilePath("bad");
  BOOST_CHECK_THROW	 (restoreConfiguration(sess.getSessionKey(), "toto"            ), VishnuException);
  BOOST_CHECK	 (close               (sess.getSessionKey()                   )==0);


  // Add auth system
  BOOST_MESSAGE(" Testing add auth system success UA8"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  asys.setName("ldap");
  asys.setURI("httm://www.graal.ens-lyon.fr");
  asys.setAuthLogin("toto");
  asys.setAuthPassword("toto");
  UMS_Data::EncryptionMethod enc = 0;
  asys.setUserPasswordEncryption(enc);
  AuthType tsys = 0;
  StatusType ssys = 1;
  asys.setType(tsys);
  asys.setStatus(ssys);
  asys.setLdapBase("$USERNAME.base");
  BOOST_CHECK(addAuthSystem(sess.getSessionKey(), asys)==0);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Add auth system already exist
  BOOST_MESSAGE(" Testing add auth system already exist UA8"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  asys.setName("ldap");
  asys.setURI("httm://www.graal.ens-lyon.fr");
  asys.setAuthLogin("toto");
  asys.setAuthPassword("toto");
  asys.setUserPasswordEncryption(enc);
  tsys = 0;
  ssys = 1;
  asys.setType(tsys);
  asys.setStatus(ssys);
  asys.setLdapBase("$USERNAME.base");
  BOOST_CHECK_THROW(addAuthSystem(sess.getSessionKey(), asys), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Add auth system bad type
  BOOST_MESSAGE(" Testing add auth system already exist UA8"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  asys.setName("ldap2");
  asys.setURI("httm://www.graal.ens-lyon.fr2");
  asys.setAuthLogin("toto2");
  asys.setAuthPassword("toto2");
  asys.setUserPasswordEncryption(enc);
  tsys = 7;
  ssys = 1;
  asys.setType(tsys);
  asys.setStatus(ssys);
  asys.setLdapBase("$USERNAME.base2");
  BOOST_CHECK_THROW(addAuthSystem(sess.getSessionKey(), asys), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

//  // Add auth system bad status
//  BOOST_MESSAGE(" Testing add auth system already exist UA8"    );
//  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
//  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
//  asys.setName("ldap2");
//  asys.setURI("httm://www.graal.ens-lyon.fr2");
//  asys.setAuthLogin("toto2");
//  asys.setAuthPassword("toto2");
//  asys.setUserPasswordEncryption(enc);
//  tsys = 0;
//  ssys = 7;
//  asys.setType(tsys);
//  asys.setStatus(ssys);
//  asys.setLdapBase("base2");
//  BOOST_CHECK_THROW(addAuthSystem(sess.getSessionKey(), asys), VishnuException);
//  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Add auth system
  BOOST_MESSAGE(" Testing add auth system with bad LDAP base UA8-E5"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  asys.setName("ldapBase-add");
  asys.setURI("httm://www.graal.ens-lyon.fr");
  asys.setAuthLogin("toto");
  asys.setAuthPassword("toto");
  enc = 0;
  tsys = 0;
  ssys = 1;
  asys.setUserPasswordEncryption(enc);
  asys.setType(tsys);
  asys.setStatus(ssys);
  asys.setLdapBase("base");
  BOOST_CHECK_THROW(addAuthSystem(sess.getSessionKey(), asys), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Update auth system
  BOOST_MESSAGE(" Testing update auth system  UA8.1"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  asys.setName("ldap3");
  asys.setURI("httm://www.graal.ens-lyon.fr");
  asys.setAuthLogin("toto3");
  asys.setAuthPassword("toto3");
  asys.setUserPasswordEncryption(enc);
  tsys = 0;
  ssys = 1;
  asys.setType(tsys);
  asys.setStatus(ssys);
  asys.setLdapBase("$USERNAME.base");
  BOOST_CHECK(addAuthSystem(sess.getSessionKey(), asys)==0);
  asys.setName("ldap4");
  BOOST_CHECK(updateAuthSystem(sess.getSessionKey(), asys)==0);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Update auth syste bad type
  BOOST_MESSAGE(" Testing update auth system bad type UA8.1"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  asys.setName("ldap8");
  asys.setURI("httm://www.graal.ens-lyon.fr");
  asys.setAuthLogin("toto4");
  asys.setAuthPassword("toto4");
  asys.setUserPasswordEncryption(enc);
  tsys = 0;
  ssys = 1;
  asys.setType(tsys);
  asys.setStatus(ssys);
  asys.setLdapBase("$USERNAME.base");
  BOOST_CHECK(addAuthSystem(sess.getSessionKey(), asys)==0);
  tsys = 5;
  asys.setType(tsys);
  BOOST_CHECK_THROW(updateAuthSystem(sess.getSessionKey(), asys), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Update auth syste bad status
  BOOST_MESSAGE(" Testing update auth system bad status UA8.1"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  asys.setName("ldap3");
  asys.setURI("httm://www.graal.ens-lyon.fr");
  asys.setAuthLogin("toto3");
  asys.setAuthPassword("toto3");
  asys.setUserPasswordEncryption(enc);
  tsys = 0;
  ssys = 7;
  asys.setType(tsys);
  asys.setStatus(ssys);
  asys.setLdapBase("$USERNAME.base");
  BOOST_CHECK(addAuthSystem(sess.getSessionKey(), asys)==0);
  asys.setStatus(ssys);
  asys.setName("ldap");
  ssys = 7;
  BOOST_CHECK_THROW(updateAuthSystem(sess.getSessionKey(), asys), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  BOOST_MESSAGE(" Testing update auth system with bad LDAP base UA8.1-E5"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  asys.setName("ldapBase-update");
  asys.setURI("httm://www.graal.ens-lyon.fr");
  asys.setAuthLogin("toto");
  asys.setAuthPassword("toto");
  enc = 0;
  tsys = 0;
  ssys = 1;
  asys.setUserPasswordEncryption(enc);
  asys.setType(tsys);
  asys.setStatus(ssys);
  asys.setLdapBase("base");
  BOOST_CHECK_THROW(updateAuthSystem(sess.getSessionKey(), asys), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Delete auth system
  BOOST_MESSAGE(" Testing delete auth system UA8.2"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  asys.setName("ldap9");
  asys.setURI("httm://www.graal.ens-lyon.fr");
  asys.setAuthLogin("toto3");
  asys.setAuthPassword("toto3");
  asys.setUserPasswordEncryption(enc);
  tsys = 0;
  ssys = 1;
  asys.setType(tsys);
  asys.setStatus(ssys);
  asys.setLdapBase("$USERNAME.base");
  BOOST_CHECK(addAuthSystem(sess.getSessionKey(), asys)==0);
  BOOST_CHECK(deleteAuthSystem(sess.getSessionKey(), asys.getAuthSystemId())==0);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Delete auth system bad id
  BOOST_MESSAGE(" Testing delete auth system with bad identifier UA8.2"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  asys.setName("ldap5");
  asys.setURI("httm://www.graal.ens-lyon.fr");
  asys.setAuthLogin("toto5");
  asys.setAuthPassword("toto5");
  asys.setUserPasswordEncryption(enc);
  tsys = 0;
  ssys = 1;
  asys.setType(tsys);
  asys.setStatus(ssys);
  asys.setLdapBase("$USERNAME.base2");
  BOOST_CHECK(addAuthSystem(sess.getSessionKey(), asys)==0);
  BOOST_CHECK_THROW(deleteAuthSystem(sess.getSessionKey(), "bad"), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // List auth system
  BOOST_MESSAGE(" Testing list auth system  U5"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  liaso.setListAllAuthSystems(true);
  liaso.setListFullInfo(true);
  BOOST_CHECK(listAuthSystems(sess.getSessionKey(), *lias, liaso)==0);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // List auth system bad user
  BOOST_MESSAGE(" Testing list auth system bad user U5"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  liaso.setListAllAuthSystems(true);
  liaso.setListFullInfo(true);
  liaso.setUserId("toto");
  BOOST_CHECK_THROW(listAuthSystems(sess.getSessionKey(), *lias, liaso), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);


  // Add auth account
  BOOST_MESSAGE(" Testing add auth account success U6"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  aacc.setAuthSystemId(asys.getAuthSystemId());
  aacc.setUserId(uidUMSDb);
  aacc.setAcLogin("toto");
  BOOST_CHECK(addAuthAccount(sess.getSessionKey(), aacc)==0);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Add auth account bad sys
  BOOST_MESSAGE(" Testing add auth account success U6"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  aacc.setAuthSystemId("storm");
  aacc.setUserId(uidUMSDb);
  aacc.setAcLogin("toto");
  BOOST_CHECK_THROW(addAuthAccount(sess.getSessionKey(), aacc), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Add auth account bad user
  BOOST_MESSAGE(" Testing add auth account success U6"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  aacc.setAuthSystemId(asys.getAuthSystemId());
  aacc.setUserId("plop");
  aacc.setAcLogin("toto");
  BOOST_CHECK_THROW(addAuthAccount(sess.getSessionKey(), aacc), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Update auth account
  BOOST_MESSAGE(" Testing update auth account success U6.1"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  aacc.setAuthSystemId(asys.getAuthSystemId());
  aacc.setUserId(uidUMSDb);
  aacc.setAcLogin("titi");
//  BOOST_CHECK(addAuthAccount(sess.getSessionKey(), aacc)==0);
  BOOST_CHECK(updateAuthAccount(sess.getSessionKey(), aacc)==0);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Update auth account bad sys
  BOOST_MESSAGE(" Testing update auth account success U6.1"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  aacc.setAuthSystemId(asys.getAuthSystemId());
  aacc.setUserId(uidUMSDb);
//  aacc.setAcLogin("toto");
//  BOOST_CHECK(addAuthAccount(sess.getSessionKey(), aacc)==0);
  aacc.setAuthSystemId("toto");
  BOOST_CHECK_THROW(updateAuthAccount(sess.getSessionKey(), aacc), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Update auth account bad user
  BOOST_MESSAGE(" Testing update auth account success U6.1"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  aacc.setAuthSystemId(asys.getAuthSystemId());
  aacc.setUserId(uidUMSDb);
  aacc.setAcLogin("toto");
//  BOOST_CHECK(addAuthAccount(sess.getSessionKey(), aacc)==0);
  aacc.setUserId("choco");
  BOOST_CHECK_THROW(updateAuthAccount(sess.getSessionKey(), aacc), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);


  // Delete auth account
  BOOST_MESSAGE(" Testing update auth account success U6.2"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  aacc.setAuthSystemId(asys.getAuthSystemId());
  aacc.setUserId(rootUMSDb);
  aacc.setAcLogin("toto2");
  BOOST_MESSAGE(uid);
  BOOST_MESSAGE(pwd);
  BOOST_MESSAGE(sess.getSessionKey());
  BOOST_MESSAGE(asys.getAuthSystemId());
  BOOST_MESSAGE(rootUMSDb);
  BOOST_CHECK(addAuthAccount(sess.getSessionKey(), aacc)==0);
  BOOST_MESSAGE(aacc.getUserId()); //TODO
  //BOOST_CHECK(deleteAuthAccount(sess.getSessionKey(), aacc.getAuthSystemId(), aacc.getUserId())==0);
  BOOST_MESSAGE("delete");
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Delete auth account bad uid
  BOOST_MESSAGE(" Testing update auth account success U6.2"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
//  aacc.setAuthSystemId(asys.getAuthSystemId());
//  aacc.setUserId(uid);
//  BOOST_CHECK(addAuthAccount(sess.getSessionKey(), aacc)==0);
  aacc.setUserId("plouf");
  BOOST_CHECK_THROW(deleteAuthAccount(sess.getSessionKey(), aacc.getAuthSystemId(), aacc.getUserId()), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // Delete auth account bad auth id
  BOOST_MESSAGE(" Testing update auth account success U6.2"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  aacc.setAuthSystemId(asys.getAuthSystemId());
  aacc.setUserId(uidUMSDb);
//  BOOST_CHECK(addAuthAccount(sess.getSessionKey(), aacc)==0);
  aacc.setAuthSystemId("err");
  BOOST_CHECK_THROW(deleteAuthAccount(sess.getSessionKey(), aacc.getAuthSystemId(), aacc.getUserId()), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // List auth acc
  BOOST_MESSAGE(" Testing update auth system already exist U6.3"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  liaao.setListAll(true);
  BOOST_CHECK(listAuthAccounts(sess.getSessionKey(), *liaa, liaao)==0);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);

  // List auth acc bad user
  BOOST_MESSAGE(" Testing update auth system already exist U6.3"    );
  BOOST_REQUIRE(restore(sqlScript+"/clean_session.sql")==0);
  BOOST_CHECK  (connect(uid, pwd, sess, cop )==0);
  liaao.setListAll(true);
  liaao.setUserId("plouf");
  BOOST_CHECK_THROW(listAuthAccounts(sess.getSessionKey(), *liaa, liaao), VishnuException);
  BOOST_CHECK(close          (sess.getSessionKey()      )==0);


  // History, make all commands once and test list them
  BOOST_MESSAGE(" Testing history cmd"    );
  BOOST_REQUIRE(restore               (sqlScript+"/clean_session.sql" )==0);
  BOOST_CHECK	 (connect               (uid, pwd , sess , cop)==0);
  li   = ecoreFactory->createListSessions();
  BOOST_CHECK  (listSessions(sess.getSessionKey(), *li , opt      )==0);
  // -> and then reconnect normal
  if (li->getSessions().size() &&
      (li->getSessions())[0]){
    rec = li->getSessions()[0]->getSessionId();
    BOOST_CHECK(reconnect  (uid, pwd, rec, sess)==0);
  }
  else{
    BOOST_MESSAGE("List session failed, reconnect not called");
  }

  liuo.setUserId ("");
  BOOST_CHECK	 (listUsers             (sess.getSessionKey(), *liu , liuo       )==0);
  liom.setMachineId(mid);
  liom.setListAllMachine(true);
  BOOST_CHECK	 (listMachines           (sess.getSessionKey(), *lim , liom     )==0);
  lioa.setMachineId("");
  BOOST_CHECK	 (listLocalAccounts      (sess.getSessionKey(), *lia , lioa     )==0);
  lioo = ListOptOptions();
  BOOST_CHECK	 (listOptions           (sess.getSessionKey(), *liov, lioo     )==0);
  BOOST_CHECK	 (addUser               (sess.getSessionKey(), *use 	     )==0);
  BOOST_CHECK	 (updateUser            (sess.getSessionKey(), *use 	     )==0);
  BOOST_CHECK	 (deleteUser            (sess.getSessionKey(), use->getUserId()  	     )==0);
  BOOST_CHECK	 (deleteMachine         (sess.getSessionKey(), mid	     )==0);

  if (umsAuthType.compare("LDAP") != 0) {
    BOOST_CHECK  (resetPassword         (sess.getSessionKey(), uidUMSDb, np      )==0);
    BOOST_CHECK	 (changePassword        (uidUMSDb, np , pwdUMSDb      )==0);
  }

  BOOST_CHECK	 (addMachine            (sess.getSessionKey(), ma	     )==0);
  lacc.setUserId       (uidUMSDb);
  lacc.setMachineId    (ma.getMachineId());
  lacc.setAcLogin     (accL);
  lacc.setSshKeyPath   (ssh);
  lacc.setHomeDirectory(home);
  BOOST_CHECK	 (addLocalAccount       (sess.getSessionKey(), lacc, key2     )==0);
  BOOST_CHECK	 (updateMachine         (sess.getSessionKey(), ma	     )==0);
  lacc.setAcLogin("");  // to avoid changing acLogin
  BOOST_CHECK	 (updateLocalAccount    (sess.getSessionKey(), lacc           )==0);
  BOOST_CHECK	 (deleteLocalAccount    (sess.getSessionKey(), uidUMSDb , ma.getMachineId()      )==0);
  opva.setValue(oval);
  BOOST_CHECK	 (configureDefaultOption(sess.getSessionKey(), opva	     )==0);
  BOOST_CHECK	 (configureOption       (sess.getSessionKey(), opva	     )==0);
  BOOST_CHECK	 (saveConfiguration     (sess.getSessionKey(), conf           )==0);
  //  BOOST_CHECK	 (restoreConfiguration  (sess.getSessionKey(), cpath          )==0);
  BOOST_CHECK	 (close                 (sess.getSessionKey()                 )==0);
  // Listing
  BOOST_CHECK	 (connect               (uid, pwd , sess, cop)==0);
  BOOST_CHECK	 (listHistoryCmd        (sess.getSessionKey(), *lic, lico     )==0);

  BOOST_CHECK_THROW	 (listHistoryCmd        ("bad", *lic, lico     ), VishnuException);

  BOOST_REQUIRE(restore    (sqlScript+"/cleanall.sql")==0);
  BOOST_REQUIRE(restore    (sqlScript+"/UMSinitTest.sql")==0);

} catch (VishnuException& e) {
  BOOST_MESSAGE(e.what());
  BOOST_CHECK(false);
}
} // BOOST_AUTO_TEST_CASE( my_test )

BOOST_AUTO_TEST_SUITE_END()
