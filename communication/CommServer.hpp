/**
 * \file CommServer.hpp
 * This file defines some utilitaries functions that use both the communication layer, the database layer, the core layer
 * \author Kevin Coulomb (kevin.coulomb@sysfera.com)
 */

#ifndef __COMMSERVER__HH__
#define __COMMSERVER__HH__

#include <boost/shared_ptr.hpp>
#include "ExecConfiguration.hpp"
#include "SeD.hpp"

/**
 * \brief Function to unregister a server (from the annuary and database)
 * \param type the type of the server
 * \param config the configuration file
 * \return 0 currently
 */
int
unregisterSeD(const std::string& type, const ExecConfiguration& config);

/**
 * \brief Function to validate an URI
 * \throws a VishnuException if contains the '*'
 * \param uri the uri to check
 */
void
validateUri(const std::string & uri);

/**
 * \brief Register a server (in both the annuary and database)
 * \param type the type of the server
 * \param config the configuration file
 * \param services the list of the offered services
 * \return 0 on SUCCESS
 */
int
registerSeD(const std::string& type, const ExecConfiguration& config,
            std::vector<std::string>& services);

/**
 * \brief initSeD registers services and starts the SeD
 * \param type the type of the SeD (fmssed, imssed, tmssed, umssed)
 * \param config the SeD configuration
 * \param uri SeD URI
 * \param server the SeD
 */
void
initSeD(const std::string& type, const ExecConfiguration& config,
        const std::string& uri, boost::shared_ptr<SeD> server);


#endif  // __COMMSERVER__HH__
