/**
 * \file utilVishnu.hpp
 * \brief This file presents the utils functions of the vishnu system
 * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com) and
 *  Daouda Traoré (daouda.traore@sysfera.com and Ibrahima Cissé (ibrahima.cisse@sysfera.com)
 * \date 15/02/2011
 */

#ifndef _UTILVISHNU_H_
#define _UTILVISHNU_H_

#include <iostream>
#include <sstream>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include "Options.hpp"
#include "TMS_Data.hpp"

#include "FMSVishnuException.hpp"
#include <boost/filesystem.hpp>
#include <boost/thread/shared_mutex.hpp>
#include "UMS_Data.hpp"

using namespace boost::posix_time;
using namespace boost::gregorian;
namespace bfs=boost::filesystem;

/**
 * \enum BatchType
 * \brief The type of the Batch
 */
typedef enum {
  TORQUE = 0,/*!< For TORQUE batch type */
  LOADLEVELER = 1,/*!< For LOADLEVELER batch type */
  SLURM = 2, /*!< For SLURM batch type */
  LSF = 3, /*!< For LSF batch type */
  SGE = 4, /*!< For SGE batch type */
  PBSPRO = 5, /*!< For PBS batch type */
  POSIX = 6, /*!< For PBS batch type */
  UNDEFINED = 7 /*!< IF batch type is not defined*/
} BatchType;

/**
 * \enum LoadType
 * \brief The type of the scheduling criteria
 */
typedef enum {
	NBWAITINGJOBS = 0,
	NBJOBS = 1,
	NBRUNNINGJOBS =2
} LoadType;

static const std::string AUTOMATIC_SUBMIT_JOB_KEYWORD="autom";
static const std::string LIST_JOBS_ON_MACHINES_KEYWORD="all";
typedef std::vector<std::string> ListStrings ;
static const int UNDEFINED_VALUE=-1;
static const int LDAPTYPE=0;
static const int SSHA_METHOD=0;
static const int ACTIVE_STATUS=1;
/**
 * \brief Function to encrypt data and password
 * \param clef is the data to be encrypted
 * \param salt This string is used to perturb the algorithm
 * \return the string encrypted
 */
char*
crypt(const char* clef, const char* salt);
/**
 * \namespace vishnu
 * \brief This naspace contains utils functions of the vishnu system
 */
