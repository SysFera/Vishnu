/**
 * \file SystemException.hpp
 * \brief This file defines the super class for the Vishnu exceptions.
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 */
#ifndef __SYSTEMEXCEPTION__
#define __SYSTEMEXCEPTION__

#include <string>
#include "VishnuException.hpp"

// RESERVED CODES FROM 1 TO 9 plus negative values
// TODO describe the error codes
static const int ERRCODE_AUTHENTERR = -1;
static const int ERRCODE_DIET = 1;
static const int ERRCODE_DBERR = 2;
static const int ERRCODE_DBCONN = 3;
static const int ERRCODE_SYSTEM = 4;
static const int ERRCODE_INVCOMP = 5;
static const int ERRCODE_INVMAPPER = 6;
static const int ERRCODE_INVEXCEP = 7;
static const int ERRCODE_INVDATA = 8;
static const int ERRCODE_SSH = 9;

/**
 * \brief This class represents the exception that are due to the system
 * \class SystemException
 */
class SystemException : public VishnuException {

public:

  /**
   * \brief Default constructor
   * \fn SystemException()
   */
  SystemException();
  /**
   * \brief Copy constructor
   * \fn SystemException(const SystemException& e)
   */
  SystemException(const SystemException& e);
  /**
   * \brief Constructor
   * \fn SystemException(int msg, std::string msgComp = "")
   */
  SystemException(int msg, std::string msgComp = "");
  /**
   * \brief Default destructor
   * \fn ~SystemException()
   */
  virtual ~SystemException() throw(){};
  /**
   * \brief To get the generic message
   * \fn std::string getMsg() const
   * \return Returns the message
   */
  std::string
  getMsg() const;
  /**
   * \brief Function to get the exception type in string
   * \fn std::string getTypeS() const
   * \return Returns the type of the exception
   */
  std::string
  getTypeS() const;
  /**
   * \brief Function to initialize all the generic messages
   * \fn void initMsg()
   */
  void
  initMsg();
};

#endif // VISHNUEXCEPTION
