// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * UMS_Data/UMS_DataPackageImpl.cpp
 * Copyright (C) Cátedra SAES-UMU 2010 <andres.senac@um.es>
 *
 * EMF4CPP is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EMF4CPP is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <UMS_Data/UMS_DataPackage.hpp>
#include <UMS_Data/UMS_DataFactory.hpp>
#include <ecore.hpp>
#include <ecore/EcorePackage.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EAttribute.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EOperation.hpp>
#include <ecore/EParameter.hpp>
#include <ecore/EEnum.hpp>
#include <ecore/EEnumLiteral.hpp>
#include <ecore/EDataType.hpp>
#include <ecore/EGenericType.hpp>
#include <ecore/ETypeParameter.hpp>
#include <ecore/EcorePackage.hpp>
#include <ecore/EcorePackage.hpp>

using namespace ::UMS_Data;

UMS_DataPackage::UMS_DataPackage()
{

    s_instance.reset(this);

    // Factory
    ::ecore::EFactory_ptr _fa = UMS_DataFactory::_instance();
    setEFactoryInstance(_fa);
    _fa->setEPackage(this);

    // Create classes and their features

    // ConnectOptions
    m_ConnectOptionsEClass = new ::ecore::EClass();
    m_ConnectOptionsEClass->setClassifierID(CONNECTOPTIONS);
    m_ConnectOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ConnectOptionsEClass);
    m_ConnectOptions__closePolicy = new ::ecore::EAttribute();
    m_ConnectOptions__closePolicy->setFeatureID(
            ::UMS_Data::UMS_DataPackage::CONNECTOPTIONS__CLOSEPOLICY);
    m_ConnectOptionsEClass->getEStructuralFeatures().push_back(
            m_ConnectOptions__closePolicy);
    m_ConnectOptions__sessionInactivityDelay = new ::ecore::EAttribute();
    m_ConnectOptions__sessionInactivityDelay->setFeatureID(
            ::UMS_Data::UMS_DataPackage::CONNECTOPTIONS__SESSIONINACTIVITYDELAY);
    m_ConnectOptionsEClass->getEStructuralFeatures().push_back(
            m_ConnectOptions__sessionInactivityDelay);
    m_ConnectOptions__substituteUserId = new ::ecore::EAttribute();
    m_ConnectOptions__substituteUserId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::CONNECTOPTIONS__SUBSTITUTEUSERID);
    m_ConnectOptionsEClass->getEStructuralFeatures().push_back(
            m_ConnectOptions__substituteUserId);

    // Session
    m_SessionEClass = new ::ecore::EClass();
    m_SessionEClass->setClassifierID(SESSION);
    m_SessionEClass->setEPackage(this);
    getEClassifiers().push_back(m_SessionEClass);
    m_Session__sessionId = new ::ecore::EAttribute();
    m_Session__sessionId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::SESSION__SESSIONID);
    m_SessionEClass->getEStructuralFeatures().push_back(m_Session__sessionId);
    m_Session__userId = new ::ecore::EAttribute();
    m_Session__userId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::SESSION__USERID);
    m_SessionEClass->getEStructuralFeatures().push_back(m_Session__userId);
    m_Session__sessionKey = new ::ecore::EAttribute();
    m_Session__sessionKey->setFeatureID(
            ::UMS_Data::UMS_DataPackage::SESSION__SESSIONKEY);
    m_SessionEClass->getEStructuralFeatures().push_back(m_Session__sessionKey);
    m_Session__dateLastConnect = new ::ecore::EAttribute();
    m_Session__dateLastConnect->setFeatureID(
            ::UMS_Data::UMS_DataPackage::SESSION__DATELASTCONNECT);
    m_SessionEClass->getEStructuralFeatures().push_back(
            m_Session__dateLastConnect);
    m_Session__dateCreation = new ::ecore::EAttribute();
    m_Session__dateCreation->setFeatureID(
            ::UMS_Data::UMS_DataPackage::SESSION__DATECREATION);
    m_SessionEClass->getEStructuralFeatures().push_back(m_Session__dateCreation);
    m_Session__dateClosure = new ::ecore::EAttribute();
    m_Session__dateClosure->setFeatureID(
            ::UMS_Data::UMS_DataPackage::SESSION__DATECLOSURE);
    m_SessionEClass->getEStructuralFeatures().push_back(m_Session__dateClosure);
    m_Session__status = new ::ecore::EAttribute();
    m_Session__status->setFeatureID(
            ::UMS_Data::UMS_DataPackage::SESSION__STATUS);
    m_SessionEClass->getEStructuralFeatures().push_back(m_Session__status);
    m_Session__closePolicy = new ::ecore::EAttribute();
    m_Session__closePolicy->setFeatureID(
            ::UMS_Data::UMS_DataPackage::SESSION__CLOSEPOLICY);
    m_SessionEClass->getEStructuralFeatures().push_back(m_Session__closePolicy);
    m_Session__timeout = new ::ecore::EAttribute();
    m_Session__timeout->setFeatureID(
            ::UMS_Data::UMS_DataPackage::SESSION__TIMEOUT);
    m_SessionEClass->getEStructuralFeatures().push_back(m_Session__timeout);
    m_Session__authenId = new ::ecore::EAttribute();
    m_Session__authenId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::SESSION__AUTHENID);
    m_SessionEClass->getEStructuralFeatures().push_back(m_Session__authenId);

    // ListSessions
    m_ListSessionsEClass = new ::ecore::EClass();
    m_ListSessionsEClass->setClassifierID(LISTSESSIONS);
    m_ListSessionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListSessionsEClass);
    m_ListSessions__sessions = new ::ecore::EReference();
    m_ListSessions__sessions->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTSESSIONS__SESSIONS);
    m_ListSessionsEClass->getEStructuralFeatures().push_back(
            m_ListSessions__sessions);

    // ListSessionOptions
    m_ListSessionOptionsEClass = new ::ecore::EClass();
    m_ListSessionOptionsEClass->setClassifierID(LISTSESSIONOPTIONS);
    m_ListSessionOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListSessionOptionsEClass);
    m_ListSessionOptions__status = new ::ecore::EAttribute();
    m_ListSessionOptions__status->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTSESSIONOPTIONS__STATUS);
    m_ListSessionOptionsEClass->getEStructuralFeatures().push_back(
            m_ListSessionOptions__status);
    m_ListSessionOptions__sessionClosePolicy = new ::ecore::EAttribute();
    m_ListSessionOptions__sessionClosePolicy->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTSESSIONOPTIONS__SESSIONCLOSEPOLICY);
    m_ListSessionOptionsEClass->getEStructuralFeatures().push_back(
            m_ListSessionOptions__sessionClosePolicy);
    m_ListSessionOptions__sessionInactivityDelay = new ::ecore::EAttribute();
    m_ListSessionOptions__sessionInactivityDelay->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTSESSIONOPTIONS__SESSIONINACTIVITYDELAY);
    m_ListSessionOptionsEClass->getEStructuralFeatures().push_back(
            m_ListSessionOptions__sessionInactivityDelay);
    m_ListSessionOptions__machineId = new ::ecore::EAttribute();
    m_ListSessionOptions__machineId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTSESSIONOPTIONS__MACHINEID);
    m_ListSessionOptionsEClass->getEStructuralFeatures().push_back(
            m_ListSessionOptions__machineId);
    m_ListSessionOptions__adminListOption = new ::ecore::EAttribute();
    m_ListSessionOptions__adminListOption->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTSESSIONOPTIONS__ADMINLISTOPTION);
    m_ListSessionOptionsEClass->getEStructuralFeatures().push_back(
            m_ListSessionOptions__adminListOption);
    m_ListSessionOptions__userId = new ::ecore::EAttribute();
    m_ListSessionOptions__userId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTSESSIONOPTIONS__USERID);
    m_ListSessionOptionsEClass->getEStructuralFeatures().push_back(
            m_ListSessionOptions__userId);
    m_ListSessionOptions__sessionId = new ::ecore::EAttribute();
    m_ListSessionOptions__sessionId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTSESSIONOPTIONS__SESSIONID);
    m_ListSessionOptionsEClass->getEStructuralFeatures().push_back(
            m_ListSessionOptions__sessionId);
    m_ListSessionOptions__startDateOption = new ::ecore::EAttribute();
    m_ListSessionOptions__startDateOption->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTSESSIONOPTIONS__STARTDATEOPTION);
    m_ListSessionOptionsEClass->getEStructuralFeatures().push_back(
            m_ListSessionOptions__startDateOption);
    m_ListSessionOptions__endDateOption = new ::ecore::EAttribute();
    m_ListSessionOptions__endDateOption->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTSESSIONOPTIONS__ENDDATEOPTION);
    m_ListSessionOptionsEClass->getEStructuralFeatures().push_back(
            m_ListSessionOptions__endDateOption);

    // User
    m_UserEClass = new ::ecore::EClass();
    m_UserEClass->setClassifierID(USER);
    m_UserEClass->setEPackage(this);
    getEClassifiers().push_back(m_UserEClass);
    m_User__userId = new ::ecore::EAttribute();
    m_User__userId->setFeatureID(::UMS_Data::UMS_DataPackage::USER__USERID);
    m_UserEClass->getEStructuralFeatures().push_back(m_User__userId);
    m_User__password = new ::ecore::EAttribute();
    m_User__password->setFeatureID(::UMS_Data::UMS_DataPackage::USER__PASSWORD);
    m_UserEClass->getEStructuralFeatures().push_back(m_User__password);
    m_User__firstname = new ::ecore::EAttribute();
    m_User__firstname->setFeatureID(
            ::UMS_Data::UMS_DataPackage::USER__FIRSTNAME);
    m_UserEClass->getEStructuralFeatures().push_back(m_User__firstname);
    m_User__lastname = new ::ecore::EAttribute();
    m_User__lastname->setFeatureID(::UMS_Data::UMS_DataPackage::USER__LASTNAME);
    m_UserEClass->getEStructuralFeatures().push_back(m_User__lastname);
    m_User__privilege = new ::ecore::EAttribute();
    m_User__privilege->setFeatureID(
            ::UMS_Data::UMS_DataPackage::USER__PRIVILEGE);
    m_UserEClass->getEStructuralFeatures().push_back(m_User__privilege);
    m_User__email = new ::ecore::EAttribute();
    m_User__email->setFeatureID(::UMS_Data::UMS_DataPackage::USER__EMAIL);
    m_UserEClass->getEStructuralFeatures().push_back(m_User__email);
    m_User__status = new ::ecore::EAttribute();
    m_User__status->setFeatureID(::UMS_Data::UMS_DataPackage::USER__STATUS);
    m_UserEClass->getEStructuralFeatures().push_back(m_User__status);

    // ListUsers
    m_ListUsersEClass = new ::ecore::EClass();
    m_ListUsersEClass->setClassifierID(LISTUSERS);
    m_ListUsersEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListUsersEClass);
    m_ListUsers__users = new ::ecore::EReference();
    m_ListUsers__users->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTUSERS__USERS);
    m_ListUsersEClass->getEStructuralFeatures().push_back(m_ListUsers__users);

    // ListUsersOptions
    m_ListUsersOptionsEClass = new ::ecore::EClass();
    m_ListUsersOptionsEClass->setClassifierID(LISTUSERSOPTIONS);
    m_ListUsersOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListUsersOptionsEClass);
    m_ListUsersOptions__userId = new ::ecore::EAttribute();
    m_ListUsersOptions__userId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTUSERSOPTIONS__USERID);
    m_ListUsersOptionsEClass->getEStructuralFeatures().push_back(
            m_ListUsersOptions__userId);
    m_ListUsersOptions__authSystemId = new ::ecore::EAttribute();
    m_ListUsersOptions__authSystemId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTUSERSOPTIONS__AUTHSYSTEMID);
    m_ListUsersOptionsEClass->getEStructuralFeatures().push_back(
            m_ListUsersOptions__authSystemId);

    // Command
    m_CommandEClass = new ::ecore::EClass();
    m_CommandEClass->setClassifierID(COMMAND);
    m_CommandEClass->setEPackage(this);
    getEClassifiers().push_back(m_CommandEClass);
    m_Command__commandId = new ::ecore::EAttribute();
    m_Command__commandId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::COMMAND__COMMANDID);
    m_CommandEClass->getEStructuralFeatures().push_back(m_Command__commandId);
    m_Command__sessionId = new ::ecore::EAttribute();
    m_Command__sessionId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::COMMAND__SESSIONID);
    m_CommandEClass->getEStructuralFeatures().push_back(m_Command__sessionId);
    m_Command__machineId = new ::ecore::EAttribute();
    m_Command__machineId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::COMMAND__MACHINEID);
    m_CommandEClass->getEStructuralFeatures().push_back(m_Command__machineId);
    m_Command__cmdDescription = new ::ecore::EAttribute();
    m_Command__cmdDescription->setFeatureID(
            ::UMS_Data::UMS_DataPackage::COMMAND__CMDDESCRIPTION);
    m_CommandEClass->getEStructuralFeatures().push_back(
            m_Command__cmdDescription);
    m_Command__cmdStartTime = new ::ecore::EAttribute();
    m_Command__cmdStartTime->setFeatureID(
            ::UMS_Data::UMS_DataPackage::COMMAND__CMDSTARTTIME);
    m_CommandEClass->getEStructuralFeatures().push_back(m_Command__cmdStartTime);
    m_Command__cmdEndTime = new ::ecore::EAttribute();
    m_Command__cmdEndTime->setFeatureID(
            ::UMS_Data::UMS_DataPackage::COMMAND__CMDENDTIME);
    m_CommandEClass->getEStructuralFeatures().push_back(m_Command__cmdEndTime);
    m_Command__status = new ::ecore::EAttribute();
    m_Command__status->setFeatureID(
            ::UMS_Data::UMS_DataPackage::COMMAND__STATUS);
    m_CommandEClass->getEStructuralFeatures().push_back(m_Command__status);

    // ListCommands
    m_ListCommandsEClass = new ::ecore::EClass();
    m_ListCommandsEClass->setClassifierID(LISTCOMMANDS);
    m_ListCommandsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListCommandsEClass);
    m_ListCommands__Commands = new ::ecore::EReference();
    m_ListCommands__Commands->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTCOMMANDS__COMMANDS);
    m_ListCommandsEClass->getEStructuralFeatures().push_back(
            m_ListCommands__Commands);

    // ListCmdOptions
    m_ListCmdOptionsEClass = new ::ecore::EClass();
    m_ListCmdOptionsEClass->setClassifierID(LISTCMDOPTIONS);
    m_ListCmdOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListCmdOptionsEClass);
    m_ListCmdOptions__adminListOption = new ::ecore::EAttribute();
    m_ListCmdOptions__adminListOption->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTCMDOPTIONS__ADMINLISTOPTION);
    m_ListCmdOptionsEClass->getEStructuralFeatures().push_back(
            m_ListCmdOptions__adminListOption);
    m_ListCmdOptions__userId = new ::ecore::EAttribute();
    m_ListCmdOptions__userId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTCMDOPTIONS__USERID);
    m_ListCmdOptionsEClass->getEStructuralFeatures().push_back(
            m_ListCmdOptions__userId);
    m_ListCmdOptions__sessionId = new ::ecore::EAttribute();
    m_ListCmdOptions__sessionId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTCMDOPTIONS__SESSIONID);
    m_ListCmdOptionsEClass->getEStructuralFeatures().push_back(
            m_ListCmdOptions__sessionId);
    m_ListCmdOptions__startDateOption = new ::ecore::EAttribute();
    m_ListCmdOptions__startDateOption->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTCMDOPTIONS__STARTDATEOPTION);
    m_ListCmdOptionsEClass->getEStructuralFeatures().push_back(
            m_ListCmdOptions__startDateOption);
    m_ListCmdOptions__endDateOption = new ::ecore::EAttribute();
    m_ListCmdOptions__endDateOption->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTCMDOPTIONS__ENDDATEOPTION);
    m_ListCmdOptionsEClass->getEStructuralFeatures().push_back(
            m_ListCmdOptions__endDateOption);

    // LocalAccount
    m_LocalAccountEClass = new ::ecore::EClass();
    m_LocalAccountEClass->setClassifierID(LOCALACCOUNT);
    m_LocalAccountEClass->setEPackage(this);
    getEClassifiers().push_back(m_LocalAccountEClass);
    m_LocalAccount__userId = new ::ecore::EAttribute();
    m_LocalAccount__userId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LOCALACCOUNT__USERID);
    m_LocalAccountEClass->getEStructuralFeatures().push_back(
            m_LocalAccount__userId);
    m_LocalAccount__machineId = new ::ecore::EAttribute();
    m_LocalAccount__machineId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LOCALACCOUNT__MACHINEID);
    m_LocalAccountEClass->getEStructuralFeatures().push_back(
            m_LocalAccount__machineId);
    m_LocalAccount__acLogin = new ::ecore::EAttribute();
    m_LocalAccount__acLogin->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LOCALACCOUNT__ACLOGIN);
    m_LocalAccountEClass->getEStructuralFeatures().push_back(
            m_LocalAccount__acLogin);
    m_LocalAccount__sshKeyPath = new ::ecore::EAttribute();
    m_LocalAccount__sshKeyPath->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LOCALACCOUNT__SSHKEYPATH);
    m_LocalAccountEClass->getEStructuralFeatures().push_back(
            m_LocalAccount__sshKeyPath);
    m_LocalAccount__homeDirectory = new ::ecore::EAttribute();
    m_LocalAccount__homeDirectory->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LOCALACCOUNT__HOMEDIRECTORY);
    m_LocalAccountEClass->getEStructuralFeatures().push_back(
            m_LocalAccount__homeDirectory);

    // ListLocalAccounts
    m_ListLocalAccountsEClass = new ::ecore::EClass();
    m_ListLocalAccountsEClass->setClassifierID(LISTLOCALACCOUNTS);
    m_ListLocalAccountsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListLocalAccountsEClass);
    m_ListLocalAccounts__accounts = new ::ecore::EReference();
    m_ListLocalAccounts__accounts->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTLOCALACCOUNTS__ACCOUNTS);
    m_ListLocalAccountsEClass->getEStructuralFeatures().push_back(
            m_ListLocalAccounts__accounts);

    // ListLocalAccOptions
    m_ListLocalAccOptionsEClass = new ::ecore::EClass();
    m_ListLocalAccOptionsEClass->setClassifierID(LISTLOCALACCOPTIONS);
    m_ListLocalAccOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListLocalAccOptionsEClass);
    m_ListLocalAccOptions__adminListOption = new ::ecore::EAttribute();
    m_ListLocalAccOptions__adminListOption->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTLOCALACCOPTIONS__ADMINLISTOPTION);
    m_ListLocalAccOptionsEClass->getEStructuralFeatures().push_back(
            m_ListLocalAccOptions__adminListOption);
    m_ListLocalAccOptions__userId = new ::ecore::EAttribute();
    m_ListLocalAccOptions__userId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTLOCALACCOPTIONS__USERID);
    m_ListLocalAccOptionsEClass->getEStructuralFeatures().push_back(
            m_ListLocalAccOptions__userId);
    m_ListLocalAccOptions__machineId = new ::ecore::EAttribute();
    m_ListLocalAccOptions__machineId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTLOCALACCOPTIONS__MACHINEID);
    m_ListLocalAccOptionsEClass->getEStructuralFeatures().push_back(
            m_ListLocalAccOptions__machineId);

    // Machine
    m_MachineEClass = new ::ecore::EClass();
    m_MachineEClass->setClassifierID(MACHINE);
    m_MachineEClass->setEPackage(this);
    getEClassifiers().push_back(m_MachineEClass);
    m_Machine__machineId = new ::ecore::EAttribute();
    m_Machine__machineId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::MACHINE__MACHINEID);
    m_MachineEClass->getEStructuralFeatures().push_back(m_Machine__machineId);
    m_Machine__name = new ::ecore::EAttribute();
    m_Machine__name->setFeatureID(::UMS_Data::UMS_DataPackage::MACHINE__NAME);
    m_MachineEClass->getEStructuralFeatures().push_back(m_Machine__name);
    m_Machine__site = new ::ecore::EAttribute();
    m_Machine__site->setFeatureID(::UMS_Data::UMS_DataPackage::MACHINE__SITE);
    m_MachineEClass->getEStructuralFeatures().push_back(m_Machine__site);
    m_Machine__machineDescription = new ::ecore::EAttribute();
    m_Machine__machineDescription->setFeatureID(
            ::UMS_Data::UMS_DataPackage::MACHINE__MACHINEDESCRIPTION);
    m_MachineEClass->getEStructuralFeatures().push_back(
            m_Machine__machineDescription);
    m_Machine__language = new ::ecore::EAttribute();
    m_Machine__language->setFeatureID(
            ::UMS_Data::UMS_DataPackage::MACHINE__LANGUAGE);
    m_MachineEClass->getEStructuralFeatures().push_back(m_Machine__language);
    m_Machine__status = new ::ecore::EAttribute();
    m_Machine__status->setFeatureID(
            ::UMS_Data::UMS_DataPackage::MACHINE__STATUS);
    m_MachineEClass->getEStructuralFeatures().push_back(m_Machine__status);
    m_Machine__sshPublicKey = new ::ecore::EAttribute();
    m_Machine__sshPublicKey->setFeatureID(
            ::UMS_Data::UMS_DataPackage::MACHINE__SSHPUBLICKEY);
    m_MachineEClass->getEStructuralFeatures().push_back(m_Machine__sshPublicKey);

    // ListMachines
    m_ListMachinesEClass = new ::ecore::EClass();
    m_ListMachinesEClass->setClassifierID(LISTMACHINES);
    m_ListMachinesEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListMachinesEClass);
    m_ListMachines__machines = new ::ecore::EReference();
    m_ListMachines__machines->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTMACHINES__MACHINES);
    m_ListMachinesEClass->getEStructuralFeatures().push_back(
            m_ListMachines__machines);

    // ListMachineOptions
    m_ListMachineOptionsEClass = new ::ecore::EClass();
    m_ListMachineOptionsEClass->setClassifierID(LISTMACHINEOPTIONS);
    m_ListMachineOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListMachineOptionsEClass);
    m_ListMachineOptions__userId = new ::ecore::EAttribute();
    m_ListMachineOptions__userId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTMACHINEOPTIONS__USERID);
    m_ListMachineOptionsEClass->getEStructuralFeatures().push_back(
            m_ListMachineOptions__userId);
    m_ListMachineOptions__listAllMachine = new ::ecore::EAttribute();
    m_ListMachineOptions__listAllMachine->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTMACHINEOPTIONS__LISTALLMACHINE);
    m_ListMachineOptionsEClass->getEStructuralFeatures().push_back(
            m_ListMachineOptions__listAllMachine);
    m_ListMachineOptions__machineId = new ::ecore::EAttribute();
    m_ListMachineOptions__machineId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTMACHINEOPTIONS__MACHINEID);
    m_ListMachineOptionsEClass->getEStructuralFeatures().push_back(
            m_ListMachineOptions__machineId);

    // Configuration
    m_ConfigurationEClass = new ::ecore::EClass();
    m_ConfigurationEClass->setClassifierID(CONFIGURATION);
    m_ConfigurationEClass->setEPackage(this);
    getEClassifiers().push_back(m_ConfigurationEClass);
    m_Configuration__filePath = new ::ecore::EAttribute();
    m_Configuration__filePath->setFeatureID(
            ::UMS_Data::UMS_DataPackage::CONFIGURATION__FILEPATH);
    m_ConfigurationEClass->getEStructuralFeatures().push_back(
            m_Configuration__filePath);
    m_Configuration__listConfUsers = new ::ecore::EReference();
    m_Configuration__listConfUsers->setFeatureID(
            ::UMS_Data::UMS_DataPackage::CONFIGURATION__LISTCONFUSERS);
    m_ConfigurationEClass->getEStructuralFeatures().push_back(
            m_Configuration__listConfUsers);
    m_Configuration__listConfMachines = new ::ecore::EReference();
    m_Configuration__listConfMachines->setFeatureID(
            ::UMS_Data::UMS_DataPackage::CONFIGURATION__LISTCONFMACHINES);
    m_ConfigurationEClass->getEStructuralFeatures().push_back(
            m_Configuration__listConfMachines);
    m_Configuration__listConfLocalAccounts = new ::ecore::EReference();
    m_Configuration__listConfLocalAccounts->setFeatureID(
            ::UMS_Data::UMS_DataPackage::CONFIGURATION__LISTCONFLOCALACCOUNTS);
    m_ConfigurationEClass->getEStructuralFeatures().push_back(
            m_Configuration__listConfLocalAccounts);
    m_Configuration__ListConfAuthSystems = new ::ecore::EReference();
    m_Configuration__ListConfAuthSystems->setFeatureID(
            ::UMS_Data::UMS_DataPackage::CONFIGURATION__LISTCONFAUTHSYSTEMS);
    m_ConfigurationEClass->getEStructuralFeatures().push_back(
            m_Configuration__ListConfAuthSystems);
    m_Configuration__ListConfAuthAccounts = new ::ecore::EReference();
    m_Configuration__ListConfAuthAccounts->setFeatureID(
            ::UMS_Data::UMS_DataPackage::CONFIGURATION__LISTCONFAUTHACCOUNTS);
    m_ConfigurationEClass->getEStructuralFeatures().push_back(
            m_Configuration__ListConfAuthAccounts);

    // OptionValue
    m_OptionValueEClass = new ::ecore::EClass();
    m_OptionValueEClass->setClassifierID(OPTIONVALUE);
    m_OptionValueEClass->setEPackage(this);
    getEClassifiers().push_back(m_OptionValueEClass);
    m_OptionValue__optionName = new ::ecore::EAttribute();
    m_OptionValue__optionName->setFeatureID(
            ::UMS_Data::UMS_DataPackage::OPTIONVALUE__OPTIONNAME);
    m_OptionValueEClass->getEStructuralFeatures().push_back(
            m_OptionValue__optionName);
    m_OptionValue__value = new ::ecore::EAttribute();
    m_OptionValue__value->setFeatureID(
            ::UMS_Data::UMS_DataPackage::OPTIONVALUE__VALUE);
    m_OptionValueEClass->getEStructuralFeatures().push_back(
            m_OptionValue__value);

    // ListOptionsValues
    m_ListOptionsValuesEClass = new ::ecore::EClass();
    m_ListOptionsValuesEClass->setClassifierID(LISTOPTIONSVALUES);
    m_ListOptionsValuesEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListOptionsValuesEClass);
    m_ListOptionsValues__optionValues = new ::ecore::EReference();
    m_ListOptionsValues__optionValues->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTOPTIONSVALUES__OPTIONVALUES);
    m_ListOptionsValuesEClass->getEStructuralFeatures().push_back(
            m_ListOptionsValues__optionValues);

    // ListOptOptions
    m_ListOptOptionsEClass = new ::ecore::EClass();
    m_ListOptOptionsEClass->setClassifierID(LISTOPTOPTIONS);
    m_ListOptOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListOptOptionsEClass);
    m_ListOptOptions__listAllDeftValue = new ::ecore::EAttribute();
    m_ListOptOptions__listAllDeftValue->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTOPTOPTIONS__LISTALLDEFTVALUE);
    m_ListOptOptionsEClass->getEStructuralFeatures().push_back(
            m_ListOptOptions__listAllDeftValue);
    m_ListOptOptions__userId = new ::ecore::EAttribute();
    m_ListOptOptions__userId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTOPTOPTIONS__USERID);
    m_ListOptOptionsEClass->getEStructuralFeatures().push_back(
            m_ListOptOptions__userId);
    m_ListOptOptions__optionName = new ::ecore::EAttribute();
    m_ListOptOptions__optionName->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTOPTOPTIONS__OPTIONNAME);
    m_ListOptOptionsEClass->getEStructuralFeatures().push_back(
            m_ListOptOptions__optionName);

    // AuthSystem
    m_AuthSystemEClass = new ::ecore::EClass();
    m_AuthSystemEClass->setClassifierID(AUTHSYSTEM);
    m_AuthSystemEClass->setEPackage(this);
    getEClassifiers().push_back(m_AuthSystemEClass);
    m_AuthSystem__authSystemId = new ::ecore::EAttribute();
    m_AuthSystem__authSystemId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHSYSTEM__AUTHSYSTEMID);
    m_AuthSystemEClass->getEStructuralFeatures().push_back(
            m_AuthSystem__authSystemId);
    m_AuthSystem__name = new ::ecore::EAttribute();
    m_AuthSystem__name->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHSYSTEM__NAME);
    m_AuthSystemEClass->getEStructuralFeatures().push_back(m_AuthSystem__name);
    m_AuthSystem__URI = new ::ecore::EAttribute();
    m_AuthSystem__URI->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHSYSTEM__URI);
    m_AuthSystemEClass->getEStructuralFeatures().push_back(m_AuthSystem__URI);
    m_AuthSystem__authLogin = new ::ecore::EAttribute();
    m_AuthSystem__authLogin->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHSYSTEM__AUTHLOGIN);
    m_AuthSystemEClass->getEStructuralFeatures().push_back(
            m_AuthSystem__authLogin);
    m_AuthSystem__authPassword = new ::ecore::EAttribute();
    m_AuthSystem__authPassword->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHSYSTEM__AUTHPASSWORD);
    m_AuthSystemEClass->getEStructuralFeatures().push_back(
            m_AuthSystem__authPassword);
    m_AuthSystem__userPasswordEncryption = new ::ecore::EAttribute();
    m_AuthSystem__userPasswordEncryption->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHSYSTEM__USERPASSWORDENCRYPTION);
    m_AuthSystemEClass->getEStructuralFeatures().push_back(
            m_AuthSystem__userPasswordEncryption);
    m_AuthSystem__type = new ::ecore::EAttribute();
    m_AuthSystem__type->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHSYSTEM__TYPE);
    m_AuthSystemEClass->getEStructuralFeatures().push_back(m_AuthSystem__type);
    m_AuthSystem__status = new ::ecore::EAttribute();
    m_AuthSystem__status->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHSYSTEM__STATUS);
    m_AuthSystemEClass->getEStructuralFeatures().push_back(m_AuthSystem__status);
    m_AuthSystem__ldapBase = new ::ecore::EAttribute();
    m_AuthSystem__ldapBase->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHSYSTEM__LDAPBASE);
    m_AuthSystemEClass->getEStructuralFeatures().push_back(
            m_AuthSystem__ldapBase);

    // ListAuthSystems
    m_ListAuthSystemsEClass = new ::ecore::EClass();
    m_ListAuthSystemsEClass->setClassifierID(LISTAUTHSYSTEMS);
    m_ListAuthSystemsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListAuthSystemsEClass);
    m_ListAuthSystems__AuthSystems = new ::ecore::EReference();
    m_ListAuthSystems__AuthSystems->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTAUTHSYSTEMS__AUTHSYSTEMS);
    m_ListAuthSystemsEClass->getEStructuralFeatures().push_back(
            m_ListAuthSystems__AuthSystems);

    // ListAuthSysOptions
    m_ListAuthSysOptionsEClass = new ::ecore::EClass();
    m_ListAuthSysOptionsEClass->setClassifierID(LISTAUTHSYSOPTIONS);
    m_ListAuthSysOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListAuthSysOptionsEClass);
    m_ListAuthSysOptions__listAllAuthSystems = new ::ecore::EAttribute();
    m_ListAuthSysOptions__listAllAuthSystems->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTAUTHSYSOPTIONS__LISTALLAUTHSYSTEMS);
    m_ListAuthSysOptionsEClass->getEStructuralFeatures().push_back(
            m_ListAuthSysOptions__listAllAuthSystems);
    m_ListAuthSysOptions__listFullInfo = new ::ecore::EAttribute();
    m_ListAuthSysOptions__listFullInfo->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTAUTHSYSOPTIONS__LISTFULLINFO);
    m_ListAuthSysOptionsEClass->getEStructuralFeatures().push_back(
            m_ListAuthSysOptions__listFullInfo);
    m_ListAuthSysOptions__userId = new ::ecore::EAttribute();
    m_ListAuthSysOptions__userId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTAUTHSYSOPTIONS__USERID);
    m_ListAuthSysOptionsEClass->getEStructuralFeatures().push_back(
            m_ListAuthSysOptions__userId);
    m_ListAuthSysOptions__authSystemId = new ::ecore::EAttribute();
    m_ListAuthSysOptions__authSystemId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTAUTHSYSOPTIONS__AUTHSYSTEMID);
    m_ListAuthSysOptionsEClass->getEStructuralFeatures().push_back(
            m_ListAuthSysOptions__authSystemId);

    // AuthAccount
    m_AuthAccountEClass = new ::ecore::EClass();
    m_AuthAccountEClass->setClassifierID(AUTHACCOUNT);
    m_AuthAccountEClass->setEPackage(this);
    getEClassifiers().push_back(m_AuthAccountEClass);
    m_AuthAccount__authSystemId = new ::ecore::EAttribute();
    m_AuthAccount__authSystemId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHACCOUNT__AUTHSYSTEMID);
    m_AuthAccountEClass->getEStructuralFeatures().push_back(
            m_AuthAccount__authSystemId);
    m_AuthAccount__userId = new ::ecore::EAttribute();
    m_AuthAccount__userId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHACCOUNT__USERID);
    m_AuthAccountEClass->getEStructuralFeatures().push_back(
            m_AuthAccount__userId);
    m_AuthAccount__acLogin = new ::ecore::EAttribute();
    m_AuthAccount__acLogin->setFeatureID(
            ::UMS_Data::UMS_DataPackage::AUTHACCOUNT__ACLOGIN);
    m_AuthAccountEClass->getEStructuralFeatures().push_back(
            m_AuthAccount__acLogin);

    // ListAuthAccounts
    m_ListAuthAccountsEClass = new ::ecore::EClass();
    m_ListAuthAccountsEClass->setClassifierID(LISTAUTHACCOUNTS);
    m_ListAuthAccountsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListAuthAccountsEClass);
    m_ListAuthAccounts__AuthAccounts = new ::ecore::EReference();
    m_ListAuthAccounts__AuthAccounts->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTAUTHACCOUNTS__AUTHACCOUNTS);
    m_ListAuthAccountsEClass->getEStructuralFeatures().push_back(
            m_ListAuthAccounts__AuthAccounts);

    // ListAuthAccOptions
    m_ListAuthAccOptionsEClass = new ::ecore::EClass();
    m_ListAuthAccOptionsEClass->setClassifierID(LISTAUTHACCOPTIONS);
    m_ListAuthAccOptionsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ListAuthAccOptionsEClass);
    m_ListAuthAccOptions__listAll = new ::ecore::EAttribute();
    m_ListAuthAccOptions__listAll->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTAUTHACCOPTIONS__LISTALL);
    m_ListAuthAccOptionsEClass->getEStructuralFeatures().push_back(
            m_ListAuthAccOptions__listAll);
    m_ListAuthAccOptions__userId = new ::ecore::EAttribute();
    m_ListAuthAccOptions__userId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTAUTHACCOPTIONS__USERID);
    m_ListAuthAccOptionsEClass->getEStructuralFeatures().push_back(
            m_ListAuthAccOptions__userId);
    m_ListAuthAccOptions__authSystemId = new ::ecore::EAttribute();
    m_ListAuthAccOptions__authSystemId->setFeatureID(
            ::UMS_Data::UMS_DataPackage::LISTAUTHACCOPTIONS__AUTHSYSTEMID);
    m_ListAuthAccOptionsEClass->getEStructuralFeatures().push_back(
            m_ListAuthAccOptions__authSystemId);

    // Version
    m_VersionEClass = new ::ecore::EClass();
    m_VersionEClass->setClassifierID(VERSION);
    m_VersionEClass->setEPackage(this);
    getEClassifiers().push_back(m_VersionEClass);
    m_Version__major = new ::ecore::EAttribute();
    m_Version__major->setFeatureID(::UMS_Data::UMS_DataPackage::VERSION__MAJOR);
    m_VersionEClass->getEStructuralFeatures().push_back(m_Version__major);
    m_Version__minor = new ::ecore::EAttribute();
    m_Version__minor->setFeatureID(::UMS_Data::UMS_DataPackage::VERSION__MINOR);
    m_VersionEClass->getEStructuralFeatures().push_back(m_Version__minor);
    m_Version__patch = new ::ecore::EAttribute();
    m_Version__patch->setFeatureID(::UMS_Data::UMS_DataPackage::VERSION__PATCH);
    m_VersionEClass->getEStructuralFeatures().push_back(m_Version__patch);
    m_Version__stringformat = new ::ecore::EAttribute();
    m_Version__stringformat->setFeatureID(
            ::UMS_Data::UMS_DataPackage::VERSION__STRINGFORMAT);
    m_VersionEClass->getEStructuralFeatures().push_back(m_Version__stringformat);

    // Create enums

    m_SessionCloseTypeEEnum = new ::ecore::EEnum();
    m_SessionCloseTypeEEnum->setClassifierID(SESSIONCLOSETYPE);
    m_SessionCloseTypeEEnum->setEPackage(this);
    getEClassifiers().push_back(m_SessionCloseTypeEEnum);

    m_PrivilegeTypeEEnum = new ::ecore::EEnum();
    m_PrivilegeTypeEEnum->setClassifierID(PRIVILEGETYPE);
    m_PrivilegeTypeEEnum->setEPackage(this);
    getEClassifiers().push_back(m_PrivilegeTypeEEnum);

    m_StatusTypeEEnum = new ::ecore::EEnum();
    m_StatusTypeEEnum->setClassifierID(STATUSTYPE);
    m_StatusTypeEEnum->setEPackage(this);
    getEClassifiers().push_back(m_StatusTypeEEnum);

    m_CommandStatusTypeEEnum = new ::ecore::EEnum();
    m_CommandStatusTypeEEnum->setClassifierID(COMMANDSTATUSTYPE);
    m_CommandStatusTypeEEnum->setEPackage(this);
    getEClassifiers().push_back(m_CommandStatusTypeEEnum);

    m_AuthTypeEEnum = new ::ecore::EEnum();
    m_AuthTypeEEnum->setClassifierID(AUTHTYPE);
    m_AuthTypeEEnum->setEPackage(this);
    getEClassifiers().push_back(m_AuthTypeEEnum);

    m_EncryptionMethodEEnum = new ::ecore::EEnum();
    m_EncryptionMethodEEnum->setClassifierID(ENCRYPTIONMETHOD);
    m_EncryptionMethodEEnum->setEPackage(this);
    getEClassifiers().push_back(m_EncryptionMethodEEnum);

    // Create data types


    // Initialize package
    setName("UMS_Data");
    setNsPrefix("ums_data");
    setNsURI("http://www.sysfera.com/emf/ums/data");

    // TODO: bounds for type parameters

    // Add supertypes to classes

    // TODO: Initialize classes and features; add operations and parameters
    // TODO: GenericTypes
    // ConnectOptions
    m_ConnectOptionsEClass->setName("ConnectOptions");
    m_ConnectOptionsEClass->setAbstract(false);
    m_ConnectOptionsEClass->setInterface(false);
    m_ConnectOptions__closePolicy->setEType(m_SessionCloseTypeEEnum);
    m_ConnectOptions__closePolicy->setName("closePolicy");
    m_ConnectOptions__closePolicy->setDefaultValueLiteral("0");
    m_ConnectOptions__closePolicy->setLowerBound(0);
    m_ConnectOptions__closePolicy->setUpperBound(1);
    m_ConnectOptions__closePolicy->setTransient(false);
    m_ConnectOptions__closePolicy->setVolatile(false);
    m_ConnectOptions__closePolicy->setChangeable(true);
    m_ConnectOptions__closePolicy->setUnsettable(false);
    m_ConnectOptions__closePolicy->setID(false);
    m_ConnectOptions__closePolicy->setUnique(true);
    m_ConnectOptions__closePolicy->setDerived(false);
    m_ConnectOptions__closePolicy->setOrdered(true);
    m_ConnectOptions__sessionInactivityDelay->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ConnectOptions__sessionInactivityDelay->setName("sessionInactivityDelay");
    m_ConnectOptions__sessionInactivityDelay->setDefaultValueLiteral("0");
    m_ConnectOptions__sessionInactivityDelay->setLowerBound(0);
    m_ConnectOptions__sessionInactivityDelay->setUpperBound(1);
    m_ConnectOptions__sessionInactivityDelay->setTransient(false);
    m_ConnectOptions__sessionInactivityDelay->setVolatile(false);
    m_ConnectOptions__sessionInactivityDelay->setChangeable(true);
    m_ConnectOptions__sessionInactivityDelay->setUnsettable(false);
    m_ConnectOptions__sessionInactivityDelay->setID(false);
    m_ConnectOptions__sessionInactivityDelay->setUnique(true);
    m_ConnectOptions__sessionInactivityDelay->setDerived(false);
    m_ConnectOptions__sessionInactivityDelay->setOrdered(true);
    m_ConnectOptions__substituteUserId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ConnectOptions__substituteUserId->setName("substituteUserId");
    m_ConnectOptions__substituteUserId->setDefaultValueLiteral("");
    m_ConnectOptions__substituteUserId->setLowerBound(0);
    m_ConnectOptions__substituteUserId->setUpperBound(1);
    m_ConnectOptions__substituteUserId->setTransient(false);
    m_ConnectOptions__substituteUserId->setVolatile(false);
    m_ConnectOptions__substituteUserId->setChangeable(true);
    m_ConnectOptions__substituteUserId->setUnsettable(false);
    m_ConnectOptions__substituteUserId->setID(false);
    m_ConnectOptions__substituteUserId->setUnique(true);
    m_ConnectOptions__substituteUserId->setDerived(false);
    m_ConnectOptions__substituteUserId->setOrdered(true);
    // Session
    m_SessionEClass->setName("Session");
    m_SessionEClass->setAbstract(false);
    m_SessionEClass->setInterface(false);
    m_Session__sessionId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Session__sessionId->setName("sessionId");
    m_Session__sessionId->setDefaultValueLiteral("" "");
    m_Session__sessionId->setLowerBound(0);
    m_Session__sessionId->setUpperBound(1);
    m_Session__sessionId->setTransient(false);
    m_Session__sessionId->setVolatile(false);
    m_Session__sessionId->setChangeable(true);
    m_Session__sessionId->setUnsettable(false);
    m_Session__sessionId->setID(false);
    m_Session__sessionId->setUnique(true);
    m_Session__sessionId->setDerived(false);
    m_Session__sessionId->setOrdered(true);
    m_Session__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Session__userId->setName("userId");
    m_Session__userId->setDefaultValueLiteral("" "");
    m_Session__userId->setLowerBound(0);
    m_Session__userId->setUpperBound(1);
    m_Session__userId->setTransient(false);
    m_Session__userId->setVolatile(false);
    m_Session__userId->setChangeable(true);
    m_Session__userId->setUnsettable(false);
    m_Session__userId->setID(false);
    m_Session__userId->setUnique(true);
    m_Session__userId->setDerived(false);
    m_Session__userId->setOrdered(true);
    m_Session__sessionKey->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Session__sessionKey->setName("sessionKey");
    m_Session__sessionKey->setDefaultValueLiteral("" "");
    m_Session__sessionKey->setLowerBound(0);
    m_Session__sessionKey->setUpperBound(1);
    m_Session__sessionKey->setTransient(false);
    m_Session__sessionKey->setVolatile(false);
    m_Session__sessionKey->setChangeable(true);
    m_Session__sessionKey->setUnsettable(false);
    m_Session__sessionKey->setID(false);
    m_Session__sessionKey->setUnique(true);
    m_Session__sessionKey->setDerived(false);
    m_Session__sessionKey->setOrdered(true);
    m_Session__dateLastConnect->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Session__dateLastConnect->setName("dateLastConnect");
    m_Session__dateLastConnect->setDefaultValueLiteral("-1");
    m_Session__dateLastConnect->setLowerBound(0);
    m_Session__dateLastConnect->setUpperBound(1);
    m_Session__dateLastConnect->setTransient(false);
    m_Session__dateLastConnect->setVolatile(false);
    m_Session__dateLastConnect->setChangeable(true);
    m_Session__dateLastConnect->setUnsettable(false);
    m_Session__dateLastConnect->setID(false);
    m_Session__dateLastConnect->setUnique(true);
    m_Session__dateLastConnect->setDerived(false);
    m_Session__dateLastConnect->setOrdered(true);
    m_Session__dateCreation->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Session__dateCreation->setName("dateCreation");
    m_Session__dateCreation->setDefaultValueLiteral("-1");
    m_Session__dateCreation->setLowerBound(0);
    m_Session__dateCreation->setUpperBound(1);
    m_Session__dateCreation->setTransient(false);
    m_Session__dateCreation->setVolatile(false);
    m_Session__dateCreation->setChangeable(true);
    m_Session__dateCreation->setUnsettable(false);
    m_Session__dateCreation->setID(false);
    m_Session__dateCreation->setUnique(true);
    m_Session__dateCreation->setDerived(false);
    m_Session__dateCreation->setOrdered(true);
    m_Session__dateClosure->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Session__dateClosure->setName("dateClosure");
    m_Session__dateClosure->setDefaultValueLiteral("-1");
    m_Session__dateClosure->setLowerBound(0);
    m_Session__dateClosure->setUpperBound(1);
    m_Session__dateClosure->setTransient(false);
    m_Session__dateClosure->setVolatile(false);
    m_Session__dateClosure->setChangeable(true);
    m_Session__dateClosure->setUnsettable(false);
    m_Session__dateClosure->setID(false);
    m_Session__dateClosure->setUnique(true);
    m_Session__dateClosure->setDerived(false);
    m_Session__dateClosure->setOrdered(true);
    m_Session__status->setEType(m_StatusTypeEEnum);
    m_Session__status->setName("status");
    m_Session__status->setDefaultValueLiteral("1");
    m_Session__status->setLowerBound(0);
    m_Session__status->setUpperBound(1);
    m_Session__status->setTransient(false);
    m_Session__status->setVolatile(false);
    m_Session__status->setChangeable(true);
    m_Session__status->setUnsettable(false);
    m_Session__status->setID(false);
    m_Session__status->setUnique(true);
    m_Session__status->setDerived(false);
    m_Session__status->setOrdered(true);
    m_Session__closePolicy->setEType(m_SessionCloseTypeEEnum);
    m_Session__closePolicy->setName("closePolicy");
    m_Session__closePolicy->setDefaultValueLiteral("0");
    m_Session__closePolicy->setLowerBound(0);
    m_Session__closePolicy->setUpperBound(1);
    m_Session__closePolicy->setTransient(false);
    m_Session__closePolicy->setVolatile(false);
    m_Session__closePolicy->setChangeable(true);
    m_Session__closePolicy->setUnsettable(false);
    m_Session__closePolicy->setID(false);
    m_Session__closePolicy->setUnique(true);
    m_Session__closePolicy->setDerived(false);
    m_Session__closePolicy->setOrdered(true);
    m_Session__timeout->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Session__timeout->setName("timeout");
    m_Session__timeout->setDefaultValueLiteral("0");
    m_Session__timeout->setLowerBound(0);
    m_Session__timeout->setUpperBound(1);
    m_Session__timeout->setTransient(false);
    m_Session__timeout->setVolatile(false);
    m_Session__timeout->setChangeable(true);
    m_Session__timeout->setUnsettable(false);
    m_Session__timeout->setID(false);
    m_Session__timeout->setUnique(true);
    m_Session__timeout->setDerived(false);
    m_Session__timeout->setOrdered(true);
    m_Session__authenId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Session__authenId->setName("authenId");
    m_Session__authenId->setDefaultValueLiteral("");
    m_Session__authenId->setLowerBound(0);
    m_Session__authenId->setUpperBound(1);
    m_Session__authenId->setTransient(false);
    m_Session__authenId->setVolatile(false);
    m_Session__authenId->setChangeable(true);
    m_Session__authenId->setUnsettable(false);
    m_Session__authenId->setID(false);
    m_Session__authenId->setUnique(true);
    m_Session__authenId->setDerived(false);
    m_Session__authenId->setOrdered(true);
    // ListSessions
    m_ListSessionsEClass->setName("ListSessions");
    m_ListSessionsEClass->setAbstract(false);
    m_ListSessionsEClass->setInterface(false);
    m_ListSessions__sessions->setEType(m_SessionEClass);
    m_ListSessions__sessions->setName("sessions");
    m_ListSessions__sessions->setDefaultValueLiteral("");
    m_ListSessions__sessions->setLowerBound(0);
    m_ListSessions__sessions->setUpperBound(-1);
    m_ListSessions__sessions->setTransient(false);
    m_ListSessions__sessions->setVolatile(false);
    m_ListSessions__sessions->setChangeable(true);
    m_ListSessions__sessions->setContainment(true);
    m_ListSessions__sessions->setResolveProxies(true);
    m_ListSessions__sessions->setUnique(true);
    m_ListSessions__sessions->setDerived(false);
    m_ListSessions__sessions->setOrdered(true);
    // ListSessionOptions
    m_ListSessionOptionsEClass->setName("ListSessionOptions");
    m_ListSessionOptionsEClass->setAbstract(false);
    m_ListSessionOptionsEClass->setInterface(false);
    m_ListSessionOptions__status->setEType(m_StatusTypeEEnum);
    m_ListSessionOptions__status->setName("status");
    m_ListSessionOptions__status->setDefaultValueLiteral("1");
    m_ListSessionOptions__status->setLowerBound(0);
    m_ListSessionOptions__status->setUpperBound(1);
    m_ListSessionOptions__status->setTransient(false);
    m_ListSessionOptions__status->setVolatile(false);
    m_ListSessionOptions__status->setChangeable(true);
    m_ListSessionOptions__status->setUnsettable(false);
    m_ListSessionOptions__status->setID(false);
    m_ListSessionOptions__status->setUnique(true);
    m_ListSessionOptions__status->setDerived(false);
    m_ListSessionOptions__status->setOrdered(true);
    m_ListSessionOptions__sessionClosePolicy->setEType(m_SessionCloseTypeEEnum);
    m_ListSessionOptions__sessionClosePolicy->setName("sessionClosePolicy");
    m_ListSessionOptions__sessionClosePolicy->setDefaultValueLiteral("0");
    m_ListSessionOptions__sessionClosePolicy->setLowerBound(0);
    m_ListSessionOptions__sessionClosePolicy->setUpperBound(1);
    m_ListSessionOptions__sessionClosePolicy->setTransient(false);
    m_ListSessionOptions__sessionClosePolicy->setVolatile(false);
    m_ListSessionOptions__sessionClosePolicy->setChangeable(true);
    m_ListSessionOptions__sessionClosePolicy->setUnsettable(false);
    m_ListSessionOptions__sessionClosePolicy->setID(false);
    m_ListSessionOptions__sessionClosePolicy->setUnique(true);
    m_ListSessionOptions__sessionClosePolicy->setDerived(false);
    m_ListSessionOptions__sessionClosePolicy->setOrdered(true);
    m_ListSessionOptions__sessionInactivityDelay->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ListSessionOptions__sessionInactivityDelay->setName(
            "sessionInactivityDelay");
    m_ListSessionOptions__sessionInactivityDelay->setDefaultValueLiteral("0");
    m_ListSessionOptions__sessionInactivityDelay->setLowerBound(0);
    m_ListSessionOptions__sessionInactivityDelay->setUpperBound(1);
    m_ListSessionOptions__sessionInactivityDelay->setTransient(false);
    m_ListSessionOptions__sessionInactivityDelay->setVolatile(false);
    m_ListSessionOptions__sessionInactivityDelay->setChangeable(true);
    m_ListSessionOptions__sessionInactivityDelay->setUnsettable(false);
    m_ListSessionOptions__sessionInactivityDelay->setID(false);
    m_ListSessionOptions__sessionInactivityDelay->setUnique(true);
    m_ListSessionOptions__sessionInactivityDelay->setDerived(false);
    m_ListSessionOptions__sessionInactivityDelay->setOrdered(true);
    m_ListSessionOptions__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListSessionOptions__machineId->setName("machineId");
    m_ListSessionOptions__machineId->setDefaultValueLiteral("" "");
    m_ListSessionOptions__machineId->setLowerBound(0);
    m_ListSessionOptions__machineId->setUpperBound(1);
    m_ListSessionOptions__machineId->setTransient(false);
    m_ListSessionOptions__machineId->setVolatile(false);
    m_ListSessionOptions__machineId->setChangeable(true);
    m_ListSessionOptions__machineId->setUnsettable(false);
    m_ListSessionOptions__machineId->setID(false);
    m_ListSessionOptions__machineId->setUnique(true);
    m_ListSessionOptions__machineId->setDerived(false);
    m_ListSessionOptions__machineId->setOrdered(true);
    m_ListSessionOptions__adminListOption->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_ListSessionOptions__adminListOption->setName("adminListOption");
    m_ListSessionOptions__adminListOption->setDefaultValueLiteral("false");
    m_ListSessionOptions__adminListOption->setLowerBound(0);
    m_ListSessionOptions__adminListOption->setUpperBound(1);
    m_ListSessionOptions__adminListOption->setTransient(false);
    m_ListSessionOptions__adminListOption->setVolatile(false);
    m_ListSessionOptions__adminListOption->setChangeable(true);
    m_ListSessionOptions__adminListOption->setUnsettable(false);
    m_ListSessionOptions__adminListOption->setID(false);
    m_ListSessionOptions__adminListOption->setUnique(true);
    m_ListSessionOptions__adminListOption->setDerived(false);
    m_ListSessionOptions__adminListOption->setOrdered(true);
    m_ListSessionOptions__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListSessionOptions__userId->setName("userId");
    m_ListSessionOptions__userId->setDefaultValueLiteral("");
    m_ListSessionOptions__userId->setLowerBound(0);
    m_ListSessionOptions__userId->setUpperBound(1);
    m_ListSessionOptions__userId->setTransient(false);
    m_ListSessionOptions__userId->setVolatile(false);
    m_ListSessionOptions__userId->setChangeable(true);
    m_ListSessionOptions__userId->setUnsettable(false);
    m_ListSessionOptions__userId->setID(false);
    m_ListSessionOptions__userId->setUnique(true);
    m_ListSessionOptions__userId->setDerived(false);
    m_ListSessionOptions__userId->setOrdered(true);
    m_ListSessionOptions__sessionId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListSessionOptions__sessionId->setName("sessionId");
    m_ListSessionOptions__sessionId->setDefaultValueLiteral("" "");
    m_ListSessionOptions__sessionId->setLowerBound(0);
    m_ListSessionOptions__sessionId->setUpperBound(1);
    m_ListSessionOptions__sessionId->setTransient(false);
    m_ListSessionOptions__sessionId->setVolatile(false);
    m_ListSessionOptions__sessionId->setChangeable(true);
    m_ListSessionOptions__sessionId->setUnsettable(false);
    m_ListSessionOptions__sessionId->setID(false);
    m_ListSessionOptions__sessionId->setUnique(true);
    m_ListSessionOptions__sessionId->setDerived(false);
    m_ListSessionOptions__sessionId->setOrdered(true);
    m_ListSessionOptions__startDateOption->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_ListSessionOptions__startDateOption->setName("startDateOption");
    m_ListSessionOptions__startDateOption->setDefaultValueLiteral("-1");
    m_ListSessionOptions__startDateOption->setLowerBound(0);
    m_ListSessionOptions__startDateOption->setUpperBound(1);
    m_ListSessionOptions__startDateOption->setTransient(false);
    m_ListSessionOptions__startDateOption->setVolatile(false);
    m_ListSessionOptions__startDateOption->setChangeable(true);
    m_ListSessionOptions__startDateOption->setUnsettable(false);
    m_ListSessionOptions__startDateOption->setID(false);
    m_ListSessionOptions__startDateOption->setUnique(true);
    m_ListSessionOptions__startDateOption->setDerived(false);
    m_ListSessionOptions__startDateOption->setOrdered(true);
    m_ListSessionOptions__endDateOption->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_ListSessionOptions__endDateOption->setName("endDateOption");
    m_ListSessionOptions__endDateOption->setDefaultValueLiteral("-1");
    m_ListSessionOptions__endDateOption->setLowerBound(0);
    m_ListSessionOptions__endDateOption->setUpperBound(1);
    m_ListSessionOptions__endDateOption->setTransient(false);
    m_ListSessionOptions__endDateOption->setVolatile(false);
    m_ListSessionOptions__endDateOption->setChangeable(true);
    m_ListSessionOptions__endDateOption->setUnsettable(false);
    m_ListSessionOptions__endDateOption->setID(false);
    m_ListSessionOptions__endDateOption->setUnique(true);
    m_ListSessionOptions__endDateOption->setDerived(false);
    m_ListSessionOptions__endDateOption->setOrdered(true);
    // User
    m_UserEClass->setName("User");
    m_UserEClass->setAbstract(false);
    m_UserEClass->setInterface(false);
    m_User__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_User__userId->setName("userId");
    m_User__userId->setDefaultValueLiteral("" "");
    m_User__userId->setLowerBound(1);
    m_User__userId->setUpperBound(1);
    m_User__userId->setTransient(false);
    m_User__userId->setVolatile(false);
    m_User__userId->setChangeable(true);
    m_User__userId->setUnsettable(false);
    m_User__userId->setID(false);
    m_User__userId->setUnique(true);
    m_User__userId->setDerived(false);
    m_User__userId->setOrdered(true);
    m_User__password->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_User__password->setName("password");
    m_User__password->setDefaultValueLiteral("");
    m_User__password->setLowerBound(0);
    m_User__password->setUpperBound(1);
    m_User__password->setTransient(false);
    m_User__password->setVolatile(false);
    m_User__password->setChangeable(true);
    m_User__password->setUnsettable(false);
    m_User__password->setID(false);
    m_User__password->setUnique(true);
    m_User__password->setDerived(false);
    m_User__password->setOrdered(true);
    m_User__firstname->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_User__firstname->setName("firstname");
    m_User__firstname->setDefaultValueLiteral("");
    m_User__firstname->setLowerBound(0);
    m_User__firstname->setUpperBound(1);
    m_User__firstname->setTransient(false);
    m_User__firstname->setVolatile(false);
    m_User__firstname->setChangeable(true);
    m_User__firstname->setUnsettable(false);
    m_User__firstname->setID(false);
    m_User__firstname->setUnique(true);
    m_User__firstname->setDerived(false);
    m_User__firstname->setOrdered(true);
    m_User__lastname->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_User__lastname->setName("lastname");
    m_User__lastname->setDefaultValueLiteral("");
    m_User__lastname->setLowerBound(0);
    m_User__lastname->setUpperBound(1);
    m_User__lastname->setTransient(false);
    m_User__lastname->setVolatile(false);
    m_User__lastname->setChangeable(true);
    m_User__lastname->setUnsettable(false);
    m_User__lastname->setID(false);
    m_User__lastname->setUnique(true);
    m_User__lastname->setDerived(false);
    m_User__lastname->setOrdered(true);
    m_User__privilege->setEType(m_PrivilegeTypeEEnum);
    m_User__privilege->setName("privilege");
    m_User__privilege->setDefaultValueLiteral("0");
    m_User__privilege->setLowerBound(0);
    m_User__privilege->setUpperBound(1);
    m_User__privilege->setTransient(false);
    m_User__privilege->setVolatile(false);
    m_User__privilege->setChangeable(true);
    m_User__privilege->setUnsettable(false);
    m_User__privilege->setID(false);
    m_User__privilege->setUnique(true);
    m_User__privilege->setDerived(false);
    m_User__privilege->setOrdered(true);
    m_User__email->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_User__email->setName("email");
    m_User__email->setDefaultValueLiteral("");
    m_User__email->setLowerBound(0);
    m_User__email->setUpperBound(1);
    m_User__email->setTransient(false);
    m_User__email->setVolatile(false);
    m_User__email->setChangeable(true);
    m_User__email->setUnsettable(false);
    m_User__email->setID(false);
    m_User__email->setUnique(true);
    m_User__email->setDerived(false);
    m_User__email->setOrdered(true);
    m_User__status->setEType(m_StatusTypeEEnum);
    m_User__status->setName("status");
    m_User__status->setDefaultValueLiteral("-1");
    m_User__status->setLowerBound(0);
    m_User__status->setUpperBound(1);
    m_User__status->setTransient(false);
    m_User__status->setVolatile(false);
    m_User__status->setChangeable(true);
    m_User__status->setUnsettable(false);
    m_User__status->setID(false);
    m_User__status->setUnique(true);
    m_User__status->setDerived(false);
    m_User__status->setOrdered(true);
    // ListUsers
    m_ListUsersEClass->setName("ListUsers");
    m_ListUsersEClass->setAbstract(false);
    m_ListUsersEClass->setInterface(false);
    m_ListUsers__users->setEType(m_UserEClass);
    m_ListUsers__users->setName("users");
    m_ListUsers__users->setDefaultValueLiteral("");
    m_ListUsers__users->setLowerBound(0);
    m_ListUsers__users->setUpperBound(-1);
    m_ListUsers__users->setTransient(false);
    m_ListUsers__users->setVolatile(false);
    m_ListUsers__users->setChangeable(true);
    m_ListUsers__users->setContainment(true);
    m_ListUsers__users->setResolveProxies(true);
    m_ListUsers__users->setUnique(true);
    m_ListUsers__users->setDerived(false);
    m_ListUsers__users->setOrdered(true);
    // ListUsersOptions
    m_ListUsersOptionsEClass->setName("ListUsersOptions");
    m_ListUsersOptionsEClass->setAbstract(false);
    m_ListUsersOptionsEClass->setInterface(false);
    m_ListUsersOptions__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListUsersOptions__userId->setName("userId");
    m_ListUsersOptions__userId->setDefaultValueLiteral("");
    m_ListUsersOptions__userId->setLowerBound(0);
    m_ListUsersOptions__userId->setUpperBound(1);
    m_ListUsersOptions__userId->setTransient(false);
    m_ListUsersOptions__userId->setVolatile(false);
    m_ListUsersOptions__userId->setChangeable(true);
    m_ListUsersOptions__userId->setUnsettable(false);
    m_ListUsersOptions__userId->setID(false);
    m_ListUsersOptions__userId->setUnique(true);
    m_ListUsersOptions__userId->setDerived(false);
    m_ListUsersOptions__userId->setOrdered(true);
    m_ListUsersOptions__authSystemId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListUsersOptions__authSystemId->setName("authSystemId");
    m_ListUsersOptions__authSystemId->setDefaultValueLiteral("" "");
    m_ListUsersOptions__authSystemId->setLowerBound(0);
    m_ListUsersOptions__authSystemId->setUpperBound(1);
    m_ListUsersOptions__authSystemId->setTransient(false);
    m_ListUsersOptions__authSystemId->setVolatile(false);
    m_ListUsersOptions__authSystemId->setChangeable(true);
    m_ListUsersOptions__authSystemId->setUnsettable(false);
    m_ListUsersOptions__authSystemId->setID(false);
    m_ListUsersOptions__authSystemId->setUnique(true);
    m_ListUsersOptions__authSystemId->setDerived(false);
    m_ListUsersOptions__authSystemId->setOrdered(true);
    // Command
    m_CommandEClass->setName("Command");
    m_CommandEClass->setAbstract(false);
    m_CommandEClass->setInterface(false);
    m_Command__commandId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Command__commandId->setName("commandId");
    m_Command__commandId->setDefaultValueLiteral("" "");
    m_Command__commandId->setLowerBound(0);
    m_Command__commandId->setUpperBound(1);
    m_Command__commandId->setTransient(false);
    m_Command__commandId->setVolatile(false);
    m_Command__commandId->setChangeable(true);
    m_Command__commandId->setUnsettable(false);
    m_Command__commandId->setID(false);
    m_Command__commandId->setUnique(true);
    m_Command__commandId->setDerived(false);
    m_Command__commandId->setOrdered(true);
    m_Command__sessionId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Command__sessionId->setName("sessionId");
    m_Command__sessionId->setDefaultValueLiteral("" "");
    m_Command__sessionId->setLowerBound(0);
    m_Command__sessionId->setUpperBound(1);
    m_Command__sessionId->setTransient(false);
    m_Command__sessionId->setVolatile(false);
    m_Command__sessionId->setChangeable(true);
    m_Command__sessionId->setUnsettable(false);
    m_Command__sessionId->setID(false);
    m_Command__sessionId->setUnique(true);
    m_Command__sessionId->setDerived(false);
    m_Command__sessionId->setOrdered(true);
    m_Command__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Command__machineId->setName("machineId");
    m_Command__machineId->setDefaultValueLiteral("" "");
    m_Command__machineId->setLowerBound(0);
    m_Command__machineId->setUpperBound(1);
    m_Command__machineId->setTransient(false);
    m_Command__machineId->setVolatile(false);
    m_Command__machineId->setChangeable(true);
    m_Command__machineId->setUnsettable(false);
    m_Command__machineId->setID(false);
    m_Command__machineId->setUnique(true);
    m_Command__machineId->setDerived(false);
    m_Command__machineId->setOrdered(true);
    m_Command__cmdDescription->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Command__cmdDescription->setName("cmdDescription");
    m_Command__cmdDescription->setDefaultValueLiteral("");
    m_Command__cmdDescription->setLowerBound(0);
    m_Command__cmdDescription->setUpperBound(1);
    m_Command__cmdDescription->setTransient(false);
    m_Command__cmdDescription->setVolatile(false);
    m_Command__cmdDescription->setChangeable(true);
    m_Command__cmdDescription->setUnsettable(false);
    m_Command__cmdDescription->setID(false);
    m_Command__cmdDescription->setUnique(true);
    m_Command__cmdDescription->setDerived(false);
    m_Command__cmdDescription->setOrdered(true);
    m_Command__cmdStartTime->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Command__cmdStartTime->setName("cmdStartTime");
    m_Command__cmdStartTime->setDefaultValueLiteral("-1");
    m_Command__cmdStartTime->setLowerBound(0);
    m_Command__cmdStartTime->setUpperBound(1);
    m_Command__cmdStartTime->setTransient(false);
    m_Command__cmdStartTime->setVolatile(false);
    m_Command__cmdStartTime->setChangeable(true);
    m_Command__cmdStartTime->setUnsettable(false);
    m_Command__cmdStartTime->setID(false);
    m_Command__cmdStartTime->setUnique(true);
    m_Command__cmdStartTime->setDerived(false);
    m_Command__cmdStartTime->setOrdered(true);
    m_Command__cmdEndTime->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_Command__cmdEndTime->setName("cmdEndTime");
    m_Command__cmdEndTime->setDefaultValueLiteral("-1");
    m_Command__cmdEndTime->setLowerBound(0);
    m_Command__cmdEndTime->setUpperBound(1);
    m_Command__cmdEndTime->setTransient(false);
    m_Command__cmdEndTime->setVolatile(false);
    m_Command__cmdEndTime->setChangeable(true);
    m_Command__cmdEndTime->setUnsettable(false);
    m_Command__cmdEndTime->setID(false);
    m_Command__cmdEndTime->setUnique(true);
    m_Command__cmdEndTime->setDerived(false);
    m_Command__cmdEndTime->setOrdered(true);
    m_Command__status->setEType(m_CommandStatusTypeEEnum);
    m_Command__status->setName("status");
    m_Command__status->setDefaultValueLiteral("0");
    m_Command__status->setLowerBound(0);
    m_Command__status->setUpperBound(1);
    m_Command__status->setTransient(false);
    m_Command__status->setVolatile(false);
    m_Command__status->setChangeable(true);
    m_Command__status->setUnsettable(false);
    m_Command__status->setID(false);
    m_Command__status->setUnique(true);
    m_Command__status->setDerived(false);
    m_Command__status->setOrdered(true);
    // ListCommands
    m_ListCommandsEClass->setName("ListCommands");
    m_ListCommandsEClass->setAbstract(false);
    m_ListCommandsEClass->setInterface(false);
    m_ListCommands__Commands->setEType(m_CommandEClass);
    m_ListCommands__Commands->setName("Commands");
    m_ListCommands__Commands->setDefaultValueLiteral("");
    m_ListCommands__Commands->setLowerBound(0);
    m_ListCommands__Commands->setUpperBound(-1);
    m_ListCommands__Commands->setTransient(false);
    m_ListCommands__Commands->setVolatile(false);
    m_ListCommands__Commands->setChangeable(true);
    m_ListCommands__Commands->setContainment(true);
    m_ListCommands__Commands->setResolveProxies(true);
    m_ListCommands__Commands->setUnique(true);
    m_ListCommands__Commands->setDerived(false);
    m_ListCommands__Commands->setOrdered(true);
    // ListCmdOptions
    m_ListCmdOptionsEClass->setName("ListCmdOptions");
    m_ListCmdOptionsEClass->setAbstract(false);
    m_ListCmdOptionsEClass->setInterface(false);
    m_ListCmdOptions__adminListOption->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_ListCmdOptions__adminListOption->setName("adminListOption");
    m_ListCmdOptions__adminListOption->setDefaultValueLiteral("false");
    m_ListCmdOptions__adminListOption->setLowerBound(0);
    m_ListCmdOptions__adminListOption->setUpperBound(1);
    m_ListCmdOptions__adminListOption->setTransient(false);
    m_ListCmdOptions__adminListOption->setVolatile(false);
    m_ListCmdOptions__adminListOption->setChangeable(true);
    m_ListCmdOptions__adminListOption->setUnsettable(false);
    m_ListCmdOptions__adminListOption->setID(false);
    m_ListCmdOptions__adminListOption->setUnique(true);
    m_ListCmdOptions__adminListOption->setDerived(false);
    m_ListCmdOptions__adminListOption->setOrdered(true);
    m_ListCmdOptions__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListCmdOptions__userId->setName("userId");
    m_ListCmdOptions__userId->setDefaultValueLiteral("");
    m_ListCmdOptions__userId->setLowerBound(0);
    m_ListCmdOptions__userId->setUpperBound(1);
    m_ListCmdOptions__userId->setTransient(false);
    m_ListCmdOptions__userId->setVolatile(false);
    m_ListCmdOptions__userId->setChangeable(true);
    m_ListCmdOptions__userId->setUnsettable(false);
    m_ListCmdOptions__userId->setID(false);
    m_ListCmdOptions__userId->setUnique(true);
    m_ListCmdOptions__userId->setDerived(false);
    m_ListCmdOptions__userId->setOrdered(true);
    m_ListCmdOptions__sessionId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListCmdOptions__sessionId->setName("sessionId");
    m_ListCmdOptions__sessionId->setDefaultValueLiteral("" "");
    m_ListCmdOptions__sessionId->setLowerBound(0);
    m_ListCmdOptions__sessionId->setUpperBound(1);
    m_ListCmdOptions__sessionId->setTransient(false);
    m_ListCmdOptions__sessionId->setVolatile(false);
    m_ListCmdOptions__sessionId->setChangeable(true);
    m_ListCmdOptions__sessionId->setUnsettable(false);
    m_ListCmdOptions__sessionId->setID(false);
    m_ListCmdOptions__sessionId->setUnique(true);
    m_ListCmdOptions__sessionId->setDerived(false);
    m_ListCmdOptions__sessionId->setOrdered(true);
    m_ListCmdOptions__startDateOption->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_ListCmdOptions__startDateOption->setName("startDateOption");
    m_ListCmdOptions__startDateOption->setDefaultValueLiteral("-1");
    m_ListCmdOptions__startDateOption->setLowerBound(0);
    m_ListCmdOptions__startDateOption->setUpperBound(1);
    m_ListCmdOptions__startDateOption->setTransient(false);
    m_ListCmdOptions__startDateOption->setVolatile(false);
    m_ListCmdOptions__startDateOption->setChangeable(true);
    m_ListCmdOptions__startDateOption->setUnsettable(false);
    m_ListCmdOptions__startDateOption->setID(false);
    m_ListCmdOptions__startDateOption->setUnique(true);
    m_ListCmdOptions__startDateOption->setDerived(false);
    m_ListCmdOptions__startDateOption->setOrdered(true);
    m_ListCmdOptions__endDateOption->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getELong());
    m_ListCmdOptions__endDateOption->setName("endDateOption");
    m_ListCmdOptions__endDateOption->setDefaultValueLiteral("-1");
    m_ListCmdOptions__endDateOption->setLowerBound(0);
    m_ListCmdOptions__endDateOption->setUpperBound(1);
    m_ListCmdOptions__endDateOption->setTransient(false);
    m_ListCmdOptions__endDateOption->setVolatile(false);
    m_ListCmdOptions__endDateOption->setChangeable(true);
    m_ListCmdOptions__endDateOption->setUnsettable(false);
    m_ListCmdOptions__endDateOption->setID(false);
    m_ListCmdOptions__endDateOption->setUnique(true);
    m_ListCmdOptions__endDateOption->setDerived(false);
    m_ListCmdOptions__endDateOption->setOrdered(true);
    // LocalAccount
    m_LocalAccountEClass->setName("LocalAccount");
    m_LocalAccountEClass->setAbstract(false);
    m_LocalAccountEClass->setInterface(false);
    m_LocalAccount__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_LocalAccount__userId->setName("userId");
    m_LocalAccount__userId->setDefaultValueLiteral("" "");
    m_LocalAccount__userId->setLowerBound(1);
    m_LocalAccount__userId->setUpperBound(1);
    m_LocalAccount__userId->setTransient(false);
    m_LocalAccount__userId->setVolatile(false);
    m_LocalAccount__userId->setChangeable(true);
    m_LocalAccount__userId->setUnsettable(false);
    m_LocalAccount__userId->setID(false);
    m_LocalAccount__userId->setUnique(true);
    m_LocalAccount__userId->setDerived(false);
    m_LocalAccount__userId->setOrdered(true);
    m_LocalAccount__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_LocalAccount__machineId->setName("machineId");
    m_LocalAccount__machineId->setDefaultValueLiteral("");
    m_LocalAccount__machineId->setLowerBound(1);
    m_LocalAccount__machineId->setUpperBound(1);
    m_LocalAccount__machineId->setTransient(false);
    m_LocalAccount__machineId->setVolatile(false);
    m_LocalAccount__machineId->setChangeable(true);
    m_LocalAccount__machineId->setUnsettable(false);
    m_LocalAccount__machineId->setID(false);
    m_LocalAccount__machineId->setUnique(true);
    m_LocalAccount__machineId->setDerived(false);
    m_LocalAccount__machineId->setOrdered(true);
    m_LocalAccount__acLogin->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_LocalAccount__acLogin->setName("acLogin");
    m_LocalAccount__acLogin->setDefaultValueLiteral("" "");
    m_LocalAccount__acLogin->setLowerBound(0);
    m_LocalAccount__acLogin->setUpperBound(1);
    m_LocalAccount__acLogin->setTransient(false);
    m_LocalAccount__acLogin->setVolatile(false);
    m_LocalAccount__acLogin->setChangeable(true);
    m_LocalAccount__acLogin->setUnsettable(false);
    m_LocalAccount__acLogin->setID(false);
    m_LocalAccount__acLogin->setUnique(true);
    m_LocalAccount__acLogin->setDerived(false);
    m_LocalAccount__acLogin->setOrdered(true);
    m_LocalAccount__sshKeyPath->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_LocalAccount__sshKeyPath->setName("sshKeyPath");
    m_LocalAccount__sshKeyPath->setDefaultValueLiteral("");
    m_LocalAccount__sshKeyPath->setLowerBound(0);
    m_LocalAccount__sshKeyPath->setUpperBound(1);
    m_LocalAccount__sshKeyPath->setTransient(false);
    m_LocalAccount__sshKeyPath->setVolatile(false);
    m_LocalAccount__sshKeyPath->setChangeable(true);
    m_LocalAccount__sshKeyPath->setUnsettable(false);
    m_LocalAccount__sshKeyPath->setID(false);
    m_LocalAccount__sshKeyPath->setUnique(true);
    m_LocalAccount__sshKeyPath->setDerived(false);
    m_LocalAccount__sshKeyPath->setOrdered(true);
    m_LocalAccount__homeDirectory->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_LocalAccount__homeDirectory->setName("homeDirectory");
    m_LocalAccount__homeDirectory->setDefaultValueLiteral("" "");
    m_LocalAccount__homeDirectory->setLowerBound(0);
    m_LocalAccount__homeDirectory->setUpperBound(1);
    m_LocalAccount__homeDirectory->setTransient(false);
    m_LocalAccount__homeDirectory->setVolatile(false);
    m_LocalAccount__homeDirectory->setChangeable(true);
    m_LocalAccount__homeDirectory->setUnsettable(false);
    m_LocalAccount__homeDirectory->setID(false);
    m_LocalAccount__homeDirectory->setUnique(true);
    m_LocalAccount__homeDirectory->setDerived(false);
    m_LocalAccount__homeDirectory->setOrdered(true);
    // ListLocalAccounts
    m_ListLocalAccountsEClass->setName("ListLocalAccounts");
    m_ListLocalAccountsEClass->setAbstract(false);
    m_ListLocalAccountsEClass->setInterface(false);
    m_ListLocalAccounts__accounts->setEType(m_LocalAccountEClass);
    m_ListLocalAccounts__accounts->setName("accounts");
    m_ListLocalAccounts__accounts->setDefaultValueLiteral("");
    m_ListLocalAccounts__accounts->setLowerBound(0);
    m_ListLocalAccounts__accounts->setUpperBound(-1);
    m_ListLocalAccounts__accounts->setTransient(false);
    m_ListLocalAccounts__accounts->setVolatile(false);
    m_ListLocalAccounts__accounts->setChangeable(true);
    m_ListLocalAccounts__accounts->setContainment(true);
    m_ListLocalAccounts__accounts->setResolveProxies(true);
    m_ListLocalAccounts__accounts->setUnique(true);
    m_ListLocalAccounts__accounts->setDerived(false);
    m_ListLocalAccounts__accounts->setOrdered(true);
    // ListLocalAccOptions
    m_ListLocalAccOptionsEClass->setName("ListLocalAccOptions");
    m_ListLocalAccOptionsEClass->setAbstract(false);
    m_ListLocalAccOptionsEClass->setInterface(false);
    m_ListLocalAccOptions__adminListOption->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_ListLocalAccOptions__adminListOption->setName("adminListOption");
    m_ListLocalAccOptions__adminListOption->setDefaultValueLiteral("false");
    m_ListLocalAccOptions__adminListOption->setLowerBound(0);
    m_ListLocalAccOptions__adminListOption->setUpperBound(1);
    m_ListLocalAccOptions__adminListOption->setTransient(false);
    m_ListLocalAccOptions__adminListOption->setVolatile(false);
    m_ListLocalAccOptions__adminListOption->setChangeable(true);
    m_ListLocalAccOptions__adminListOption->setUnsettable(false);
    m_ListLocalAccOptions__adminListOption->setID(false);
    m_ListLocalAccOptions__adminListOption->setUnique(true);
    m_ListLocalAccOptions__adminListOption->setDerived(false);
    m_ListLocalAccOptions__adminListOption->setOrdered(true);
    m_ListLocalAccOptions__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListLocalAccOptions__userId->setName("userId");
    m_ListLocalAccOptions__userId->setDefaultValueLiteral("");
    m_ListLocalAccOptions__userId->setLowerBound(0);
    m_ListLocalAccOptions__userId->setUpperBound(1);
    m_ListLocalAccOptions__userId->setTransient(false);
    m_ListLocalAccOptions__userId->setVolatile(false);
    m_ListLocalAccOptions__userId->setChangeable(true);
    m_ListLocalAccOptions__userId->setUnsettable(false);
    m_ListLocalAccOptions__userId->setID(false);
    m_ListLocalAccOptions__userId->setUnique(true);
    m_ListLocalAccOptions__userId->setDerived(false);
    m_ListLocalAccOptions__userId->setOrdered(true);
    m_ListLocalAccOptions__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListLocalAccOptions__machineId->setName("machineId");
    m_ListLocalAccOptions__machineId->setDefaultValueLiteral("" "");
    m_ListLocalAccOptions__machineId->setLowerBound(0);
    m_ListLocalAccOptions__machineId->setUpperBound(1);
    m_ListLocalAccOptions__machineId->setTransient(false);
    m_ListLocalAccOptions__machineId->setVolatile(false);
    m_ListLocalAccOptions__machineId->setChangeable(true);
    m_ListLocalAccOptions__machineId->setUnsettable(false);
    m_ListLocalAccOptions__machineId->setID(false);
    m_ListLocalAccOptions__machineId->setUnique(true);
    m_ListLocalAccOptions__machineId->setDerived(false);
    m_ListLocalAccOptions__machineId->setOrdered(true);
    // Machine
    m_MachineEClass->setName("Machine");
    m_MachineEClass->setAbstract(false);
    m_MachineEClass->setInterface(false);
    m_Machine__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Machine__machineId->setName("machineId");
    m_Machine__machineId->setDefaultValueLiteral("" "");
    m_Machine__machineId->setLowerBound(1);
    m_Machine__machineId->setUpperBound(1);
    m_Machine__machineId->setTransient(false);
    m_Machine__machineId->setVolatile(false);
    m_Machine__machineId->setChangeable(true);
    m_Machine__machineId->setUnsettable(false);
    m_Machine__machineId->setID(false);
    m_Machine__machineId->setUnique(true);
    m_Machine__machineId->setDerived(false);
    m_Machine__machineId->setOrdered(true);
    m_Machine__name->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Machine__name->setName("name");
    m_Machine__name->setDefaultValueLiteral("");
    m_Machine__name->setLowerBound(0);
    m_Machine__name->setUpperBound(1);
    m_Machine__name->setTransient(false);
    m_Machine__name->setVolatile(false);
    m_Machine__name->setChangeable(true);
    m_Machine__name->setUnsettable(false);
    m_Machine__name->setID(false);
    m_Machine__name->setUnique(true);
    m_Machine__name->setDerived(false);
    m_Machine__name->setOrdered(true);
    m_Machine__site->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Machine__site->setName("site");
    m_Machine__site->setDefaultValueLiteral("");
    m_Machine__site->setLowerBound(0);
    m_Machine__site->setUpperBound(1);
    m_Machine__site->setTransient(false);
    m_Machine__site->setVolatile(false);
    m_Machine__site->setChangeable(true);
    m_Machine__site->setUnsettable(false);
    m_Machine__site->setID(false);
    m_Machine__site->setUnique(true);
    m_Machine__site->setDerived(false);
    m_Machine__site->setOrdered(true);
    m_Machine__machineDescription->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Machine__machineDescription->setName("machineDescription");
    m_Machine__machineDescription->setDefaultValueLiteral("" "");
    m_Machine__machineDescription->setLowerBound(0);
    m_Machine__machineDescription->setUpperBound(1);
    m_Machine__machineDescription->setTransient(false);
    m_Machine__machineDescription->setVolatile(false);
    m_Machine__machineDescription->setChangeable(true);
    m_Machine__machineDescription->setUnsettable(false);
    m_Machine__machineDescription->setID(false);
    m_Machine__machineDescription->setUnique(true);
    m_Machine__machineDescription->setDerived(false);
    m_Machine__machineDescription->setOrdered(true);
    m_Machine__language->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Machine__language->setName("language");
    m_Machine__language->setDefaultValueLiteral("");
    m_Machine__language->setLowerBound(0);
    m_Machine__language->setUpperBound(1);
    m_Machine__language->setTransient(false);
    m_Machine__language->setVolatile(false);
    m_Machine__language->setChangeable(true);
    m_Machine__language->setUnsettable(false);
    m_Machine__language->setID(false);
    m_Machine__language->setUnique(true);
    m_Machine__language->setDerived(false);
    m_Machine__language->setOrdered(true);
    m_Machine__status->setEType(m_StatusTypeEEnum);
    m_Machine__status->setName("status");
    m_Machine__status->setDefaultValueLiteral("-1");
    m_Machine__status->setLowerBound(0);
    m_Machine__status->setUpperBound(1);
    m_Machine__status->setTransient(false);
    m_Machine__status->setVolatile(false);
    m_Machine__status->setChangeable(true);
    m_Machine__status->setUnsettable(false);
    m_Machine__status->setID(false);
    m_Machine__status->setUnique(true);
    m_Machine__status->setDerived(false);
    m_Machine__status->setOrdered(true);
    m_Machine__sshPublicKey->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Machine__sshPublicKey->setName("sshPublicKey");
    m_Machine__sshPublicKey->setDefaultValueLiteral("");
    m_Machine__sshPublicKey->setLowerBound(0);
    m_Machine__sshPublicKey->setUpperBound(1);
    m_Machine__sshPublicKey->setTransient(false);
    m_Machine__sshPublicKey->setVolatile(false);
    m_Machine__sshPublicKey->setChangeable(true);
    m_Machine__sshPublicKey->setUnsettable(false);
    m_Machine__sshPublicKey->setID(false);
    m_Machine__sshPublicKey->setUnique(true);
    m_Machine__sshPublicKey->setDerived(false);
    m_Machine__sshPublicKey->setOrdered(true);
    // ListMachines
    m_ListMachinesEClass->setName("ListMachines");
    m_ListMachinesEClass->setAbstract(false);
    m_ListMachinesEClass->setInterface(false);
    m_ListMachines__machines->setEType(m_MachineEClass);
    m_ListMachines__machines->setName("machines");
    m_ListMachines__machines->setDefaultValueLiteral("");
    m_ListMachines__machines->setLowerBound(0);
    m_ListMachines__machines->setUpperBound(-1);
    m_ListMachines__machines->setTransient(false);
    m_ListMachines__machines->setVolatile(false);
    m_ListMachines__machines->setChangeable(true);
    m_ListMachines__machines->setContainment(true);
    m_ListMachines__machines->setResolveProxies(true);
    m_ListMachines__machines->setUnique(true);
    m_ListMachines__machines->setDerived(false);
    m_ListMachines__machines->setOrdered(true);
    // ListMachineOptions
    m_ListMachineOptionsEClass->setName("ListMachineOptions");
    m_ListMachineOptionsEClass->setAbstract(false);
    m_ListMachineOptionsEClass->setInterface(false);
    m_ListMachineOptions__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListMachineOptions__userId->setName("userId");
    m_ListMachineOptions__userId->setDefaultValueLiteral("");
    m_ListMachineOptions__userId->setLowerBound(0);
    m_ListMachineOptions__userId->setUpperBound(1);
    m_ListMachineOptions__userId->setTransient(false);
    m_ListMachineOptions__userId->setVolatile(false);
    m_ListMachineOptions__userId->setChangeable(true);
    m_ListMachineOptions__userId->setUnsettable(false);
    m_ListMachineOptions__userId->setID(false);
    m_ListMachineOptions__userId->setUnique(true);
    m_ListMachineOptions__userId->setDerived(false);
    m_ListMachineOptions__userId->setOrdered(true);
    m_ListMachineOptions__listAllMachine->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_ListMachineOptions__listAllMachine->setName("listAllMachine");
    m_ListMachineOptions__listAllMachine->setDefaultValueLiteral("false");
    m_ListMachineOptions__listAllMachine->setLowerBound(0);
    m_ListMachineOptions__listAllMachine->setUpperBound(1);
    m_ListMachineOptions__listAllMachine->setTransient(false);
    m_ListMachineOptions__listAllMachine->setVolatile(false);
    m_ListMachineOptions__listAllMachine->setChangeable(true);
    m_ListMachineOptions__listAllMachine->setUnsettable(false);
    m_ListMachineOptions__listAllMachine->setID(false);
    m_ListMachineOptions__listAllMachine->setUnique(true);
    m_ListMachineOptions__listAllMachine->setDerived(false);
    m_ListMachineOptions__listAllMachine->setOrdered(true);
    m_ListMachineOptions__machineId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListMachineOptions__machineId->setName("machineId");
    m_ListMachineOptions__machineId->setDefaultValueLiteral("" "");
    m_ListMachineOptions__machineId->setLowerBound(0);
    m_ListMachineOptions__machineId->setUpperBound(1);
    m_ListMachineOptions__machineId->setTransient(false);
    m_ListMachineOptions__machineId->setVolatile(false);
    m_ListMachineOptions__machineId->setChangeable(true);
    m_ListMachineOptions__machineId->setUnsettable(false);
    m_ListMachineOptions__machineId->setID(false);
    m_ListMachineOptions__machineId->setUnique(true);
    m_ListMachineOptions__machineId->setDerived(false);
    m_ListMachineOptions__machineId->setOrdered(true);
    // Configuration
    m_ConfigurationEClass->setName("Configuration");
    m_ConfigurationEClass->setAbstract(false);
    m_ConfigurationEClass->setInterface(false);
    m_Configuration__filePath->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Configuration__filePath->setName("filePath");
    m_Configuration__filePath->setDefaultValueLiteral("");
    m_Configuration__filePath->setLowerBound(0);
    m_Configuration__filePath->setUpperBound(1);
    m_Configuration__filePath->setTransient(false);
    m_Configuration__filePath->setVolatile(false);
    m_Configuration__filePath->setChangeable(true);
    m_Configuration__filePath->setUnsettable(false);
    m_Configuration__filePath->setID(false);
    m_Configuration__filePath->setUnique(true);
    m_Configuration__filePath->setDerived(false);
    m_Configuration__filePath->setOrdered(true);
    m_Configuration__listConfUsers->setEType(m_UserEClass);
    m_Configuration__listConfUsers->setName("listConfUsers");
    m_Configuration__listConfUsers->setDefaultValueLiteral("");
    m_Configuration__listConfUsers->setLowerBound(0);
    m_Configuration__listConfUsers->setUpperBound(-1);
    m_Configuration__listConfUsers->setTransient(false);
    m_Configuration__listConfUsers->setVolatile(false);
    m_Configuration__listConfUsers->setChangeable(true);
    m_Configuration__listConfUsers->setContainment(true);
    m_Configuration__listConfUsers->setResolveProxies(true);
    m_Configuration__listConfUsers->setUnique(true);
    m_Configuration__listConfUsers->setDerived(false);
    m_Configuration__listConfUsers->setOrdered(true);
    m_Configuration__listConfMachines->setEType(m_MachineEClass);
    m_Configuration__listConfMachines->setName("listConfMachines");
    m_Configuration__listConfMachines->setDefaultValueLiteral("");
    m_Configuration__listConfMachines->setLowerBound(0);
    m_Configuration__listConfMachines->setUpperBound(-1);
    m_Configuration__listConfMachines->setTransient(false);
    m_Configuration__listConfMachines->setVolatile(false);
    m_Configuration__listConfMachines->setChangeable(true);
    m_Configuration__listConfMachines->setContainment(true);
    m_Configuration__listConfMachines->setResolveProxies(true);
    m_Configuration__listConfMachines->setUnique(true);
    m_Configuration__listConfMachines->setDerived(false);
    m_Configuration__listConfMachines->setOrdered(true);
    m_Configuration__listConfLocalAccounts->setEType(m_LocalAccountEClass);
    m_Configuration__listConfLocalAccounts->setName("listConfLocalAccounts");
    m_Configuration__listConfLocalAccounts->setDefaultValueLiteral("");
    m_Configuration__listConfLocalAccounts->setLowerBound(0);
    m_Configuration__listConfLocalAccounts->setUpperBound(-1);
    m_Configuration__listConfLocalAccounts->setTransient(false);
    m_Configuration__listConfLocalAccounts->setVolatile(false);
    m_Configuration__listConfLocalAccounts->setChangeable(true);
    m_Configuration__listConfLocalAccounts->setContainment(true);
    m_Configuration__listConfLocalAccounts->setResolveProxies(true);
    m_Configuration__listConfLocalAccounts->setUnique(true);
    m_Configuration__listConfLocalAccounts->setDerived(false);
    m_Configuration__listConfLocalAccounts->setOrdered(true);
    m_Configuration__ListConfAuthSystems->setEType(m_AuthSystemEClass);
    m_Configuration__ListConfAuthSystems->setName("ListConfAuthSystems");
    m_Configuration__ListConfAuthSystems->setDefaultValueLiteral("");
    m_Configuration__ListConfAuthSystems->setLowerBound(0);
    m_Configuration__ListConfAuthSystems->setUpperBound(-1);
    m_Configuration__ListConfAuthSystems->setTransient(false);
    m_Configuration__ListConfAuthSystems->setVolatile(false);
    m_Configuration__ListConfAuthSystems->setChangeable(true);
    m_Configuration__ListConfAuthSystems->setContainment(true);
    m_Configuration__ListConfAuthSystems->setResolveProxies(true);
    m_Configuration__ListConfAuthSystems->setUnique(true);
    m_Configuration__ListConfAuthSystems->setDerived(false);
    m_Configuration__ListConfAuthSystems->setOrdered(true);
    m_Configuration__ListConfAuthAccounts->setEType(m_AuthAccountEClass);
    m_Configuration__ListConfAuthAccounts->setName("ListConfAuthAccounts");
    m_Configuration__ListConfAuthAccounts->setDefaultValueLiteral("");
    m_Configuration__ListConfAuthAccounts->setLowerBound(0);
    m_Configuration__ListConfAuthAccounts->setUpperBound(-1);
    m_Configuration__ListConfAuthAccounts->setTransient(false);
    m_Configuration__ListConfAuthAccounts->setVolatile(false);
    m_Configuration__ListConfAuthAccounts->setChangeable(true);
    m_Configuration__ListConfAuthAccounts->setContainment(true);
    m_Configuration__ListConfAuthAccounts->setResolveProxies(true);
    m_Configuration__ListConfAuthAccounts->setUnique(true);
    m_Configuration__ListConfAuthAccounts->setDerived(false);
    m_Configuration__ListConfAuthAccounts->setOrdered(true);
    // OptionValue
    m_OptionValueEClass->setName("OptionValue");
    m_OptionValueEClass->setAbstract(false);
    m_OptionValueEClass->setInterface(false);
    m_OptionValue__optionName->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_OptionValue__optionName->setName("optionName");
    m_OptionValue__optionName->setDefaultValueLiteral("" "");
    m_OptionValue__optionName->setLowerBound(1);
    m_OptionValue__optionName->setUpperBound(1);
    m_OptionValue__optionName->setTransient(false);
    m_OptionValue__optionName->setVolatile(false);
    m_OptionValue__optionName->setChangeable(true);
    m_OptionValue__optionName->setUnsettable(false);
    m_OptionValue__optionName->setID(false);
    m_OptionValue__optionName->setUnique(true);
    m_OptionValue__optionName->setDerived(false);
    m_OptionValue__optionName->setOrdered(true);
    m_OptionValue__value->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_OptionValue__value->setName("value");
    m_OptionValue__value->setDefaultValueLiteral("");
    m_OptionValue__value->setLowerBound(1);
    m_OptionValue__value->setUpperBound(1);
    m_OptionValue__value->setTransient(false);
    m_OptionValue__value->setVolatile(false);
    m_OptionValue__value->setChangeable(true);
    m_OptionValue__value->setUnsettable(false);
    m_OptionValue__value->setID(false);
    m_OptionValue__value->setUnique(true);
    m_OptionValue__value->setDerived(false);
    m_OptionValue__value->setOrdered(true);
    // ListOptionsValues
    m_ListOptionsValuesEClass->setName("ListOptionsValues");
    m_ListOptionsValuesEClass->setAbstract(false);
    m_ListOptionsValuesEClass->setInterface(false);
    m_ListOptionsValues__optionValues->setEType(m_OptionValueEClass);
    m_ListOptionsValues__optionValues->setName("optionValues");
    m_ListOptionsValues__optionValues->setDefaultValueLiteral("");
    m_ListOptionsValues__optionValues->setLowerBound(0);
    m_ListOptionsValues__optionValues->setUpperBound(-1);
    m_ListOptionsValues__optionValues->setTransient(false);
    m_ListOptionsValues__optionValues->setVolatile(false);
    m_ListOptionsValues__optionValues->setChangeable(true);
    m_ListOptionsValues__optionValues->setContainment(true);
    m_ListOptionsValues__optionValues->setResolveProxies(true);
    m_ListOptionsValues__optionValues->setUnique(true);
    m_ListOptionsValues__optionValues->setDerived(false);
    m_ListOptionsValues__optionValues->setOrdered(true);
    // ListOptOptions
    m_ListOptOptionsEClass->setName("ListOptOptions");
    m_ListOptOptionsEClass->setAbstract(false);
    m_ListOptOptionsEClass->setInterface(false);
    m_ListOptOptions__listAllDeftValue->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_ListOptOptions__listAllDeftValue->setName("listAllDeftValue");
    m_ListOptOptions__listAllDeftValue->setDefaultValueLiteral("false");
    m_ListOptOptions__listAllDeftValue->setLowerBound(0);
    m_ListOptOptions__listAllDeftValue->setUpperBound(1);
    m_ListOptOptions__listAllDeftValue->setTransient(false);
    m_ListOptOptions__listAllDeftValue->setVolatile(false);
    m_ListOptOptions__listAllDeftValue->setChangeable(true);
    m_ListOptOptions__listAllDeftValue->setUnsettable(false);
    m_ListOptOptions__listAllDeftValue->setID(false);
    m_ListOptOptions__listAllDeftValue->setUnique(true);
    m_ListOptOptions__listAllDeftValue->setDerived(false);
    m_ListOptOptions__listAllDeftValue->setOrdered(true);
    m_ListOptOptions__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListOptOptions__userId->setName("userId");
    m_ListOptOptions__userId->setDefaultValueLiteral("");
    m_ListOptOptions__userId->setLowerBound(0);
    m_ListOptOptions__userId->setUpperBound(1);
    m_ListOptOptions__userId->setTransient(false);
    m_ListOptOptions__userId->setVolatile(false);
    m_ListOptOptions__userId->setChangeable(true);
    m_ListOptOptions__userId->setUnsettable(false);
    m_ListOptOptions__userId->setID(false);
    m_ListOptOptions__userId->setUnique(true);
    m_ListOptOptions__userId->setDerived(false);
    m_ListOptOptions__userId->setOrdered(true);
    m_ListOptOptions__optionName->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListOptOptions__optionName->setName("optionName");
    m_ListOptOptions__optionName->setDefaultValueLiteral("" "");
    m_ListOptOptions__optionName->setLowerBound(0);
    m_ListOptOptions__optionName->setUpperBound(1);
    m_ListOptOptions__optionName->setTransient(false);
    m_ListOptOptions__optionName->setVolatile(false);
    m_ListOptOptions__optionName->setChangeable(true);
    m_ListOptOptions__optionName->setUnsettable(false);
    m_ListOptOptions__optionName->setID(false);
    m_ListOptOptions__optionName->setUnique(true);
    m_ListOptOptions__optionName->setDerived(false);
    m_ListOptOptions__optionName->setOrdered(true);
    // AuthSystem
    m_AuthSystemEClass->setName("AuthSystem");
    m_AuthSystemEClass->setAbstract(false);
    m_AuthSystemEClass->setInterface(false);
    m_AuthSystem__authSystemId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AuthSystem__authSystemId->setName("authSystemId");
    m_AuthSystem__authSystemId->setDefaultValueLiteral("" "");
    m_AuthSystem__authSystemId->setLowerBound(1);
    m_AuthSystem__authSystemId->setUpperBound(1);
    m_AuthSystem__authSystemId->setTransient(false);
    m_AuthSystem__authSystemId->setVolatile(false);
    m_AuthSystem__authSystemId->setChangeable(true);
    m_AuthSystem__authSystemId->setUnsettable(false);
    m_AuthSystem__authSystemId->setID(false);
    m_AuthSystem__authSystemId->setUnique(true);
    m_AuthSystem__authSystemId->setDerived(false);
    m_AuthSystem__authSystemId->setOrdered(true);
    m_AuthSystem__name->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AuthSystem__name->setName("name");
    m_AuthSystem__name->setDefaultValueLiteral("" "");
    m_AuthSystem__name->setLowerBound(1);
    m_AuthSystem__name->setUpperBound(1);
    m_AuthSystem__name->setTransient(false);
    m_AuthSystem__name->setVolatile(false);
    m_AuthSystem__name->setChangeable(true);
    m_AuthSystem__name->setUnsettable(false);
    m_AuthSystem__name->setID(false);
    m_AuthSystem__name->setUnique(true);
    m_AuthSystem__name->setDerived(false);
    m_AuthSystem__name->setOrdered(true);
    m_AuthSystem__URI->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AuthSystem__URI->setName("URI");
    m_AuthSystem__URI->setDefaultValueLiteral("" "");
    m_AuthSystem__URI->setLowerBound(1);
    m_AuthSystem__URI->setUpperBound(1);
    m_AuthSystem__URI->setTransient(false);
    m_AuthSystem__URI->setVolatile(false);
    m_AuthSystem__URI->setChangeable(true);
    m_AuthSystem__URI->setUnsettable(false);
    m_AuthSystem__URI->setID(false);
    m_AuthSystem__URI->setUnique(true);
    m_AuthSystem__URI->setDerived(false);
    m_AuthSystem__URI->setOrdered(true);
    m_AuthSystem__authLogin->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AuthSystem__authLogin->setName("authLogin");
    m_AuthSystem__authLogin->setDefaultValueLiteral("" "");
    m_AuthSystem__authLogin->setLowerBound(1);
    m_AuthSystem__authLogin->setUpperBound(1);
    m_AuthSystem__authLogin->setTransient(false);
    m_AuthSystem__authLogin->setVolatile(false);
    m_AuthSystem__authLogin->setChangeable(true);
    m_AuthSystem__authLogin->setUnsettable(false);
    m_AuthSystem__authLogin->setID(false);
    m_AuthSystem__authLogin->setUnique(true);
    m_AuthSystem__authLogin->setDerived(false);
    m_AuthSystem__authLogin->setOrdered(true);
    m_AuthSystem__authPassword->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AuthSystem__authPassword->setName("authPassword");
    m_AuthSystem__authPassword->setDefaultValueLiteral("" "");
    m_AuthSystem__authPassword->setLowerBound(1);
    m_AuthSystem__authPassword->setUpperBound(1);
    m_AuthSystem__authPassword->setTransient(false);
    m_AuthSystem__authPassword->setVolatile(false);
    m_AuthSystem__authPassword->setChangeable(true);
    m_AuthSystem__authPassword->setUnsettable(false);
    m_AuthSystem__authPassword->setID(false);
    m_AuthSystem__authPassword->setUnique(true);
    m_AuthSystem__authPassword->setDerived(false);
    m_AuthSystem__authPassword->setOrdered(true);
    m_AuthSystem__userPasswordEncryption->setEType(m_EncryptionMethodEEnum);
    m_AuthSystem__userPasswordEncryption->setName("userPasswordEncryption");
    m_AuthSystem__userPasswordEncryption->setDefaultValueLiteral("-1");
    m_AuthSystem__userPasswordEncryption->setLowerBound(1);
    m_AuthSystem__userPasswordEncryption->setUpperBound(1);
    m_AuthSystem__userPasswordEncryption->setTransient(false);
    m_AuthSystem__userPasswordEncryption->setVolatile(false);
    m_AuthSystem__userPasswordEncryption->setChangeable(true);
    m_AuthSystem__userPasswordEncryption->setUnsettable(false);
    m_AuthSystem__userPasswordEncryption->setID(false);
    m_AuthSystem__userPasswordEncryption->setUnique(true);
    m_AuthSystem__userPasswordEncryption->setDerived(false);
    m_AuthSystem__userPasswordEncryption->setOrdered(true);
    m_AuthSystem__type->setEType(m_AuthTypeEEnum);
    m_AuthSystem__type->setName("type");
    m_AuthSystem__type->setDefaultValueLiteral("-1");
    m_AuthSystem__type->setLowerBound(0);
    m_AuthSystem__type->setUpperBound(1);
    m_AuthSystem__type->setTransient(false);
    m_AuthSystem__type->setVolatile(false);
    m_AuthSystem__type->setChangeable(true);
    m_AuthSystem__type->setUnsettable(false);
    m_AuthSystem__type->setID(false);
    m_AuthSystem__type->setUnique(true);
    m_AuthSystem__type->setDerived(false);
    m_AuthSystem__type->setOrdered(true);
    m_AuthSystem__status->setEType(m_StatusTypeEEnum);
    m_AuthSystem__status->setName("status");
    m_AuthSystem__status->setDefaultValueLiteral("-1");
    m_AuthSystem__status->setLowerBound(0);
    m_AuthSystem__status->setUpperBound(1);
    m_AuthSystem__status->setTransient(false);
    m_AuthSystem__status->setVolatile(false);
    m_AuthSystem__status->setChangeable(true);
    m_AuthSystem__status->setUnsettable(false);
    m_AuthSystem__status->setID(false);
    m_AuthSystem__status->setUnique(true);
    m_AuthSystem__status->setDerived(false);
    m_AuthSystem__status->setOrdered(true);
    m_AuthSystem__ldapBase->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AuthSystem__ldapBase->setName("ldapBase");
    m_AuthSystem__ldapBase->setDefaultValueLiteral("" "");
    m_AuthSystem__ldapBase->setLowerBound(0);
    m_AuthSystem__ldapBase->setUpperBound(1);
    m_AuthSystem__ldapBase->setTransient(false);
    m_AuthSystem__ldapBase->setVolatile(false);
    m_AuthSystem__ldapBase->setChangeable(true);
    m_AuthSystem__ldapBase->setUnsettable(false);
    m_AuthSystem__ldapBase->setID(false);
    m_AuthSystem__ldapBase->setUnique(true);
    m_AuthSystem__ldapBase->setDerived(false);
    m_AuthSystem__ldapBase->setOrdered(true);
    // ListAuthSystems
    m_ListAuthSystemsEClass->setName("ListAuthSystems");
    m_ListAuthSystemsEClass->setAbstract(false);
    m_ListAuthSystemsEClass->setInterface(false);
    m_ListAuthSystems__AuthSystems->setEType(m_AuthSystemEClass);
    m_ListAuthSystems__AuthSystems->setName("AuthSystems");
    m_ListAuthSystems__AuthSystems->setDefaultValueLiteral("");
    m_ListAuthSystems__AuthSystems->setLowerBound(0);
    m_ListAuthSystems__AuthSystems->setUpperBound(-1);
    m_ListAuthSystems__AuthSystems->setTransient(false);
    m_ListAuthSystems__AuthSystems->setVolatile(false);
    m_ListAuthSystems__AuthSystems->setChangeable(true);
    m_ListAuthSystems__AuthSystems->setContainment(true);
    m_ListAuthSystems__AuthSystems->setResolveProxies(true);
    m_ListAuthSystems__AuthSystems->setUnique(true);
    m_ListAuthSystems__AuthSystems->setDerived(false);
    m_ListAuthSystems__AuthSystems->setOrdered(true);
    // ListAuthSysOptions
    m_ListAuthSysOptionsEClass->setName("ListAuthSysOptions");
    m_ListAuthSysOptionsEClass->setAbstract(false);
    m_ListAuthSysOptionsEClass->setInterface(false);
    m_ListAuthSysOptions__listAllAuthSystems->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_ListAuthSysOptions__listAllAuthSystems->setName("listAllAuthSystems");
    m_ListAuthSysOptions__listAllAuthSystems->setDefaultValueLiteral("false");
    m_ListAuthSysOptions__listAllAuthSystems->setLowerBound(0);
    m_ListAuthSysOptions__listAllAuthSystems->setUpperBound(1);
    m_ListAuthSysOptions__listAllAuthSystems->setTransient(false);
    m_ListAuthSysOptions__listAllAuthSystems->setVolatile(false);
    m_ListAuthSysOptions__listAllAuthSystems->setChangeable(true);
    m_ListAuthSysOptions__listAllAuthSystems->setUnsettable(false);
    m_ListAuthSysOptions__listAllAuthSystems->setID(false);
    m_ListAuthSysOptions__listAllAuthSystems->setUnique(true);
    m_ListAuthSysOptions__listAllAuthSystems->setDerived(false);
    m_ListAuthSysOptions__listAllAuthSystems->setOrdered(true);
    m_ListAuthSysOptions__listFullInfo->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_ListAuthSysOptions__listFullInfo->setName("listFullInfo");
    m_ListAuthSysOptions__listFullInfo->setDefaultValueLiteral("false");
    m_ListAuthSysOptions__listFullInfo->setLowerBound(0);
    m_ListAuthSysOptions__listFullInfo->setUpperBound(1);
    m_ListAuthSysOptions__listFullInfo->setTransient(false);
    m_ListAuthSysOptions__listFullInfo->setVolatile(false);
    m_ListAuthSysOptions__listFullInfo->setChangeable(true);
    m_ListAuthSysOptions__listFullInfo->setUnsettable(false);
    m_ListAuthSysOptions__listFullInfo->setID(false);
    m_ListAuthSysOptions__listFullInfo->setUnique(true);
    m_ListAuthSysOptions__listFullInfo->setDerived(false);
    m_ListAuthSysOptions__listFullInfo->setOrdered(true);
    m_ListAuthSysOptions__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListAuthSysOptions__userId->setName("userId");
    m_ListAuthSysOptions__userId->setDefaultValueLiteral("");
    m_ListAuthSysOptions__userId->setLowerBound(0);
    m_ListAuthSysOptions__userId->setUpperBound(1);
    m_ListAuthSysOptions__userId->setTransient(false);
    m_ListAuthSysOptions__userId->setVolatile(false);
    m_ListAuthSysOptions__userId->setChangeable(true);
    m_ListAuthSysOptions__userId->setUnsettable(false);
    m_ListAuthSysOptions__userId->setID(false);
    m_ListAuthSysOptions__userId->setUnique(true);
    m_ListAuthSysOptions__userId->setDerived(false);
    m_ListAuthSysOptions__userId->setOrdered(true);
    m_ListAuthSysOptions__authSystemId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListAuthSysOptions__authSystemId->setName("authSystemId");
    m_ListAuthSysOptions__authSystemId->setDefaultValueLiteral("" "");
    m_ListAuthSysOptions__authSystemId->setLowerBound(0);
    m_ListAuthSysOptions__authSystemId->setUpperBound(1);
    m_ListAuthSysOptions__authSystemId->setTransient(false);
    m_ListAuthSysOptions__authSystemId->setVolatile(false);
    m_ListAuthSysOptions__authSystemId->setChangeable(true);
    m_ListAuthSysOptions__authSystemId->setUnsettable(false);
    m_ListAuthSysOptions__authSystemId->setID(false);
    m_ListAuthSysOptions__authSystemId->setUnique(true);
    m_ListAuthSysOptions__authSystemId->setDerived(false);
    m_ListAuthSysOptions__authSystemId->setOrdered(true);
    // AuthAccount
    m_AuthAccountEClass->setName("AuthAccount");
    m_AuthAccountEClass->setAbstract(false);
    m_AuthAccountEClass->setInterface(false);
    m_AuthAccount__authSystemId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AuthAccount__authSystemId->setName("authSystemId");
    m_AuthAccount__authSystemId->setDefaultValueLiteral("" "");
    m_AuthAccount__authSystemId->setLowerBound(1);
    m_AuthAccount__authSystemId->setUpperBound(1);
    m_AuthAccount__authSystemId->setTransient(false);
    m_AuthAccount__authSystemId->setVolatile(false);
    m_AuthAccount__authSystemId->setChangeable(true);
    m_AuthAccount__authSystemId->setUnsettable(false);
    m_AuthAccount__authSystemId->setID(false);
    m_AuthAccount__authSystemId->setUnique(true);
    m_AuthAccount__authSystemId->setDerived(false);
    m_AuthAccount__authSystemId->setOrdered(true);
    m_AuthAccount__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AuthAccount__userId->setName("userId");
    m_AuthAccount__userId->setDefaultValueLiteral("" "");
    m_AuthAccount__userId->setLowerBound(0);
    m_AuthAccount__userId->setUpperBound(1);
    m_AuthAccount__userId->setTransient(false);
    m_AuthAccount__userId->setVolatile(false);
    m_AuthAccount__userId->setChangeable(true);
    m_AuthAccount__userId->setUnsettable(false);
    m_AuthAccount__userId->setID(false);
    m_AuthAccount__userId->setUnique(true);
    m_AuthAccount__userId->setDerived(false);
    m_AuthAccount__userId->setOrdered(true);
    m_AuthAccount__acLogin->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_AuthAccount__acLogin->setName("acLogin");
    m_AuthAccount__acLogin->setDefaultValueLiteral("" "");
    m_AuthAccount__acLogin->setLowerBound(1);
    m_AuthAccount__acLogin->setUpperBound(1);
    m_AuthAccount__acLogin->setTransient(false);
    m_AuthAccount__acLogin->setVolatile(false);
    m_AuthAccount__acLogin->setChangeable(true);
    m_AuthAccount__acLogin->setUnsettable(false);
    m_AuthAccount__acLogin->setID(false);
    m_AuthAccount__acLogin->setUnique(true);
    m_AuthAccount__acLogin->setDerived(false);
    m_AuthAccount__acLogin->setOrdered(true);
    // ListAuthAccounts
    m_ListAuthAccountsEClass->setName("ListAuthAccounts");
    m_ListAuthAccountsEClass->setAbstract(false);
    m_ListAuthAccountsEClass->setInterface(false);
    m_ListAuthAccounts__AuthAccounts->setEType(m_AuthAccountEClass);
    m_ListAuthAccounts__AuthAccounts->setName("AuthAccounts");
    m_ListAuthAccounts__AuthAccounts->setDefaultValueLiteral("");
    m_ListAuthAccounts__AuthAccounts->setLowerBound(0);
    m_ListAuthAccounts__AuthAccounts->setUpperBound(-1);
    m_ListAuthAccounts__AuthAccounts->setTransient(false);
    m_ListAuthAccounts__AuthAccounts->setVolatile(false);
    m_ListAuthAccounts__AuthAccounts->setChangeable(true);
    m_ListAuthAccounts__AuthAccounts->setContainment(true);
    m_ListAuthAccounts__AuthAccounts->setResolveProxies(true);
    m_ListAuthAccounts__AuthAccounts->setUnique(true);
    m_ListAuthAccounts__AuthAccounts->setDerived(false);
    m_ListAuthAccounts__AuthAccounts->setOrdered(true);
    // ListAuthAccOptions
    m_ListAuthAccOptionsEClass->setName("ListAuthAccOptions");
    m_ListAuthAccOptionsEClass->setAbstract(false);
    m_ListAuthAccOptionsEClass->setInterface(false);
    m_ListAuthAccOptions__listAll->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_ListAuthAccOptions__listAll->setName("listAll");
    m_ListAuthAccOptions__listAll->setDefaultValueLiteral("false");
    m_ListAuthAccOptions__listAll->setLowerBound(0);
    m_ListAuthAccOptions__listAll->setUpperBound(1);
    m_ListAuthAccOptions__listAll->setTransient(false);
    m_ListAuthAccOptions__listAll->setVolatile(false);
    m_ListAuthAccOptions__listAll->setChangeable(true);
    m_ListAuthAccOptions__listAll->setUnsettable(false);
    m_ListAuthAccOptions__listAll->setID(false);
    m_ListAuthAccOptions__listAll->setUnique(true);
    m_ListAuthAccOptions__listAll->setDerived(false);
    m_ListAuthAccOptions__listAll->setOrdered(true);
    m_ListAuthAccOptions__userId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListAuthAccOptions__userId->setName("userId");
    m_ListAuthAccOptions__userId->setDefaultValueLiteral("");
    m_ListAuthAccOptions__userId->setLowerBound(0);
    m_ListAuthAccOptions__userId->setUpperBound(1);
    m_ListAuthAccOptions__userId->setTransient(false);
    m_ListAuthAccOptions__userId->setVolatile(false);
    m_ListAuthAccOptions__userId->setChangeable(true);
    m_ListAuthAccOptions__userId->setUnsettable(false);
    m_ListAuthAccOptions__userId->setID(false);
    m_ListAuthAccOptions__userId->setUnique(true);
    m_ListAuthAccOptions__userId->setDerived(false);
    m_ListAuthAccOptions__userId->setOrdered(true);
    m_ListAuthAccOptions__authSystemId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ListAuthAccOptions__authSystemId->setName("authSystemId");
    m_ListAuthAccOptions__authSystemId->setDefaultValueLiteral("" "");
    m_ListAuthAccOptions__authSystemId->setLowerBound(0);
    m_ListAuthAccOptions__authSystemId->setUpperBound(1);
    m_ListAuthAccOptions__authSystemId->setTransient(false);
    m_ListAuthAccOptions__authSystemId->setVolatile(false);
    m_ListAuthAccOptions__authSystemId->setChangeable(true);
    m_ListAuthAccOptions__authSystemId->setUnsettable(false);
    m_ListAuthAccOptions__authSystemId->setID(false);
    m_ListAuthAccOptions__authSystemId->setUnique(true);
    m_ListAuthAccOptions__authSystemId->setDerived(false);
    m_ListAuthAccOptions__authSystemId->setOrdered(true);
    // Version
    m_VersionEClass->setName("Version");
    m_VersionEClass->setAbstract(false);
    m_VersionEClass->setInterface(false);
    m_Version__major->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Version__major->setName("major");
    m_Version__major->setDefaultValueLiteral("0");
    m_Version__major->setLowerBound(0);
    m_Version__major->setUpperBound(1);
    m_Version__major->setTransient(false);
    m_Version__major->setVolatile(false);
    m_Version__major->setChangeable(true);
    m_Version__major->setUnsettable(false);
    m_Version__major->setID(false);
    m_Version__major->setUnique(true);
    m_Version__major->setDerived(false);
    m_Version__major->setOrdered(true);
    m_Version__minor->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Version__minor->setName("minor");
    m_Version__minor->setDefaultValueLiteral("0");
    m_Version__minor->setLowerBound(0);
    m_Version__minor->setUpperBound(1);
    m_Version__minor->setTransient(false);
    m_Version__minor->setVolatile(false);
    m_Version__minor->setChangeable(true);
    m_Version__minor->setUnsettable(false);
    m_Version__minor->setID(false);
    m_Version__minor->setUnique(true);
    m_Version__minor->setDerived(false);
    m_Version__minor->setOrdered(true);
    m_Version__patch->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Version__patch->setName("patch");
    m_Version__patch->setDefaultValueLiteral("0");
    m_Version__patch->setLowerBound(0);
    m_Version__patch->setUpperBound(1);
    m_Version__patch->setTransient(false);
    m_Version__patch->setVolatile(false);
    m_Version__patch->setChangeable(true);
    m_Version__patch->setUnsettable(false);
    m_Version__patch->setID(false);
    m_Version__patch->setUnique(true);
    m_Version__patch->setDerived(false);
    m_Version__patch->setOrdered(true);
    m_Version__stringformat->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Version__stringformat->setName("stringformat");
    m_Version__stringformat->setDefaultValueLiteral("" "");
    m_Version__stringformat->setLowerBound(0);
    m_Version__stringformat->setUpperBound(1);
    m_Version__stringformat->setTransient(false);
    m_Version__stringformat->setVolatile(false);
    m_Version__stringformat->setChangeable(true);
    m_Version__stringformat->setUnsettable(false);
    m_Version__stringformat->setID(false);
    m_Version__stringformat->setUnique(true);
    m_Version__stringformat->setDerived(false);
    m_Version__stringformat->setOrdered(true);

    // TODO: Initialize data types


    // SessionCloseType
    m_SessionCloseTypeEEnum->setName("SessionCloseType");
    m_SessionCloseTypeEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // DEFAULT
        _el->setName("DEFAULT");
        _el->setValue(0);
        _el->setLiteral("DEFAULT");
        _el->setEEnum(m_SessionCloseTypeEEnum);
        m_SessionCloseTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // CLOSE_ON_TIMEOUT
        _el->setName("CLOSE_ON_TIMEOUT");
        _el->setValue(1);
        _el->setLiteral("CLOSE_ON_TIMEOUT");
        _el->setEEnum(m_SessionCloseTypeEEnum);
        m_SessionCloseTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // CLOSE_ON_DISCONNECT
        _el->setName("CLOSE_ON_DISCONNECT");
        _el->setValue(2);
        _el->setLiteral("CLOSE_ON_DISCONNECT");
        _el->setEEnum(m_SessionCloseTypeEEnum);
        m_SessionCloseTypeEEnum->getELiterals().push_back(_el);
    }

    // PrivilegeType
    m_PrivilegeTypeEEnum->setName("PrivilegeType");
    m_PrivilegeTypeEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // USER
        _el->setName("USER");
        _el->setValue(0);
        _el->setLiteral("USER");
        _el->setEEnum(m_PrivilegeTypeEEnum);
        m_PrivilegeTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // ADMIN
        _el->setName("ADMIN");
        _el->setValue(1);
        _el->setLiteral("ADMIN");
        _el->setEEnum(m_PrivilegeTypeEEnum);
        m_PrivilegeTypeEEnum->getELiterals().push_back(_el);
    }

    // StatusType
    m_StatusTypeEEnum->setName("StatusType");
    m_StatusTypeEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // UNDEFINED
        _el->setName("UNDEFINED");
        _el->setValue(0);
        _el->setLiteral("UNDEFINED");
        _el->setEEnum(m_StatusTypeEEnum);
        m_StatusTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // INACTIVE
        _el->setName("INACTIVE");
        _el->setValue(1);
        _el->setLiteral("INACTIVE");
        _el->setEEnum(m_StatusTypeEEnum);
        m_StatusTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // ACTIVE
        _el->setName("ACTIVE");
        _el->setValue(2);
        _el->setLiteral("ACTIVE");
        _el->setEEnum(m_StatusTypeEEnum);
        m_StatusTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // DELETED
        _el->setName("DELETED");
        _el->setValue(3);
        _el->setLiteral("DELETED");
        _el->setEEnum(m_StatusTypeEEnum);
        m_StatusTypeEEnum->getELiterals().push_back(_el);
    }

    // CommandStatusType
    m_CommandStatusTypeEEnum->setName("CommandStatusType");
    m_CommandStatusTypeEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // FAILURE
        _el->setName("FAILURE");
        _el->setValue(0);
        _el->setLiteral("FAILURE");
        _el->setEEnum(m_CommandStatusTypeEEnum);
        m_CommandStatusTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // SUCCESS
        _el->setName("SUCCESS");
        _el->setValue(1);
        _el->setLiteral("SUCCESS");
        _el->setEEnum(m_CommandStatusTypeEEnum);
        m_CommandStatusTypeEEnum->getELiterals().push_back(_el);
    }

    // AuthType
    m_AuthTypeEEnum->setName("AuthType");
    m_AuthTypeEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // UNDEFINED
        _el->setName("UNDEFINED");
        _el->setValue(0);
        _el->setLiteral("UNDEFINED");
        _el->setEEnum(m_AuthTypeEEnum);
        m_AuthTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // LDAP
        _el->setName("LDAP");
        _el->setValue(1);
        _el->setLiteral("LDAP");
        _el->setEEnum(m_AuthTypeEEnum);
        m_AuthTypeEEnum->getELiterals().push_back(_el);
    }

    // EncryptionMethod
    m_EncryptionMethodEEnum->setName("EncryptionMethod");
    m_EncryptionMethodEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // UNDEFINED
        _el->setName("UNDEFINED");
        _el->setValue(0);
        _el->setLiteral("UNDEFINED");
        _el->setEEnum(m_EncryptionMethodEEnum);
        m_EncryptionMethodEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // SSHA
        _el->setName("SSHA");
        _el->setValue(1);
        _el->setLiteral("SSHA");
        _el->setEEnum(m_EncryptionMethodEEnum);
        m_EncryptionMethodEEnum->getELiterals().push_back(_el);
    }

    _initialize();
}

