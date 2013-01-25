
#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include <string>

namespace vishnu {
  /**
   * \brief Define a constant type
   */
  typedef enum {
    NONE_PARAMETER,
    BOOL_PARAMETER,
    INT_PARAMETER,
    ULONG_PARAMETER,
    STRING_PARAMETER,
    URI_PARAMETER
  } c_type_t ;

  /**
 * \brief Define a parameter type
 */

  typedef enum {
    VISHNUID=0,
    DBTYPE,
    DBHOST,
    DBPORT,
    DBNAME,
    DBUSERNAME,
    DBPASSWORD,
    SENDMAILSCRIPT,
    BATCHTYPE,
    BATCHVERSION,
    MACHINEID,
    TIMEOUT,
    REMOTEBINDIR,
    INTERVALMONITOR,
    DBPOOLSIZE,
    AUTHENTYPE,
    DEFAULTBATCHCONFIGFILE,
    URLSUPERVISOR,
    DISP_URIADDR,
    DISP_URISUBS,
    DISP_NBTHREAD,
    FMS_URIADDR,
    IMS_URIADDR,
    TMS_URIADDR,
    UMS_URIADDR
  } param_type_t;

  /**
   * \brief A convenient data type to store a parameter
   */
  struct param_t {
    /**
     * \brief key to retrieve the parameter
     */
    param_type_t key;
    /**
     * \brief the value of the parameter
     */
    const std::string value;
    /**
    * \brief the type of the parameter
    */
    c_type_t type;
  };

  /**
   * \brief An arry to store all paraeters
   */
  extern param_t params[]; //%RELAX<MISRA_3_1_3> Because this table is defined in constants.cpp
}

#endif /* _CONSTANTS_HPP_ */
