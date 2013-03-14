/**
 * \file api_tms.cpp
 * \brief This file contains the VISHNU api functions for TMS package.
 * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
 * \date March 2011
 */

#include <vector>
#include "api_tms.hpp"
#include "api_ums.hpp"
#include "utilVishnu.hpp"
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

//UMS include
#include "SessionProxy.hpp"
#include "MachineProxy.hpp"
#include "LocalAccountProxy.hpp"
#include "ConfigurationProxy.hpp"
#include "OptionValueProxy.hpp"
#include "QueryProxy.hpp"
#include "utilVishnu.hpp"

//TMS include
#include "JobProxy.hpp"
#include "JobOutputProxy.hpp"
#include "WorkProxy.hpp"
#include "tmsUtils.hpp"
#include "TMSServices.hpp"


using namespace TMS_Data;


/**
 * \brief The submitJob function submits job on a machine through a script pointed by scriptFilePath.
 * \param sessionKey : The session key
 * \param machineId : Is the id of the machine on which the job must be submitted
 * \param scriptFilePath : The path to the file containing the characteristics (job command, and batch scheduler directive required or optional) of the job to submit.
 * \param jobInfo : The  Job object containing the output information (ex: jobId and jobPath) of the job to submit
 * \param options : Is an instance of the class SubmitOptions. Each option is associated to a set operation (e.g: setNbCpu(...)) in the class.  If no set operation is not called on the instance object  options, the job is submitted with the options defined in the scriptFilePath. Otherewise the job is submitted with the optionnal values set by the options object and optionnal values defined in the scriptFilePath, but optionnal values set by SubmitOptions object take precedence over those in scriptFilePath. With in the object options or within the scriptFilePath, the last occurance of an optionnal value takes precedence over earlier occurance.
 * \return int : an error code
 */
int
vishnu::submitJob(const std::string& sessionKey,
                  const std::string& machineId,
                  const std::string& scriptFilePath,
                  Job& jobInfo,
                  const SubmitOptions& options)
throw (UMSVishnuException, TMSVishnuException, UserException, SystemException) {

  checkEmptyString(sessionKey, "The session key");
  checkEmptyString(machineId, "The machine id");
  //To check options value nbNodesAndCpuPerNode
  checkJobNbNodesAndNbCpuPerNode(options.getNbNodesAndCpuPerNode());

  SessionProxy sessionProxy(sessionKey);
  boost::filesystem::path completePath(scriptFilePath);
  std::string scriptFileCompletePath = (boost::filesystem::path(boost::filesystem::system_complete(completePath))).string();
  jobInfo.setJobPath(scriptFileCompletePath);

  std::string scriptContent = vishnu::get_file_content(scriptFilePath);

  JobProxy jobProxy(sessionProxy , machineId , jobInfo);

  ListStrings fileParamsVec;
  std::string fileParamsStr = options.getFileParams() ;
  boost::trim(fileParamsStr) ; //TODO BUG when empty list
  boost::split(fileParamsVec, fileParamsStr, boost::is_any_of(" "), boost::token_compress_on) ;

  int ret = jobProxy.submitJob(scriptContent, options);
  jobInfo = jobProxy.getData();

  return ret;
}

/**
 * \brief The cancelJob function cancels a job from its id
 * \param sessionKey : The session key
 * \param machineId : The id of the machine
 * \param jobId : The Id of the job
 * \param infoMsg : The information message
 * \return int : an error code
 */
int
vishnu::cancelJob(const std::string& sessionKey,
                  const std::string& machineId,
                  const std::string& jobId)
throw (UMSVishnuException, TMSVishnuException, UserException, SystemException) {

  checkEmptyString(sessionKey, "The session key");
  checkEmptyString(machineId, "The machine id");
  checkEmptyString(jobId, "The job id");

  SessionProxy sessionProxy(sessionKey);

  TMS_Data::Job job;
  job.setJobId(jobId);

  return JobProxy(sessionProxy,
                  machineId,
                  job).cancelJob();

}


/**
 * \brief The getJobInfo function gets a specific job's information
bInfo function gets information on a job from its id
 * \param sessionKey : The session key
 * \param machineId : The id of the machine
 * \param jobId : The id of the job
 * \param jobInfos : The resulting information on the job
 * \return int : an error code
 */
