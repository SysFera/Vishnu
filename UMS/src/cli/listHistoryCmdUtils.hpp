/**
 * \file listHistoryCmdUtils.hpp
 * \brief This file declares useful functions and types for the VISHNU list history
 *  command
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 */



#ifndef LISTHISTORYCMDUTILS__HH
#define LISTHISTORYCMDUTILS__HH

//VISHNU Headers

#include "common.hpp"

//Boost Headers

#include<boost/function.hpp>



class Options;

/**
 * \brief A convenient function type taking a string parameter and
 * without return value
 */

typedef
boost::function1<void,std::string> StringcallBackType;

/**
 * \brief The close policy option callback type
 * 
 */

typedef
boost::function1<void,UMS_Data::SessionCloseType> ClosePolicycallBackType;

/**
 * \brief The status option callback type
 * 
 */

typedef
boost::function1<void,UMS_Data::StatusType> StatuscallBackType;


/**
 * \brief A convenient function type taking a integer  parameter and
 * without return value
 */
typedef  
boost::function1<void,int> IntcallBackType;


/**
 * \brief To build options for the VISHNU list history command
 * \param pgName : The name of the command
 * \param fUserId: The user identifier option callback
 * \param configFile: Represents the VISHNU config file
 * \param fSessionId : The callback for the session identifier
 * \param startDateOption: The start date option
 * \param endDateOption: The  end date option
 * \return The description of all options allowed by the command
 */


boost::shared_ptr<Options>
makeListHistoryCmdOptions(std::string pgName,StringcallBackType& fUserId,
                          std::string & configFile, StringcallBackType& fSessionId,
												  std::string& startDateOption, std::string& endDateOption);






#endif