::ecore::EClass_ptr UMS_DataPackage::getConnectOptions()
{
    return m_ConnectOptionsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getSession()
{
    return m_SessionEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListSessions()
{
    return m_ListSessionsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListSessionOptions()
{
    return m_ListSessionOptionsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getUser()
{
    return m_UserEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListUsers()
{
    return m_ListUsersEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListUsersOptions()
{
    return m_ListUsersOptionsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getCommand()
{
    return m_CommandEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListCommands()
{
    return m_ListCommandsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListCmdOptions()
{
    return m_ListCmdOptionsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getLocalAccount()
{
    return m_LocalAccountEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListLocalAccounts()
{
    return m_ListLocalAccountsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListLocalAccOptions()
{
    return m_ListLocalAccOptionsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getMachine()
{
    return m_MachineEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListMachines()
{
    return m_ListMachinesEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListMachineOptions()
{
    return m_ListMachineOptionsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getConfiguration()
{
    return m_ConfigurationEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getOptionValue()
{
    return m_OptionValueEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListOptionsValues()
{
    return m_ListOptionsValuesEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListOptOptions()
{
    return m_ListOptOptionsEClass;
}
::ecore::EEnum_ptr UMS_DataPackage::getSessionCloseType()
{
    return m_SessionCloseTypeEEnum;
}
::ecore::EEnum_ptr UMS_DataPackage::getPrivilegeType()
{
    return m_PrivilegeTypeEEnum;
}
::ecore::EEnum_ptr UMS_DataPackage::getStatusType()
{
    return m_StatusTypeEEnum;
}
::ecore::EEnum_ptr UMS_DataPackage::getCommandStatusType()
{
    return m_CommandStatusTypeEEnum;
}
::ecore::EClass_ptr UMS_DataPackage::getAuthSystem()
{
    return m_AuthSystemEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListAuthSystems()
{
    return m_ListAuthSystemsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListAuthSysOptions()
{
    return m_ListAuthSysOptionsEClass;
}
::ecore::EEnum_ptr UMS_DataPackage::getAuthType()
{
    return m_AuthTypeEEnum;
}
::ecore::EClass_ptr UMS_DataPackage::getAuthAccount()
{
    return m_AuthAccountEClass;
}
::ecore::EEnum_ptr UMS_DataPackage::getEncryptionMethod()
{
    return m_EncryptionMethodEEnum;
}
::ecore::EClass_ptr UMS_DataPackage::getListAuthAccounts()
{
    return m_ListAuthAccountsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getListAuthAccOptions()
{
    return m_ListAuthAccOptionsEClass;
}
::ecore::EClass_ptr UMS_DataPackage::getVersion()
{
    return m_VersionEClass;
}

::ecore::EAttribute_ptr UMS_DataPackage::getConnectOptions__closePolicy()
{
    return m_ConnectOptions__closePolicy;
}
::ecore::EAttribute_ptr UMS_DataPackage::getConnectOptions__sessionInactivityDelay()
{
    return m_ConnectOptions__sessionInactivityDelay;
}
::ecore::EAttribute_ptr UMS_DataPackage::getConnectOptions__substituteUserId()
{
    return m_ConnectOptions__substituteUserId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getSession__sessionId()
{
    return m_Session__sessionId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getSession__userId()
{
    return m_Session__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getSession__sessionKey()
{
    return m_Session__sessionKey;
}
::ecore::EAttribute_ptr UMS_DataPackage::getSession__dateLastConnect()
{
    return m_Session__dateLastConnect;
}
::ecore::EAttribute_ptr UMS_DataPackage::getSession__dateCreation()
{
    return m_Session__dateCreation;
}
::ecore::EAttribute_ptr UMS_DataPackage::getSession__dateClosure()
{
    return m_Session__dateClosure;
}
::ecore::EAttribute_ptr UMS_DataPackage::getSession__status()
{
    return m_Session__status;
}
::ecore::EAttribute_ptr UMS_DataPackage::getSession__closePolicy()
{
    return m_Session__closePolicy;
}
::ecore::EAttribute_ptr UMS_DataPackage::getSession__timeout()
{
    return m_Session__timeout;
}
::ecore::EAttribute_ptr UMS_DataPackage::getSession__authenId()
{
    return m_Session__authenId;
}
::ecore::EReference_ptr UMS_DataPackage::getListSessions__sessions()
{
    return m_ListSessions__sessions;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListSessionOptions__status()
{
    return m_ListSessionOptions__status;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListSessionOptions__sessionClosePolicy()
{
    return m_ListSessionOptions__sessionClosePolicy;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListSessionOptions__sessionInactivityDelay()
{
    return m_ListSessionOptions__sessionInactivityDelay;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListSessionOptions__machineId()
{
    return m_ListSessionOptions__machineId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListSessionOptions__adminListOption()
{
    return m_ListSessionOptions__adminListOption;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListSessionOptions__userId()
{
    return m_ListSessionOptions__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListSessionOptions__sessionId()
{
    return m_ListSessionOptions__sessionId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListSessionOptions__startDateOption()
{
    return m_ListSessionOptions__startDateOption;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListSessionOptions__endDateOption()
{
    return m_ListSessionOptions__endDateOption;
}
::ecore::EAttribute_ptr UMS_DataPackage::getUser__userId()
{
    return m_User__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getUser__password()
{
    return m_User__password;
}
::ecore::EAttribute_ptr UMS_DataPackage::getUser__firstname()
{
    return m_User__firstname;
}
::ecore::EAttribute_ptr UMS_DataPackage::getUser__lastname()
{
    return m_User__lastname;
}
::ecore::EAttribute_ptr UMS_DataPackage::getUser__privilege()
{
    return m_User__privilege;
}
::ecore::EAttribute_ptr UMS_DataPackage::getUser__email()
{
    return m_User__email;
}
::ecore::EAttribute_ptr UMS_DataPackage::getUser__status()
{
    return m_User__status;
}
::ecore::EReference_ptr UMS_DataPackage::getListUsers__users()
{
    return m_ListUsers__users;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListUsersOptions__userId()
{
    return m_ListUsersOptions__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListUsersOptions__authSystemId()
{
    return m_ListUsersOptions__authSystemId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getCommand__commandId()
{
    return m_Command__commandId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getCommand__sessionId()
{
    return m_Command__sessionId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getCommand__machineId()
{
    return m_Command__machineId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getCommand__cmdDescription()
{
    return m_Command__cmdDescription;
}
::ecore::EAttribute_ptr UMS_DataPackage::getCommand__cmdStartTime()
{
    return m_Command__cmdStartTime;
}
::ecore::EAttribute_ptr UMS_DataPackage::getCommand__cmdEndTime()
{
    return m_Command__cmdEndTime;
}
::ecore::EAttribute_ptr UMS_DataPackage::getCommand__status()
{
    return m_Command__status;
}
::ecore::EReference_ptr UMS_DataPackage::getListCommands__Commands()
{
    return m_ListCommands__Commands;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListCmdOptions__adminListOption()
{
    return m_ListCmdOptions__adminListOption;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListCmdOptions__userId()
{
    return m_ListCmdOptions__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListCmdOptions__sessionId()
{
    return m_ListCmdOptions__sessionId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListCmdOptions__startDateOption()
{
    return m_ListCmdOptions__startDateOption;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListCmdOptions__endDateOption()
{
    return m_ListCmdOptions__endDateOption;
}
::ecore::EAttribute_ptr UMS_DataPackage::getLocalAccount__userId()
{
    return m_LocalAccount__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getLocalAccount__machineId()
{
    return m_LocalAccount__machineId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getLocalAccount__acLogin()
{
    return m_LocalAccount__acLogin;
}
::ecore::EAttribute_ptr UMS_DataPackage::getLocalAccount__sshKeyPath()
{
    return m_LocalAccount__sshKeyPath;
}
::ecore::EAttribute_ptr UMS_DataPackage::getLocalAccount__homeDirectory()
{
    return m_LocalAccount__homeDirectory;
}
::ecore::EReference_ptr UMS_DataPackage::getListLocalAccounts__accounts()
{
    return m_ListLocalAccounts__accounts;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListLocalAccOptions__adminListOption()
{
    return m_ListLocalAccOptions__adminListOption;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListLocalAccOptions__userId()
{
    return m_ListLocalAccOptions__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListLocalAccOptions__machineId()
{
    return m_ListLocalAccOptions__machineId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getMachine__machineId()
{
    return m_Machine__machineId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getMachine__name()
{
    return m_Machine__name;
}
::ecore::EAttribute_ptr UMS_DataPackage::getMachine__site()
{
    return m_Machine__site;
}
::ecore::EAttribute_ptr UMS_DataPackage::getMachine__machineDescription()
{
    return m_Machine__machineDescription;
}
::ecore::EAttribute_ptr UMS_DataPackage::getMachine__language()
{
    return m_Machine__language;
}
::ecore::EAttribute_ptr UMS_DataPackage::getMachine__status()
{
    return m_Machine__status;
}
::ecore::EAttribute_ptr UMS_DataPackage::getMachine__sshPublicKey()
{
    return m_Machine__sshPublicKey;
}
::ecore::EReference_ptr UMS_DataPackage::getListMachines__machines()
{
    return m_ListMachines__machines;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListMachineOptions__userId()
{
    return m_ListMachineOptions__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListMachineOptions__listAllMachine()
{
    return m_ListMachineOptions__listAllMachine;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListMachineOptions__machineId()
{
    return m_ListMachineOptions__machineId;
}
::ecore::EReference_ptr UMS_DataPackage::getConfiguration__listConfUsers()
{
    return m_Configuration__listConfUsers;
}
::ecore::EReference_ptr UMS_DataPackage::getConfiguration__listConfMachines()
{
    return m_Configuration__listConfMachines;
}
::ecore::EReference_ptr UMS_DataPackage::getConfiguration__listConfLocalAccounts()
{
    return m_Configuration__listConfLocalAccounts;
}
::ecore::EReference_ptr UMS_DataPackage::getConfiguration__ListConfAuthSystems()
{
    return m_Configuration__ListConfAuthSystems;
}
::ecore::EReference_ptr UMS_DataPackage::getConfiguration__ListConfAuthAccounts()
{
    return m_Configuration__ListConfAuthAccounts;
}
::ecore::EAttribute_ptr UMS_DataPackage::getConfiguration__filePath()
{
    return m_Configuration__filePath;
}
::ecore::EAttribute_ptr UMS_DataPackage::getOptionValue__optionName()
{
    return m_OptionValue__optionName;
}
::ecore::EAttribute_ptr UMS_DataPackage::getOptionValue__value()
{
    return m_OptionValue__value;
}
::ecore::EReference_ptr UMS_DataPackage::getListOptionsValues__optionValues()
{
    return m_ListOptionsValues__optionValues;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListOptOptions__listAllDeftValue()
{
    return m_ListOptOptions__listAllDeftValue;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListOptOptions__userId()
{
    return m_ListOptOptions__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListOptOptions__optionName()
{
    return m_ListOptOptions__optionName;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthSystem__authSystemId()
{
    return m_AuthSystem__authSystemId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthSystem__name()
{
    return m_AuthSystem__name;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthSystem__URI()
{
    return m_AuthSystem__URI;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthSystem__authLogin()
{
    return m_AuthSystem__authLogin;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthSystem__authPassword()
{
    return m_AuthSystem__authPassword;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthSystem__userPasswordEncryption()
{
    return m_AuthSystem__userPasswordEncryption;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthSystem__type()
{
    return m_AuthSystem__type;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthSystem__status()
{
    return m_AuthSystem__status;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthSystem__ldapBase()
{
    return m_AuthSystem__ldapBase;
}
::ecore::EReference_ptr UMS_DataPackage::getListAuthSystems__AuthSystems()
{
    return m_ListAuthSystems__AuthSystems;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListAuthSysOptions__listAllAuthSystems()
{
    return m_ListAuthSysOptions__listAllAuthSystems;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListAuthSysOptions__listFullInfo()
{
    return m_ListAuthSysOptions__listFullInfo;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListAuthSysOptions__userId()
{
    return m_ListAuthSysOptions__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListAuthSysOptions__authSystemId()
{
    return m_ListAuthSysOptions__authSystemId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthAccount__authSystemId()
{
    return m_AuthAccount__authSystemId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthAccount__userId()
{
    return m_AuthAccount__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getAuthAccount__acLogin()
{
    return m_AuthAccount__acLogin;
}
::ecore::EReference_ptr UMS_DataPackage::getListAuthAccounts__AuthAccounts()
{
    return m_ListAuthAccounts__AuthAccounts;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListAuthAccOptions__listAll()
{
    return m_ListAuthAccOptions__listAll;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListAuthAccOptions__userId()
{
    return m_ListAuthAccOptions__userId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getListAuthAccOptions__authSystemId()
{
    return m_ListAuthAccOptions__authSystemId;
}
::ecore::EAttribute_ptr UMS_DataPackage::getVersion__major()
{
    return m_Version__major;
}
::ecore::EAttribute_ptr UMS_DataPackage::getVersion__minor()
{
    return m_Version__minor;
}
::ecore::EAttribute_ptr UMS_DataPackage::getVersion__patch()
{
    return m_Version__patch;
}
::ecore::EAttribute_ptr UMS_DataPackage::getVersion__stringformat()
{
    return m_Version__stringformat;
}