int
vishnu::getJobInfo(const std::string& sessionKey,
                   const std::string& machineId,
                   const std::string& jobId,
                   Job& jobInfo)
throw (UMSVishnuException, TMSVishnuException, UserException, SystemException) {

  checkEmptyString(sessionKey, "The session key");
  checkEmptyString(machineId, "The machine id");
  checkEmptyString(jobId, "The job id");

  SessionProxy sessionProxy(sessionKey);
  jobInfo.setJobId(jobId);

  JobProxy jobProxy(sessionProxy,
                    machineId,
                    jobInfo);

  jobInfo = jobProxy.getJobInfo();

  return 0;

}

/**
 * \brief The listJobs function gets a list of all submitted jobs
 * \param sessionKey : The session key
 * \param machineId : The id of the machine
 * \param listOfJobs : The constructed object list of jobs
 * \param options : Additional options for jobs listing
 * \return int : an error code
 */
int
vishnu::listJobs(const std::string& sessionKey,
                 const std::string& machineId,
                 ListJobs& listOfJobs,
                 const ListJobsOptions& options)
throw (UMSVishnuException, TMSVishnuException, UserException, SystemException) {
  checkEmptyString(sessionKey, "The session key");
  checkEmptyString(machineId, "The machine id");

  UMS_Data::ListMachines machines;
  UMS_Data::Machine_ptr machine;
  if (machineId == LIST_JOBS_ON_MACHINES_KEYWORD) {
    // First list all machines where the user has a local account
    UMS_Data::ListMachineOptions mopts;
    mopts.setListAllMachine(false);
    mopts.setMachineId("");
    listMachines(sessionKey, machines, mopts) ;
  } else {
    // Here the list of machine will contain only a single machine
    machine = new UMS_Data::Machine();
    machine->setMachineId(machineId);
    machines.getMachines().push_back(machine);
  }

  // Now iterate through all the machines to list jobs according to the query filter
  listOfJobs.setNbJobs(0);
  listOfJobs.setNbRunningJobs(0);
  listOfJobs.setNbWaitingJobs(0);
  for (int i=0; i< machines.getMachines().size(); i++) {
    machine = machines.getMachines().get(i) ;
    std::string serviceName = std::string(SERVICES_TMS[GETLISTOFJOBS]) + "@";
    serviceName.append(machine->getMachineId());
    SessionProxy sessionProxy(sessionKey);

    checkJobStatus(options.getStatus()); //To check the job status options
    checkJobPriority(options.getPriority()); //To check the job priority options

    QueryProxy<TMS_Data::ListJobsOptions, TMS_Data::ListJobs>
        query(options, sessionProxy, serviceName, machine->getMachineId());
    TMS_Data::ListJobs* listJobs_ptr = NULL;
    try {
      listJobs_ptr = query.list();
    } catch(...) {
      // This means the machine is not active or the user doesn't have a local account on it
      if (machineId != LIST_JOBS_ON_MACHINES_KEYWORD) {
        throw ;
      } else {
        continue ;
      }
    }
    if (listJobs_ptr != NULL) {
      TMS_Data::TMS_DataFactory_ptr ecoreFactory = TMS_Data::TMS_DataFactory::_instance();
      for (unsigned int j = 0; j < listJobs_ptr->getJobs().size(); j++) {
        TMS_Data::Job_ptr job = ecoreFactory->createJob();
        //To copy the content and not the pointer
        *job = *listJobs_ptr->getJobs().get(j);
        listOfJobs.getJobs().push_back(job);
      }
      listOfJobs.setNbJobs(listOfJobs.getNbJobs()+listJobs_ptr->getJobs().size());
      listOfJobs.setNbRunningJobs(listOfJobs.getNbRunningJobs()+listJobs_ptr->getNbRunningJobs());
      listOfJobs.setNbWaitingJobs(listOfJobs.getNbWaitingJobs()+listJobs_ptr->getNbWaitingJobs());
      delete listJobs_ptr;
    }
  }
  return 0;
}

/**
 * \brief The getJobProgress function gets the progression status of jobs
 * \param sessionKey : The session key
 * \param machineId : Is the id of the machine to get the jobs progression.
 * \param listOfProgress : Is the object containing jobs progression information
 * \param options : Is an object containing the available options jobs for progression .
 * \return int : an error code
 */
