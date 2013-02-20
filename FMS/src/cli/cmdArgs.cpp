/**
 * \file cmdArgs.cpp
 * This file defines the VISHNU FMS cli utility
 * \author Daouda Traore (daouda.traore@sysfera.com)
 */


#include "CLICmd.hpp"
#include "utilVishnu.hpp"
#include "cliError.hpp"
#include "cliUtil.hpp"
#include "api_ums.hpp"
#include "api_fms.hpp"
#include "sessionUtils.hpp"
#include <boost/bind.hpp>

namespace po = boost::program_options;

using namespace std;
using namespace vishnu;

/**
 * \brief To build options for the VISHNU cmdArgs command
 * \param pgName : The name of the command
 * \param configFile: Represents the VISHNU config file
 */
boost::shared_ptr<Options>
processOpt(string pgName,
    string& configFile){

  boost::shared_ptr<Options> opt(new Options(pgName));

  // Environement option
  opt->add("configFile,c",
      "VISHNU configuration file",
      ENV,
      configFile);

  return opt;
}
