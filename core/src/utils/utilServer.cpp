/**
 * \file utilServer.cpp
 * \brief This file implements the utils functions of the vishnu system
 * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
 * \date 15/02/2011
 */

#include <boost/scoped_ptr.hpp>
#include "DatabaseResult.hpp"
#include "utilServer.hpp"
#include "utilVishnu.hpp"
#include "DbFactory.hpp"
#include "SystemException.hpp"
#include "DbFactory.hpp"
#include "zhelpers.hpp"
#include "Server.hpp"

// To get the hostname
#include <unistd.h>

using namespace std;


int
vishnu::unregisterSeD(string type, ExecConfiguration config) {
  //  string uri;
  //  string uridispatcher;
  //
  //  // Getting the machine id
  //  config.getRequiredConfigValue<std::string>(vishnu::URI, uri);
  //  config.getRequiredConfigValue<std::string>(vishnu::DISP_URISUBS, uridispatcher);
  //  zmq::context_t ctx(1);
  //  LazyPirateClient lpc(ctx, uridispatcher);
  //  std::vector<std::string> tmp;
  //  tmp.push_back("deleting");
  //
  //  boost::shared_ptr<Server> s = boost::shared_ptr<Server> (new Server(type, tmp, uri));
  //
  //  std::string req = "0"+s.get()->toString();
  //  std::cout << "sending " << req << std::endl;
  //
  //  if (!lpc.send(req)) {
  //    std::cerr << "E: request failed, exiting ...\n";
  //    exit(-1);
  //  }
  //  std::string response = lpc.recv();
  //  std::cout << "response received: ->" << response << "<- ," << response.length() <<  "\n";
  //
  return 0;
}


void
validateUri(const string & uri) {
  size_t pos = uri.find("*");
  if(pos != string::npos) {
    std::cerr << boost::format("W: character '*' is not permitted in the uri %1%\n")%uri;
    exit(-1);
  }

}

bool
vishnu::isNew(std::string urlsup, std::string mid, std::string type){
  std::string req = "select machineid from process where machineid='"+mid+"' and vishnuname='"+type+"' and dietname='"+urlsup+"'";
  DbFactory factory;
  Database *mdatabase;
  mdatabase = factory.getDatabaseInstance();
  try{
    boost::scoped_ptr<DatabaseResult> result(mdatabase->getResult(req.c_str()));
    if(result->getNbTuples() != 0) {
      return false;
    }
  }catch(SystemException& e){
    e.appendMsgComp(" Failed to determine if the process "+type + " already exist");
    throw(e);
  }
  return true;
}


int
vishnu::registerSeD(string type, ExecConfiguration config, string& cfg, std::vector<std::string>& services){
  string uri;
  string mid;
  string uridispatcher;
  string urlsup;

  // Getting the machine id
  config.getRequiredConfigValue<std::string>(vishnu::MACHINEID, mid);
  config.getRequiredConfigValue<std::string>(vishnu::DISP_URISUBS, uridispatcher);
  config.getRequiredConfigValue<std::string>(vishnu::URLSUPERVISOR, urlsup);
  if (type == "fmssed") {
    config.getRequiredConfigValue<std::string>(vishnu::FMS_URIADDR, uri);
  } else  if (type == "imssed") {
    config.getRequiredConfigValue<std::string>(vishnu::IMS_URIADDR, uri);
  } else  if (type == "tmssed") {
    config.getRequiredConfigValue<std::string>(vishnu::TMS_URIADDR, uri);
  } else { // presumably UMS
    config.getRequiredConfigValue<std::string>(vishnu::UMS_URIADDR, uri);
  }

  // Check that the uri does not contain *
  validateUri(uridispatcher);

  // Register in database
  if (isNew(urlsup, mid, type)){
    std::string request = "insert into process (dietname, launchscript, machineid, pstatus, uptime, vishnuname) values ('"+urlsup+"','"+config.scriptToString()+"','"+mid+"','"+convertToString(PRUNNING)+"',CURRENT_TIMESTAMP, '"+type+"')";
    try {
      DbFactory factory;
      Database* database = factory.getDatabaseInstance();
      database->process(request.c_str());
    } catch (SystemException& e) {
      if (type.compare("umssed")!=0){
        throw (e);
      }
    }
  }

  zmq::context_t ctx(1);
  LazyPirateClient lpc(ctx, uridispatcher);

  boost::shared_ptr<Server> s = boost::shared_ptr<Server> (new Server(type, services, uri));
  // prefix with 1 to say registering the sed
  std::string req = "1"+s.get()->toString();

  std::cout << "sending " << req << std::endl;
  if (!lpc.send(req)) {
    std::cerr << "W: failed to register in the naming service\n";
    return -1; //instead of exiting
  }
  std::string response = lpc.recv();
  std::cout << "response received: ->" << response << "<- ," << response.length() <<  "\n";

  return 0;
}


