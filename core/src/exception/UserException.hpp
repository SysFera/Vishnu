/**
 * \file UserException.hpp
 * \brief This file defines class for the Vishnu exceptions coming from the user.
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 */
#ifndef __USEREXCEPTION__
#define __USEREXCEPTION__

#include "VishnuException.hpp"

// RESERVED CODES FROM 10 TO 19
static const int ERRCODE_INVALID_PARAM = 10;
static const int ERRCODE_FILENOTFOUND = 11;
static const int ERRCODE_CONFIGNOTFOUND = 12;
static const int ERRCODE_CLI_ERROR_NO_SESSION =13;
static const int ERRCODE_CLI_ERROR_MISSING_PARAMETER =14;
static const int ERRCODE_CLI_ERROR_DIET = 15;
static const int ERRCODE_CLI_ERROR_RUNTIME = 16;
/**
 * \brief This class represents the exception due to a user misuse
 * \class UserException
 */
class UserException :  public VishnuException {
public :
  /**
   * \brief Default constructor
   * \fn UserException()
   */
  UserException();
  /**
   * \brief Copy constructor
   * \fn UserException(const UserException& e)
   */
  UserException(const UserException& e);
  /**
   * \brief Constructor
   * \fn UserException(int msg, std::string msgComp = "")
   */
  UserException(int msg, std::string msgComp = "");
  /**
   * \brief Default destructor
   * \fn ~UserException() throw()
   */
  virtual ~UserException() throw(){};
  /**
   * \brief Function to get the exception type in string
   * \fn std::string getTypeS() const
   * \return Returns the type of the exception
   */
  std::string
  getTypeS() const;
  /**
   * \brief To get the generic message
   * \fn std::string getMsg() const
   * \return Returns the message
   */
  std::string
  getMsg() const;

protected :
  /**
   * \brief Function to initialize all the generic messages
   * \fn void initMsg()
   */
  void
  initMsg();
};

#endif // VISHNUEXCEPTION