int
vishnu::getJobProgress(const std::string& sessionKey,
                       const std::string& machineId,
                       ListProgression& listOfProgress,
                       const ProgressOptions& options)
throw (UMSVishnuException, TMSVishnuException, UserException, SystemException) {
  checkEmptyString(sessionKey, "The session key");
  checkEmptyString(machineId, "The machine id");

  UMS_Data::ListMachines machines;
  UMS_Data::Machine_ptr machine;

  if(machineId == LIST_JOBS_ON_MACHINES_KEYWORD) {
    // First list all machines where we have a local account
    UMS_Data::ListMachineOptions mopts;
    mopts.setListAllMachine(false);
    mopts.setMachineId("");
    listMachines(sessionKey, machines, mopts) ;
  } else {
    // Here the list of machine will contain only a single machine
    machine = new UMS_Data::Machine();
    machine->setMachineId(machineId);
    machines.getMachines().push_back(machine);
  }

  // Now iterate through all the machines to list queues according to the query filter
  listOfProgress.setNbJobs(0);
  for(int i=0; i< machines.getMachines().size(); i++) {
    machine = machines.getMachines().get(i) ;
    std::string serviceName = std::string(SERVICES_TMS[GETJOBSPROGRESSION]) + "@";
    serviceName.append(machine->getMachineId());

    SessionProxy sessionProxy(sessionKey);
    QueryProxy<TMS_Data::ProgressOptions, TMS_Data::ListProgression>
        query(options, sessionProxy, serviceName, machine->getMachineId());

    TMS_Data::ListProgression* listProgression_ptr = NULL ;
    try {
      listProgression_ptr = query.list();
    } catch(...) {
      // This means the machine is not active
      // or we don't have a local account on it
      if(machineId != LIST_JOBS_ON_MACHINES_KEYWORD) {
        throw ;
      } else {
        continue ;
      }
    }

    if(listProgression_ptr != NULL) {
      TMS_Data::TMS_DataFactory_ptr ecoreFactory = TMS_Data::TMS_DataFactory::_instance();
      for(unsigned int i = 0; i < listProgression_ptr->getProgress().size(); i++) {
        TMS_Data::Progression_ptr progression = ecoreFactory->createProgression();
        //To copy the content and not the pointer
        *progression = *listProgression_ptr->getProgress().get(i);
        listOfProgress.getProgress().push_back(progression);
      }
      listOfProgress.setNbJobs(listOfProgress.getNbJobs()+listProgression_ptr->getProgress().size());
      delete listProgression_ptr;
    }
  }

  return 0;
}

/**
 * \brief The listQueues function gets queues information
 * \param sessionKey : The session key
 * \param machineId : The id of the machine
 * \param listofQueues : The list of queues
 * \param queueName The option value, if it is given, listQueues gives information only of this queue
 * \return int : an error code
 */
int
vishnu::listQueues(const std::string& sessionKey,
                   const std::string& machineId,
                   ListQueues& listofQueues,
                   const std::string& queueName)
throw (UMSVishnuException, TMSVishnuException, UserException, SystemException) {
  checkEmptyString(sessionKey, "The session key");
  checkEmptyString(machineId, "The machine id");

  UMS_Data::ListMachines machines;
  UMS_Data::Machine_ptr machine;

  if(machineId == LIST_JOBS_ON_MACHINES_KEYWORD) {
    // First list all the machines where we have a local account
    UMS_Data::ListMachineOptions mopts;
    mopts.setListAllMachine(false);
    mopts.setMachineId("");
    listMachines(sessionKey, machines, mopts) ;
  } else {
    machine = new UMS_Data::Machine();
    machine->setMachineId(machineId);
    machines.getMachines().push_back(machine);
  }

  // Now iterate through all the machines to list queues according to the query filter
  listofQueues.setNbQueues(0);
  for(int i=0; i< machines.getMachines().size(); i++) {
    machine = machines.getMachines().get(i) ;
    std::string serviceName = std::string(SERVICES_TMS[GETLISTOFQUEUES]) + "@";
    serviceName.append(machine->getMachineId());

    SessionProxy sessionProxy(sessionKey);
    QueryProxy<std::string, TMS_Data::ListQueues>
        query(queueName, sessionProxy, serviceName, machine->getMachineId());

    TMS_Data::ListQueues* listQueues_ptr = NULL ;
    try {
      listQueues_ptr = query.list();
    } catch(...) {
      // This means the machine is not active
      // or we don't have a local account on it
      if(machineId != LIST_JOBS_ON_MACHINES_KEYWORD) {
        throw ;
      } else {
        continue ;
      }
    }

    if(listQueues_ptr != NULL) {
      TMS_Data::TMS_DataFactory_ptr ecoreFactory = TMS_Data::TMS_DataFactory::_instance();
      for(unsigned int i = 0; i < listQueues_ptr->getQueues().size(); i++) {
        TMS_Data::Queue_ptr queue = ecoreFactory->createQueue();
        //To copy the content and not the pointer
        *queue = *listQueues_ptr->getQueues().get(i);
        listofQueues.getQueues().push_back(queue);
      }
      listofQueues.setNbQueues(listofQueues.getNbQueues()+listQueues_ptr->getQueues().size());
      delete listQueues_ptr;
    }
  }
  return 0;
}