/**
* \brief Function to get a random number
* \fn    int isMonth (const char * s)
* \return
*/
int
vishnu::isMonth (const char * s) {
  return (s[0]=='M' && s[1]=='O' && s[2]=='N' && s[3]=='T' && s[4]=='H');
}
int
vishnu::isYear (const char * s) {
  return (s[0]=='Y' && s[1]=='E' && s[2]=='A' && s[3]=='R');
}
int
vishnu::isSite (const char * s) {
  return (s[0]=='S' && s[1]=='I' && s[2]=='T' && s[3]=='E');
}
int
vishnu::isType (const char * s) {
  return (s[0]=='T' && s[1]=='Y' && s[2]=='P' && s[3]=='E');
}
int
vishnu::isUName (const char * s) {
  return (s[0]=='U' && s[1]=='N' && s[2]=='A' && s[3]=='M' && s[4]=='E');
}
int
vishnu::isMaName (const char * s) {
  return (s[0]=='M' && s[1]=='A' && s[2]=='N' && s[3]=='A' && s[4]=='M' && s[5]=='E');
}
int
vishnu::isDay (const char * s) {
  return (s[0]=='D' && s[1]=='A' && s[2]=='Y');
}
int
vishnu::isCpt (const char * s) {
  return (s[0]=='C' && s[1]=='P' && s[2]=='T');
}

/**
* \brief Parse the format and fill the array with the variable and their value
* \fn void getKeywords(int* size, Format_t* array,
*                      const char* format,
*                      int cpt, IdType type,
*                      std::string name,
*                      std::string site)
* \param size Size of the array (OUT)
* \param array Array to fill with variables and their value (OUT)
* \param format The string to parse
* \param cpt Value of the counter variable
* \param type Type of the id to generate
* \param name Name of the user or machine
* \param site Site of the machine
* \return 0 on success and -1 when an error occurs
*/
int
vishnu::getKeywords (int* size, Format_t* array, const char* format, int cpt, IdType type,
std::string name, std::string site) {
  unsigned int i;
  *size = 0;

  char buf[500];
  memset (buf, 0, 500);

  //the current time
  ptime now = microsec_clock::local_time();
  boost::gregorian::date::ymd_type ymd = now.date().year_month_day();

  std::ostringstream osY, osM, osD;
  osY << ymd.year;
  std::string year = osY.str();
  osM << ymd.month;
  std::string month = osM.str();
  osD << ymd.day;
  std::string day = osD.str();

  // Loop parsing for the variables, setting their position and their value
  /* >RELAX<MISRA_6_3_1> avoid using too many brackets */
  /* >RELAX<MISRA_6_4_1> avoid using too many brackets */
  for (i=0;i<strlen (format);i++){
    if (format[i]=='$'){
      if (isDay (format+i+1)){
        array[*size].start = i;
        array[*size].end = i+3;
        array[*size].value = day;
        (*size) ++;
      }else if (isMonth (format+i+1)){
        array[*size].value = month;
        array[*size].start = i;
        array[*size].end = i+5;
        (*size) ++;
      }else if (isYear (format+i+1)){
        array[*size].start = i;
        array[*size].end = i+4;
        array[*size].value = year;
        (*size) ++;
      }else if (isCpt (format+i+1)){
        char tmp[10];
        sprintf (tmp, "%d", cpt);
        array[*size].value = std::string (tmp);
        array[*size].start = i;
        array[*size].end = i+3;
        (*size) ++;
      }else if (isSite (format+i+1)){
        array[*size].value = site;
        array[*size].start = i;
        array[*size].end = i+4;
        (*size) ++;
      }else if (isMaName (format+i+1)){
        array[*size].value = name;
        array[*size].start = i;
        array[*size].end = i+6;
        (*size) ++;
      }else if (isUName (format+i+1)){
        array[*size].value = name;
        array[*size].start = i;
        array[*size].end = i+5;
        (*size) ++;
      }else if (isType (format+i+1)) {
        switch (type){
        case 0 :
          array[*size].value = "M";
          break;
        case 1 :
          array[*size].value = "U";
          break;
        case 2 :
          array[*size].value = "J";
          break;
        case 3 :
          array[*size].value = "F";
          break;
        case 4 :
          array[*size].value = "A";
          break;
        case 5 :
          array[*size].value = "W";
          break;
        default :
          break;
        }
        array[*size].start = i;
        array[*size].end = i+4;
        (*size) ++;
      }
      else {
        return -1;
      }
    }
  }
  return 0;
}