namespace vishnu {
static const std::string ROOTUSERNAME = "root";
static const std::string UMSMAPPERNAME = "UMS";
static const std::string TMSMAPPERNAME = "TMS";
static const std::string IMSMAPPERNAME = "IMS";
static const std::string FMSMAPPERNAME = "FMS";
static const int PASSWORD_MAX_SIZE = 8;

static boost::shared_mutex mutex;
/**
 * \brief Generic function to convert an object to string
 * \param val is a generic data to be transformed to string
 * \return the string version of val
 */
template <class T>
std::string
convertToString(T val) {
  std::ostringstream out;
  out << val;
  return out.str();
}

/**
 * \brief Function to convert a given date into correspondant long value
 * \fn long long convertToTimeType(std::string date)
 * \param date The date to convert
 * \return The converted value
 */
long long
convertToTimeType(const std::string& date);

/**
 * \brief Function to convert a string to int
 * \param  val a value to convert to int
 * \return int value of the corresponding string
 */
int
convertToInt(const std::string& val);

/**
 * \brief Function to convert a string to long int
 * \param  val a value to convert to int
 * \return int value of the corresponding string
 */
long
convertToLong(const std::string& val) ;

/**
 * \brief To crypt a password
 * \param salt The salt to use to crypt
 * \param password The password to crypt
 * \param encrypted The flag that password encryption
 * \return The crypted password
 */
std::string
cryptPassword(const std::string& salt, const std::string& password, bool encrypted = true) ;

/**
 * \brief Function to get a random number
 * \fn    int generateNumbers()
 * \return the number generated
 */
int
generateNumbers();

/**
 * \brief To retrieve the password
 * \param prompt: The message inviting the user to enter his/her password
 * \return The password entered.
 */
std::string
takePassword(const std::string& prompt);

/**
 * \brief Simple function to convert time
 * from string format (YYYY-MM-DD H:mm:ss) to
 * long integer format in seconds
 * \param ts: the time in string format
 * \return the time in long integer format in seconds
 */
std::time_t
string_to_time_t(const std::string& ts);

/**
 * \brief Simple function to convert time
 * from string format (YYYY-MM-DD H:M:S) to
 * long integer format in seconds in utc
 * \param ts: the time in string format
 * \param utcOffset: time zone in string format
 * \return the time in long integer format in seconds
 */


std::time_t string_lc_to_utc_time_t(const std::string & ts,const std::string& utcOffset);


/**
 * \brief Simple function to read the content of a regular file
 * \param filePath: the path to the file
 * \param rejectEmptyFile: tell whether empty file will be rejected
 * \return The content of the file
 */
std::string
get_file_content(const std::string& filePath, const bool& rejectEmptyFile=true);

/**
 * \brief Function to move file
 * \param src: the path of the file to move
 * \param dest: the destination where the file will be moved
 * \param filename: the name of the file in dest
 * \return raises an exception on error
 */
int
boostMoveFile(const std::string& src, const std::string& dest,  const std::string& filename="");

/**
 * \brief Function to check a numerical value
 * \param value The value to check
 * \return raises an exception on error
 */
bool isNumericalValue(const std::string& value);

/**
 * \brief Function a given walltime into string
 * \param walltime The walltime to convert
 * \return the walltime converted to string
 */
std::string convertWallTimeToString(const long& walltime);

/**
 * \brief Function a given walltime into seconds
 * \param walltime The walltime to convert
 * \return the walltime converted to seconds
 */
long convertStringToWallTime(const std::string& walltime);

/**
 * \brief Function to check the job status
 * \param status the status of the job
 * \return raises an exception on error
 */
void
checkJobStatus(const int& status);

    /**
     * \brief Return all the IP of the machines (IPV4, except 127.0.0.1)
     * \return The IP of the machine
     */
    std::vector<std::string>
    getIPList();

    /**
     * \brief Replace localhost by the IP of the machine in the path
     * \param name The string to replace the machine name
     * \param IP The IP of the machine
     */
    void
    setIP(std::string& name, std::string IP);