/**
 * \brief The getJobOutput function gets outputPath and errorPath of a job from its id
 * \param sessionKey : The session key
 * \param machineId : The Id of the machine
 * \param jobId : The Id of the job
 * \param outputInfo : The  Job object  containing the job output information (ex: outputPath and errorPath) of the job to submit
 * \param outDir : The output directory where the files will be stored (default is current directory)
 * \return int : an error code
 */
int
vishnu::getJobOutput(const std::string& sessionKey,
                     const std::string& machineId,
                     const std::string& jobId,
                     JobResult& outputInfo,
                     const std::string& outDir)
throw (UMSVishnuException, TMSVishnuException, UserException, SystemException) {

  checkEmptyString(sessionKey, "The session key");
  checkEmptyString(machineId, "The machine id");

  if((outDir.size()!=0)&&(!boost::filesystem::exists(outDir))) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM, "The directory "+outDir+" does not exist");
  }

  SessionProxy sessionProxy(sessionKey);
  JobOutputProxy jobOutputProxy(sessionProxy, machineId, outDir);

  outputInfo = jobOutputProxy.getJobOutPut(jobId);

  return 0;
}

/**
 * \brief The getCompletedJobsOutput() function gets standard output and error output files
 * of completed jobs (applies only once for each job)
 * \param sessionKey : The session key
 * \param machineId : The id of the machine
 * \param listOfResults : Is the list of jobs results
 * \param outDir : The output directory where the files will be stored (default is current directory)
 * \return int : an error code
 */
int
vishnu::getCompletedJobsOutput(const std::string& sessionKey,
                               const std::string& machineId,
                               ListJobResults& listOfResults,
                               const std::string& outDir)
throw (UMSVishnuException, TMSVishnuException, UserException, SystemException) {

  checkEmptyString(sessionKey, "The session key");
  checkEmptyString(machineId, "The machine id");

  if((outDir.size()!=0)&&(!boost::filesystem::exists(outDir))) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM, "The directory "+outDir+" does not exist");
  }

  SessionProxy sessionProxy(sessionKey);
  JobOutputProxy jobOutputProxy(sessionProxy, machineId, outDir);

  TMS_Data::ListJobResults_ptr listJobResults_ptr = jobOutputProxy.getCompletedJobsOutput();

  if(listJobResults_ptr != NULL) {
    TMS_Data::TMS_DataFactory_ptr ecoreFactory = TMS_Data::TMS_DataFactory::_instance();
    for(unsigned int i = 0; i < listJobResults_ptr->getResults().size(); i++) {
      TMS_Data::JobResult_ptr jobResult = ecoreFactory->createJobResult();
      //To copy the content and not the pointer
      *jobResult = *listJobResults_ptr->getResults().get(i);
      listOfResults.getResults().push_back(jobResult);
    }
    listOfResults.setNbJobs(listJobResults_ptr->getNbJobs());
    delete listJobResults_ptr;
  }
  return 0;
}

int
vishnu::addWork(const std::string& sessionKey,
                Work& newWork,
                const AddWorkOptions& options)
throw (UMSVishnuException, TMSVishnuException, UserException, SystemException){
  checkEmptyString(sessionKey, "The session key");
  SessionProxy sessionProxy(sessionKey);
  WorkProxy workProxy(newWork, sessionProxy);
  int res = workProxy.add(options);
  newWork = workProxy.getData();
  return res;
}
