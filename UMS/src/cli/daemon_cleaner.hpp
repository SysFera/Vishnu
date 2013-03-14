#ifndef DAEMON_CLEANER_HPP
#define DAEMON_CLEANER_HPP
/**
 * \file daemon_cleaner.hpp
 * \brief This file defines a few functions to close properly session
 * and clean the corresponding file.
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 * \author Haikel Guemar (haikel.guemar@sysfera.com)
 */

/* Posix headers */
#include <string>                       // for string
#include <fcntl.h>

/* Boost headers */
#include <boost/scoped_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace bfs = boost::filesystem;
namespace bi = boost::interprocess;
namespace btt = boost::this_thread;
namespace bpt = boost::posix_time;
/**
 * \brief Check if the pid exists
 * \fn bool pid_exists(const std::string& pid)
 * \param pid The given pid
 * \return True if the pid exists
 */
bool
pid_exists(const std::string& pid);

/**
 * \brief Deletes the file corresponding to the terminal closed
 * \param configFile: The VISHNU configuration file
 * \param ac: The number of command parameters
 * \param av: The names of parameters
 */
void
deleter(char* configFile,int ac,char* av[]);

/**
 * \brief Creates a child process and call the deleter() function
 * \param configFile: The VISHNU configuration file
 * \param ac: The number of command parameters
 * \param av: The names of parameters
 */

void
cleaner(char* configFile,int ac,char* av[]);

#endif