    /**
     * \brief Tells if the string is an IP address
     * \param name The string to test
     */
    bool
    isNotIP(std::string name);

/**
 * \brief Function to check the job priority
 * \param priority the priority of the job
 * \return raises an exception on error
 */
void
checkJobPriority(const int& priority);

/**
 * \brief Function to check the job nbNodesAndCpuPerNode
 * \param nbNodesAndCpuPerNode the number of nodes and cpu per node
 * \return raises an exception on error
 */
void
checkJobNbNodesAndNbCpuPerNode(const std::string& nbNodesAndCpuPerNode);

/**
 * \brief Function to get current time in seconds (UTC)
 * \return the time as the number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC)
 */
time_t getCurrentTimeInUTC();

/**
 * \brief Function to convert UTC time into localtime (seconds)
 * \param localtime the local time
 * \return the correspondant localtime (seconds)
 */
time_t convertUTCtimeINLocaltime(const time_t& localtime);

/**
 * \brief Function to localtime into UTC (seconds)
 * \param localtime the local time
 * \return the diffence time (seconds)
 */
time_t convertLocaltimeINUTCtime(const time_t& localtime);

/**
 * \brief Function to return the difference between localtime and UTC time (seconds)
 * \return the difference time (seconds)
 */
long diffLocaltimeUTCtime();

/**
 * \brief Function to create temporary file
 * \param fileName The name of the file to create
 * \param file_content The content of the file
 */
void createTmpFile(char* fileName, const std::string& file_content);

/**
 * \brief Function to create temporary file
 * \param fileName The name of the file to create
 * \param content The content of the file
 */
void saveInFile(const std::string & fileName, const std::string& content);

/**
 * \brief Function to create temporary file
 * \param fileName The name of the file to create
 * \param missingDesc The content of the file
 */
void recordMissingFiles(const std::string & fileName, const std::string& missingDesc);

/**
 * \brief Function to create temporary file
 * \param fileName The name of the file to create
 */
void createTmpFile(char* fileName);

/**
 * \brief Function to delete file
 * \param fileName The name of the file to create
 * \return 0 in case of success, another value otherwise
 */
int deleteFile(const char* fileName);

/**
 * \brief Function to print success message
 */
inline void printSuccessMessage() {
	// can be used to display a message when vishnu service was performed successfully
	;
}

/**
 * \brief Function to display the session key
 */
inline void printSessionKeyMessage() {
	// can be used to display a message containing the current session key
	;
}

/**
 * \brief Function to check the metric value
 * \param metric: the metric value
 * \return raises an exception on error
 */
void
checkMetricHistoryValue(const int& metric);

/**
 * \brief Function to check the remote file path
 * \param path the remote file path
 * \return raises an exception on error
 */
void
checkRemotePath(const std::string& path);

/**
 * \brief Check if the pid exists
 * \param pid The given pid
 * \param proc_dir The given process info directory
 * \return True if the pid exists
 */
bool
process_exists(const std::string& pid, const bfs::path& proc_dir="/proc");

/**
 * \brief Get the fully qualified name for the current system
 * \param port the port
 * \return the fully qualified name for the current system
 */
std::string getLocalMachineName(const std::string& port );

/**
 * \brief Function to check if a string is empty
 * \param str The string to check
 * \param compMsg The complementary message to print
 * \return raises an exception on error
 */
void
checkEmptyString(const std::string& str,
		const std::string& compMsg);

/**
 * \brief Function to parse textual or file parameters
 * \param IN opt A structure containing the set of submitted options
 * \param OUT paramStr a string containing all of parameters
 * \param IN paramOptName the name of the option for a single parameter
 * \param IN paramsVector a vector of parameters
 * \return true if all parameters are syntaxicaly valid
 */
int
validateParameters(const boost::shared_ptr<Options> & opt,
		std::string & paramsStr,
		const std::string & paramOptName,
		const std::vector<std::string> & paramsVector);


/**
 * \brief Function to list file containing in a directory
 * \param fileNames the names of files containing in the directory
 * \param dirPath The path of the directory
 * \return true on success and false if not
 * */
bool
appendFilesFromDir(std::ostringstream & fileNames, const std::string & dirPath);


/**
 * \brief Function to get the list of output files related to a job
 * \param result : The Job Result
 * \param appendJobId : Determine whether or not append the job id before the files lists
 * \return The list of files
 * Throw exception on error
 * */
std::string
getResultFiles(const TMS_Data::JobResult & result,
		const bool & appendJobId);



/**
 * \brief Function to create a directory
 * \param dirPath The path of the directory
 * Throw exception on error
 * */
void
createOutputDir(std::string& dirPath);

/**
 * \brief Function to create a unique file suffix with the current time
 * \return tha suffix created
 * */
std::string createSuffixFromCurTime() ;

/**
 * \brief Function to make a link from a given
 * \param src : the source file
 * \return the path of the link
 * Throw exception on error
 */
std::string
mklink(const std::string& src) ;

 /**
   * \brief Function to parse the string representing the version
   * \param version the string representing the version
   * \return  The version object
   */
  UMS_Data::Version_ptr
  parseVersion(const std::string& version);


/**
 * \brief Source an configuration file
 * \param filePath: the path to the file
 */
void
sourceFile(const std::string& filePath);

} //END NAMESPACE


#endif // _UTILVISHNU_H_