/**
* \brief Function to generate an ID
* \fn std::string getGeneratedName (const char* format,
*                                   int cpt,
*                                   IdType type,
*                                   std::string name = "",
*                                   std::string site ="")
* \param format Format to use to generate the id
* \param cpt Value of the counter to use
* \param type Type of the id generated
* \param name Name of the user or machine (optionnal)
* \param site Site of the machine (optionnal)
*/
std::string
vishnu::getGeneratedName (const char* format, int cpt, IdType type,
std::string name , std::string site ) {

  std::string res;
  res.clear ();
  res = std::string ("");
  int  size;
  Format_t *keywords;

  keywords = new Format_t[strlen(format)+1];
  int ret = getKeywords (&size, keywords, format, cpt, type, name, site); // Getting var and their value

  // if there is no error with the getKeywords function
  if (ret != -1) {
    // Building the id using the format and the values of the var
    if (size > 0){
      res.append(format, keywords[0].start);
    } else {
      res = std::string (format);
    }
    for (int i = 0; i < size; i++){
      res.append (keywords[i].value);
      // If other variables
      if (*(format+keywords[i].end + 1) != '\0' && i!=size-1) {
        res.append (format+keywords[i].end+1, keywords[i+1].start-keywords[i].end-1);
        // If text after the variable
      }
      else if (*(format+keywords[i].end + 1) != '\0' ){
        res.append (format+keywords[i].end+1, strlen (format)-keywords[i].end-1);
      }
    }
  }
  delete [] keywords;
  return res;
}

int
vishnu::getVishnuCounter(std::string vishnuIdString, IdType type){
  DbFactory factory;
  Database *databaseVishnu;
  int ret;

  std::string table;
  std::string fields;
  std::string val;
  std::string primary;


  bool insert=true;
  switch(type) {
  case MACHINE:
    table="machine";
    fields=" (vishnu_vishnuid) ";
    val = " ("+vishnuIdString+") ";
    primary="nummachineid";
    break;
  case USER:
    table="users";
    fields=" (vishnu_vishnuid,pwd,userid) ";
    val = " ("+vishnuIdString+",'tata','titi') ";
    primary="numuserid";
    break;
  case JOB:
    table="job";
    fields=" (job_owner_id, machine_id, workId, vsession_numsessionid) ";
    val= " ((select max(numuserid) from users), (select max(nummachineid) from machine),"
    "NULL, (select max(numsessionid) from vsession)) "; //FIXME insert invalid value then update it
    primary="numjobid";
    break;
  case FILETRANSFERT:
    table="filetransfer";
    fields=" (vsession_numsessionid) ";
    val= " ((select max(numsessionid) from vsession)) "; //FIXME insert invalid value then update it
    primary="numfiletransferid";
    break;
  case AUTH:
    table="authsystem";
    fields=" (vishnu_vishnuid) ";
    val = " ("+vishnuIdString+") ";
    primary="numauthsystemid";
    break;
  case WORK:
    //FIXME : no auto-increment field in work
    fields = " (application_id"
    ",date_created,done_ratio, estimated_hours,identifier,"
    "last_updated, nbcpus, owner_id, priority, "
    "project_id, "
    "start_date, status, subject) ";
    val = " ((select min(id) from application_version),"
    " CURRENT_TIMESTAMP, 1, 1.0, 't',"
    " CURRENT_TIMESTAMP, 1, (select min(numuserid) from users), 1,"
    "(select min(id) from project), "
    "CURRENT_TIMESTAMP, 1,'toto') ";
    table = "work";
    primary="id";
    break;
  default:
    fields = " (updatefreq, formatiduser, formatidjob, formatidfiletransfer, formatidmachine, formatidauth) ";
    val = " (1, 't', 't', 't', 't', 't') ";
    table = "vishnu";
    insert=false;
    primary="vishnu_vishnuid";
    break;
  }

  databaseVishnu = factory.getDatabaseInstance();
  int tid = databaseVishnu->startTransaction();
  try{
    ret = databaseVishnu->generateId(table, fields, val, tid, primary);
  } catch (exception const & e){
    databaseVishnu->cancelTransaction(tid);
    throw e;
  }
  if(insert) {
    databaseVishnu->endTransaction(tid);
  }
  else {
    databaseVishnu->cancelTransaction(tid);
  }
  return ret;
}

/**
 * \brief To set the objectId in the specified row in the database
 * \param key : the key to identify the reserved row
 * \param objectId : the objectId to set
 * \param type : the type of the object
 */
