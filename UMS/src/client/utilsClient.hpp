/**
 * \file utilsClient.hpp
 * \brief This file contains client utils functions for VISHNU client Proxy classes
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#ifndef  _utilsClient_H_
#define  _utilsClient_H_

#include <string>
#include <iostream>


/**
 * \brief Function to print an error message and the line and file where this error has been occured
 * \fn  inline void errMsg(const std::string& msg)
 * \param msg to print
 */
inline void
errMsg(const std::string& msg) {
  std::cerr << "Error line " << __LINE__-1  << " in file " << __FILE__
            << " with message:\n" << msg << "\n";
}

/**
 * \brief Function to check if a text is empty
 * \param text The text to check
 * \param compMsg The complementary message to print
 * \param exceptionType The type of exception to raise
 * \exception raises an exception on error
 */
void
checkIfTextIsEmpty(const std::string& text,
                   const std::string& compMsg,
                   const int& exceptionType);

/**
 * \brief Function to check if an email is valid
 * \param mail The email to check
 * \return raises an exception on error
 */
void
checkEmail(const std::string& mail);


#endif
