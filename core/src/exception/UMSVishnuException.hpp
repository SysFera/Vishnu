/**
 * \file UMSVishnuException.hpp
 * \brief This file defines the UMS sub class for the Vishnu exceptions.
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 */
#ifndef __UMSVISHNUEXCEPTION__
#define __UMSVISHNUEXCEPTION__

#include <string>
#include "UserException.hpp"


static const int ERRCODE_UNKNOWN_USER = 20;
static const int ERRCODE_UNKNOWN_USERID = 21;
static const int ERRCODE_USERID_EXISTING = 22;
static const int ERRCODE_USER_LOCKED = 23;
static const int ERRCODE_USER_ALREADY_LOCKED = 24;
static const int ERRCODE_NO_ADMIN = 25;
static const int ERRCODE_TEMPORARY_PASSWORD = 26;
static const int ERRCODE_INVALID_MAIL_ADRESS = 27;

static const int ERRCODE_SESSIONKEY_NOT_FOUND = 28;
static const int ERRCODE_SESSIONKEY_EXPIRED = 29;
static const int ERRCODE_UNKNOWN_SESSION_ID = 30;
static const int ERRCODE_COMMAND_RUNNING = 31;

static const int ERRCODE_UNKNOWN_MACHINE = 32;
static const int ERRCODE_MACHINE_EXISTING = 33;
static const int ERRCODE_MACHINE_LOCKED = 34;
static const int ERRCODE_MACHINE_ALREADY_LOCKED = 35;
static const int ERRCODE_UNUSABLE_MACHINE = 36;

static const int ERRCODE_LOCAL_ACCOUNT_EXIST = 37;
static const int ERRCODE_UNKNOWN_LOCAL_ACCOUNT = 38;

static const int ERRCODE_SAVE_CONFIG_ERROR = 39;
static const int ERRCODE_RESTORE_CONFIG_ERROR = 40;

static const int ERRCODE_UNKNOWN_OPTION = 41;
static const int ERRCODE_UNKNOWN_CLOSURE_MODE = 42;
static const int ERRCODE_INCORRECT_TIMEOUT = 43;
static const int ERRCODE_INCORRECT_TRANSFER_CMD = 44;

static const int ERRCODE_ROOT_USER_ONLY = 45;
static const int ERRCODE_LOGIN_ALREADY_USED = 46;

static const int ERRCODE_UNKNOWN_AUTH_SYSTEM_TYPE = 47;
static const int ERRCODE_UNKNOWN_AUTH_SYSTEM = 48;
static const int ERRCODE_AUTH_SYSTEM_ALREADY_LOCKED = 49;
static const int ERRCODE_AUTH_SYSTEM_ALREADY_EXIST = 50;
static const int ERRCODE_AUTH_ACCOUNT_EXIST = 51;
static const int ERRCODE_UNKNOWN_AUTH_ACCOUNT = 52;
static const int ERRCODE_UNKNOWN_ENCRYPTION_METHOD = 53;
static const int ERRCODE_READONLY_ACCOUNT = 54;

/**
 * \class UMSVishnuException
 * \brief Specialisation of the user exception for the UMS module
 */
class UMSVishnuException: public UserException{

public:
  /**
   * \brief Default constructor
   */
  UMSVishnuException();
  /**
   * \brief Copy constructor
   * \param e The copied exception
   */
  UMSVishnuException(const UMSVishnuException& e);
  /**
   * \brief Constructor
   * \param msg The message to use to build
   * \param msgComp Th complementary message used to build the exception
   */
  UMSVishnuException(int msg, std::string msgComp = "");
  /**
   * \brief Default constructor
   */
  ~UMSVishnuException()throw (){};
  /**
   * \brief Function to initialize all UMS generic messages
   */
  void
  initMsg();
};

#endif // UMSVishnuException