void
vishnu::reserveObjectId(int key, std::string objectId, IdType type) {

  std::string table;
  std::string keyname;
  std::string idname;
  switch(type) {
  case MACHINE:
    table="machine";
    keyname="nummachineid";
    idname="machineid";
    break;
  case USER:
    table="users";
    keyname="numuserid";
    idname="userid";
    break;
  case JOB:
    table="job";
    keyname="numjobid";
    idname="jobid";
    break;
  case FILETRANSFERT:
    table="filetransfer";
    keyname="numfiletransferid";
    idname="transferid";
    break;
  case AUTH:
    table="authsystem";
    keyname="numauthsystemid";
    idname="authsystemid";
    break;
  case WORK:
    table="work";
    keyname="id";
    idname="identifier";
    break;
  default:
    throw SystemException(ERRCODE_SYSTEM,"Cannot reserve Object id, type in unrecognized");
    break;
  }
  std::string sqlReserve="UPDATE "+table+" ";
  sqlReserve+="set "+idname+"='"+objectId+"' ";
  sqlReserve+="where "+keyname+"="+convertToString(key)+";";

  DbFactory factory;
  try {
    factory.getDatabaseInstance()->process(sqlReserve);
  }
  catch (exception const & e)
  {
    throw SystemException(ERRCODE_SYSTEM,string("Cannot reserve Object id : ")+e.what());
  }

}

/**
 * \brief Function to get information from the table vishnu
 * \fn    string getAttrVishnu(string attrname, string vishnuid)
 * \param attrname the name of the attribut
 * \param vishnuid the id of the vishnu configuration
 * \return the corresponding attribut
 */
std::string
vishnu::getAttrVishnu(std::string attrname, std::string vishnuid, int transacId) {

  DbFactory factory;
  Database *databaseVishnu;

  std::string sqlCommand("SELECT "+attrname+" FROM vishnu where vishnuid="+vishnuid);

  databaseVishnu = factory.getDatabaseInstance();
  boost::scoped_ptr<DatabaseResult> result(databaseVishnu->getResult(sqlCommand.c_str(), transacId));
  return result->getFirstElement();

}
/**
 * \brief Function to increment a counter of the table vishnu
 * \fn    incrementCpt(std::string cptName, int cpt)
 * \param cptName the name of the counter to increment
 * \param cpt     the current value of the counter
 * \return raises an exception
 */
void
vishnu::incrementCpt(std::string cptName, int cpt, int transacId) {

  DbFactory factory;
  Database *databaseVishnu;

  cpt = cpt+1;

  std::string sqlCommand("UPDATE vishnu set "+cptName+"="+cptName+"+1");

  databaseVishnu = factory.getDatabaseInstance();
  databaseVishnu->process(sqlCommand.c_str(), transacId);

}

/**
* \brief Function to get an Id generated by VISHNU
* \param vishnuId the vishnu Id
* \param formatName the name of the format
* \return the corresponding conversion
*/
std::string
vishnu::getObjectId(int vishnuId,
std::string formatName,
IdType type,
std::string stringforgeneration) {

  std::string idGenerated;

  std::string vishnuIdString = convertToString(vishnuId);

  pthread_mutex_t mutex;
  pthread_mutex_init(&(mutex), NULL);
  pthread_mutex_lock(&(mutex));

  //To get the counter
  int counter;
  counter = getVishnuCounter(vishnuIdString,type);
  //To get the formatiduser
  std::string format = getAttrVishnu(formatName, vishnuIdString).c_str();

  if (format.size() != 0) {
    idGenerated =
    getGeneratedName(format.c_str(), counter, type, stringforgeneration);

    if (idGenerated.size() != 0) {
    } else {
      SystemException e (ERRCODE_SYSTEM, "There is a problem during the id generation with the format:"+ formatName);
      pthread_mutex_unlock(&(mutex));
      throw e;
    }
    // To set the idGenerated in the related row
    reserveObjectId(counter,idGenerated,type);

  } else {
    pthread_mutex_unlock(&(mutex));
    SystemException e (ERRCODE_SYSTEM, "The format "+ formatName +" is undefined");
    throw e;
  }
  pthread_mutex_unlock(&(mutex));
  return idGenerated;
}

/**
 * \brief Function to parse a system error message
 * \param errorMsg the error message
 * \return the parsed message
 */
std::string
vishnu::parseErrorMessage (const std::string& errorMsg) {
  size_t commandPos;
  std::string result(errorMsg);

  commandPos = result.find(":");

  if (commandPos != std::string::npos) {
    result = result.substr(commandPos + 1);

    size_t endOfLinePos = result.find_last_of("\n");
    if (endOfLinePos != std::string::npos) {
      result.erase(endOfLinePos);
    }
  }

  return result;
}
