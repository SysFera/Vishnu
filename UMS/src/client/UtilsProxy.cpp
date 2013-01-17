/**
 * \file UtilsProxy.cpp
 * \brief This file contains the VISHNU UtilsProxy class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#include <string>
#include <iostream>
#include <fstream>

#include "UMSVishnuException.hpp"
#include "SystemException.hpp"
#include "UtilsProxy.hpp"
#include "utilsClient.hpp"

/**
 * \fn  UtilsProxy()
 * \brief Constructor, default constructor
 */
UtilsProxy::UtilsProxy()
{
  mcfg  = NULL;
  margc = 0;
  margv = NULL;
}

/**
 * \fn UtilsProxy(char* cfg,
 *                int argc,
 char** argv)
 * \param cfg The SYSFERA-DS configuration file
 * \param argc The number of arguments of the program
 * \param argv The list of arguments
 * \brief Constructor
 */
UtilsProxy::UtilsProxy(char* cfg, int argc, char** argv):
  mcfg(cfg), margc(argc), margv(argv)
{
}

/**
 * \fn UtilsProxy(const std::string& filePath)
 * \param filePath The SYSFERA-DS configuration file
 * \brief Constructor
 */
UtilsProxy::UtilsProxy(const std::string& filePath):
  mfilePath(filePath)
{
  mcfg = NULL;
  margc = 0;
  margv = NULL;
}

/**
 * \brief Function to initialize the SYSFERA-DS configuration
 * \fn  int initialize()
 * \return 0 or GRPC code if success else raises an exception if error
 */
int
UtilsProxy::initialize() {
  int res = 0;
  try {
    res = diet_initialize(mcfg, margc, margv);
  } catch (...) {
    throw SystemException(ERRCODE_DIET, "Internal DIET Exception");
  }
  if (res == -1) {
    throw SystemException(ERRCODE_DIET, "DIET Initialization failure");
  }
  return res;
}

#ifdef BUILD_TESTING
/**
 * \brief Function to initialize the database
 * \fn  int restore()
 * \return an error code
 */
int
UtilsProxy::restore() {

  int READSIZE = 1000;
  diet_profile_t* profile = NULL;
  std::ifstream file(mfilePath.c_str(), std::ios::in);
  std::string errorInfo;
  if(!file) {
    return -1;
  }
  // While all has not been read
  while (-1 != file.tellg()){
    char* tmp = new char[READSIZE];
    file.getline(tmp, READSIZE);
    if (strcmp(tmp, "")==0){
      break;
    }
    profile = diet_profile_alloc("restore", 0, 0, 1);
    //IN Parameters
    diet_string_set(profile,0, tmp);
    //OUT Parameters
    diet_string_set(profile,1);
    delete [] tmp;
    if(!diet_call(profile)){
      if(diet_string_get(profile,1, errorInfo)) {
        raiseDietMsgException("DIET call failure");
      }
    } else {
      raiseDietMsgException("DIET call failure");
    }
    raiseExceptionIfNotEmptyMsg(errorInfo);
  }
  return 0;
}
#endif

/**
 * \fn ~UtilsProxy()
 * \brief Destructor, raises an exception on error
 */
UtilsProxy::~UtilsProxy()
{
}
