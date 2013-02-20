/**
 * \file listHistoryCmdUtils.cpp
 * \brief This file defines useful functions and types for the VISHNU list history
 *  command
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 */



#include "Options.hpp"

#include "listHistoryCmdUtils.hpp"
#include<iostream>
using namespace std;

/**
 * \brief To build options for the VISHNU list history command
 * \param pgName : The name of the command
 * \param fUserId: The user identifier option callback
 * \param configFile: Represents the VISHNU config file
 * \param fSessionId : The callback for the session identifier
 * \param startDateOption: The start date option
 * \param endDateOption: The end date option
 * \return The description of all options allowed by the command
 */
boost::shared_ptr<Options> 
makeListHistoryCmdOptions(std::string pgName,StringcallBackType& fUserId,std::string & configFile,
                          StringcallBackType& fSessionId,
                          std::string& startDateOption,
                          std::string& endDateOption){


  boost::shared_ptr<Options> opt(new Options(pgName));


  opt->add("configFile,c",
           "VISHNU configuration file",
           ENV,
           configFile);

  opt->add("adminListOption,a",
           "is an admin option to list with respect to all users ",
           CONFIG);

  opt->add("userId,u",
           "an admin option to precise the list\n"
           "with respect to a specific user identified by his/her userId",
           CONFIG,
           fUserId);

  opt->add("sessionId,i",
           "lists with respect to a specific session",
           CONFIG,
           fSessionId);

  opt->add("startDateOption,s",
           "allows the user to organize the list\n"
           "by providing the start date\n"
           "(in the format ""YYYY-MM-DD H:mm:ss "")",
           CONFIG,
           startDateOption);

  opt->add("endDateOption,e",
           "allows the user to organize the list\n"
           "by providing the end date \n"
           "(in the format ""YYYY-MM-DD H:mm:ss "")"
           "By default, the end date is the current day",
           CONFIG,
           endDateOption);

  return opt;

}





