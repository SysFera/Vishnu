// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * UMS_Data/UMS_DataPackage.hpp
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

/**
 * \file UMS_DataPackage.hpp
 * \brief The UMS_DataPackage class
 * \author Generated file
 * \date 31/03/2011
 */

#ifndef _UMS_DATAPACKAGE_HPP
#define _UMS_DATAPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <UMS_Data_forward.hpp>

namespace UMS_Data
{
    /**
     * \class UMS_DataPackage
     * \brief The package class (reflective API) for generated model UMS_Data
     */
    class UMS_DataPackage: public virtual ::ecore::EPackage
    {
    public:

        /**
         * \brief To get the instance of the singleton
         * \return Pointer to the instance
         */
        static UMS_DataPackage_ptr _instance();

        // IDs for classifiers

        /**
         * \brief Constant for AuthAccount class
         */
        static const int AUTHACCOUNT = 0;

        /**
         * \brief Constant for AuthSystem class
         */
        static const int AUTHSYSTEM = 1;

        /**
         * \brief Constant for AuthType class
         */
        static const int AUTHTYPE = 2;

        /**
         * \brief Constant for Command class
         */
        static const int COMMAND = 3;

        /**
         * \brief Constant for CommandStatusType class
         */
        static const int COMMANDSTATUSTYPE = 4;

        /**
         * \brief Constant for ConnectOptions class
         */
        static const int CONNECTOPTIONS = 5;

        /**
         * \brief Constant for EncryptionMethod class
         */
        static const int ENCRYPTIONMETHOD = 6;

        /**
         * \brief Constant for ListAuthAccOptions class
         */
        static const int LISTAUTHACCOPTIONS = 7;

        /**
         * \brief Constant for ListAuthAccounts class
         */
        static const int LISTAUTHACCOUNTS = 8;

        /**
         * \brief Constant for ListAuthSysOptions class
         */
        static const int LISTAUTHSYSOPTIONS = 9;

        /**
         * \brief Constant for ListAuthSystems class
         */
        static const int LISTAUTHSYSTEMS = 10;

        /**
         * \brief Constant for ListCmdOptions class
         */
        static const int LISTCMDOPTIONS = 11;

        /**
         * \brief Constant for ListCommands class
         */
        static const int LISTCOMMANDS = 12;

        /**
         * \brief Constant for ListLocalAccOptions class
         */
        static const int LISTLOCALACCOPTIONS = 13;

        /**
         * \brief Constant for ListLocalAccounts class
         */
        static const int LISTLOCALACCOUNTS = 14;

        /**
         * \brief Constant for ListMachineOptions class
         */
        static const int LISTMACHINEOPTIONS = 15;

        /**
         * \brief Constant for ListMachines class
         */
        static const int LISTMACHINES = 16;

        /**
         * \brief Constant for ListSessionOptions class
         */
        static const int LISTSESSIONOPTIONS = 17;

        /**
         * \brief Constant for ListSessions class
         */
        static const int LISTSESSIONS = 18;

        /**
         * \brief Constant for ListUsers class
         */
        static const int LISTUSERS = 19;

        /**
         * \brief Constant for ListUsersOptions class
         */
        static const int LISTUSERSOPTIONS = 20;

        /**
         * \brief Constant for LocalAccount class
         */
        static const int LOCALACCOUNT = 21;

        /**
         * \brief Constant for Machine class
         */
        static const int MACHINE = 22;

        /**
         * \brief Constant for PrivilegeType class
         */
        static const int PRIVILEGETYPE = 23;

        /**
         * \brief Constant for Session class
         */
        static const int SESSION = 24;

        /**
         * \brief Constant for SessionCloseType class
         */
        static const int SESSIONCLOSETYPE = 25;

        /**
         * \brief Constant for StatusType class
         */
        static const int STATUSTYPE = 26;

        /**
         * \brief Constant for User class
         */
        static const int USER = 27;

        /**
         * \brief Constant for Version class
         */
        static const int VERSION = 28;

        /**
         * \brief Constant for CONNECTOPTIONS__CLOSEPOLICY feature
         */
        static const int CONNECTOPTIONS__CLOSEPOLICY = 0;

        /**
         * \brief Constant for CONNECTOPTIONS__SESSIONINACTIVITYDELAY feature
         */
        static const int CONNECTOPTIONS__SESSIONINACTIVITYDELAY = 1;

        /**
         * \brief Constant for CONNECTOPTIONS__SUBSTITUTEUSERID feature
         */
        static const int CONNECTOPTIONS__SUBSTITUTEUSERID = 2;

        /**
         * \brief Constant for SESSION__SESSIONID feature
         */
        static const int SESSION__SESSIONID = 3;

        /**
         * \brief Constant for SESSION__USERID feature
         */
        static const int SESSION__USERID = 4;

        /**
         * \brief Constant for SESSION__SESSIONKEY feature
         */
        static const int SESSION__SESSIONKEY = 5;

        /**
         * \brief Constant for SESSION__DATELASTCONNECT feature
         */
        static const int SESSION__DATELASTCONNECT = 6;

        /**
         * \brief Constant for SESSION__DATECREATION feature
         */
        static const int SESSION__DATECREATION = 7;

        /**
         * \brief Constant for SESSION__DATECLOSURE feature
         */
        static const int SESSION__DATECLOSURE = 8;

        /**
         * \brief Constant for SESSION__STATUS feature
         */
        static const int SESSION__STATUS = 9;

        /**
         * \brief Constant for SESSION__CLOSEPOLICY feature
         */
        static const int SESSION__CLOSEPOLICY = 10;

        /**
         * \brief Constant for SESSION__TIMEOUT feature
         */
        static const int SESSION__TIMEOUT = 11;

        /**
         * \brief Constant for SESSION__AUTHENID feature
         */
        static const int SESSION__AUTHENID = 12;

        /**
         * \brief Constant for LISTSESSIONS__SESSIONS feature
         */
        static const int LISTSESSIONS__SESSIONS = 13;

        /**
         * \brief Constant for LISTSESSIONOPTIONS__STATUS feature
         */
        static const int LISTSESSIONOPTIONS__STATUS = 14;

        /**
         * \brief Constant for LISTSESSIONOPTIONS__SESSIONCLOSEPOLICY feature
         */
        static const int LISTSESSIONOPTIONS__SESSIONCLOSEPOLICY = 15;

        /**
         * \brief Constant for LISTSESSIONOPTIONS__SESSIONINACTIVITYDELAY feature
         */
        static const int LISTSESSIONOPTIONS__SESSIONINACTIVITYDELAY = 16;

        /**
         * \brief Constant for LISTSESSIONOPTIONS__MACHINEID feature
         */
        static const int LISTSESSIONOPTIONS__MACHINEID = 17;

        /**
         * \brief Constant for LISTSESSIONOPTIONS__ADMINLISTOPTION feature
         */
        static const int LISTSESSIONOPTIONS__ADMINLISTOPTION = 18;

        /**
         * \brief Constant for LISTSESSIONOPTIONS__USERID feature
         */
        static const int LISTSESSIONOPTIONS__USERID = 19;

        /**
         * \brief Constant for LISTSESSIONOPTIONS__SESSIONID feature
         */
        static const int LISTSESSIONOPTIONS__SESSIONID = 20;

        /**
         * \brief Constant for LISTSESSIONOPTIONS__STARTDATEOPTION feature
         */
        static const int LISTSESSIONOPTIONS__STARTDATEOPTION = 21;

        /**
         * \brief Constant for LISTSESSIONOPTIONS__ENDDATEOPTION feature
         */
        static const int LISTSESSIONOPTIONS__ENDDATEOPTION = 22;

        /**
         * \brief Constant for USER__USERID feature
         */
        static const int USER__USERID = 23;

        /**
         * \brief Constant for USER__PASSWORD feature
         */
        static const int USER__PASSWORD = 24;

        /**
         * \brief Constant for USER__FIRSTNAME feature
         */
        static const int USER__FIRSTNAME = 25;

        /**
         * \brief Constant for USER__LASTNAME feature
         */
        static const int USER__LASTNAME = 26;

        /**
         * \brief Constant for USER__PRIVILEGE feature
         */
        static const int USER__PRIVILEGE = 27;

        /**
         * \brief Constant for USER__EMAIL feature
         */
        static const int USER__EMAIL = 28;

        /**
         * \brief Constant for USER__STATUS feature
         */
        static const int USER__STATUS = 29;

        /**
         * \brief Constant for LISTUSERS__USERS feature
         */
        static const int LISTUSERS__USERS = 30;

        /**
         * \brief Constant for LISTUSERSOPTIONS__USERID feature
         */
        static const int LISTUSERSOPTIONS__USERID = 31;

        /**
         * \brief Constant for LISTUSERSOPTIONS__AUTHSYSTEMID feature
         */
        static const int LISTUSERSOPTIONS__AUTHSYSTEMID = 32;

        /**
         * \brief Constant for COMMAND__COMMANDID feature
         */
        static const int COMMAND__COMMANDID = 33;

        /**
         * \brief Constant for COMMAND__SESSIONID feature
         */
        static const int COMMAND__SESSIONID = 34;

        /**
         * \brief Constant for COMMAND__MACHINEID feature
         */
        static const int COMMAND__MACHINEID = 35;

        /**
         * \brief Constant for COMMAND__CMDDESCRIPTION feature
         */
        static const int COMMAND__CMDDESCRIPTION = 36;

        /**
         * \brief Constant for COMMAND__CMDSTARTTIME feature
         */
        static const int COMMAND__CMDSTARTTIME = 37;

        /**
         * \brief Constant for COMMAND__CMDENDTIME feature
         */
        static const int COMMAND__CMDENDTIME = 38;

        /**
         * \brief Constant for COMMAND__STATUS feature
         */
        static const int COMMAND__STATUS = 39;

        /**
         * \brief Constant for LISTCOMMANDS__COMMANDS feature
         */
        static const int LISTCOMMANDS__COMMANDS = 40;

        /**
         * \brief Constant for LISTCMDOPTIONS__ADMINLISTOPTION feature
         */
        static const int LISTCMDOPTIONS__ADMINLISTOPTION = 41;

        /**
         * \brief Constant for LISTCMDOPTIONS__USERID feature
         */
        static const int LISTCMDOPTIONS__USERID = 42;

        /**
         * \brief Constant for LISTCMDOPTIONS__SESSIONID feature
         */
        static const int LISTCMDOPTIONS__SESSIONID = 43;

        /**
         * \brief Constant for LISTCMDOPTIONS__STARTDATEOPTION feature
         */
        static const int LISTCMDOPTIONS__STARTDATEOPTION = 44;

        /**
         * \brief Constant for LISTCMDOPTIONS__ENDDATEOPTION feature
         */
        static const int LISTCMDOPTIONS__ENDDATEOPTION = 45;

        /**
         * \brief Constant for LOCALACCOUNT__USERID feature
         */
        static const int LOCALACCOUNT__USERID = 46;

        /**
         * \brief Constant for LOCALACCOUNT__MACHINEID feature
         */
        static const int LOCALACCOUNT__MACHINEID = 47;

        /**
         * \brief Constant for LOCALACCOUNT__ACLOGIN feature
         */
        static const int LOCALACCOUNT__ACLOGIN = 48;

        /**
         * \brief Constant for LOCALACCOUNT__SSHKEYPATH feature
         */
        static const int LOCALACCOUNT__SSHKEYPATH = 49;

        /**
         * \brief Constant for LOCALACCOUNT__HOMEDIRECTORY feature
         */
        static const int LOCALACCOUNT__HOMEDIRECTORY = 50;

        /**
         * \brief Constant for LISTLOCALACCOUNTS__ACCOUNTS feature
         */
        static const int LISTLOCALACCOUNTS__ACCOUNTS = 51;

        /**
         * \brief Constant for LISTLOCALACCOPTIONS__ADMINLISTOPTION feature
         */
        static const int LISTLOCALACCOPTIONS__ADMINLISTOPTION = 52;

        /**
         * \brief Constant for LISTLOCALACCOPTIONS__USERID feature
         */
        static const int LISTLOCALACCOPTIONS__USERID = 53;

        /**
         * \brief Constant for LISTLOCALACCOPTIONS__MACHINEID feature
         */
        static const int LISTLOCALACCOPTIONS__MACHINEID = 54;

        /**
         * \brief Constant for MACHINE__MACHINEID feature
         */
        static const int MACHINE__MACHINEID = 55;

        /**
         * \brief Constant for MACHINE__ADDRESS feature
         */
        static const int MACHINE__ADDRESS = 56;

        /**
         * \brief Constant for MACHINE__DESCRIPTION feature
         */
        static const int MACHINE__DESCRIPTION = 57;

        /**
         * \brief Constant for MACHINE__STATUS feature
         */
        static const int MACHINE__STATUS = 58;

        /**
         * \brief Constant for LISTMACHINES__MACHINES feature
         */
        static const int LISTMACHINES__MACHINES = 59;

        /**
         * \brief Constant for LISTMACHINEOPTIONS__USERID feature
         */
        static const int LISTMACHINEOPTIONS__USERID = 60;

        /**
         * \brief Constant for LISTMACHINEOPTIONS__LISTALLMACHINE feature
         */
        static const int LISTMACHINEOPTIONS__LISTALLMACHINE = 61;

        /**
         * \brief Constant for LISTMACHINEOPTIONS__MACHINEID feature
         */
        static const int LISTMACHINEOPTIONS__MACHINEID = 62;

        /**
         * \brief Constant for AUTHSYSTEM__AUTHSYSTEMID feature
         */
        static const int AUTHSYSTEM__AUTHSYSTEMID = 63;

        /**
         * \brief Constant for AUTHSYSTEM__NAME feature
         */
        static const int AUTHSYSTEM__NAME = 64;

        /**
         * \brief Constant for AUTHSYSTEM__URI feature
         */
        static const int AUTHSYSTEM__URI = 65;

        /**
         * \brief Constant for AUTHSYSTEM__AUTHLOGIN feature
         */
        static const int AUTHSYSTEM__AUTHLOGIN = 66;

        /**
         * \brief Constant for AUTHSYSTEM__AUTHPASSWORD feature
         */
        static const int AUTHSYSTEM__AUTHPASSWORD = 67;

        /**
         * \brief Constant for AUTHSYSTEM__USERPASSWORDENCRYPTION feature
         */
        static const int AUTHSYSTEM__USERPASSWORDENCRYPTION = 68;

        /**
         * \brief Constant for AUTHSYSTEM__TYPE feature
         */
        static const int AUTHSYSTEM__TYPE = 69;

        /**
         * \brief Constant for AUTHSYSTEM__STATUS feature
         */
        static const int AUTHSYSTEM__STATUS = 70;

        /**
         * \brief Constant for AUTHSYSTEM__LDAPBASE feature
         */
        static const int AUTHSYSTEM__LDAPBASE = 71;

        /**
         * \brief Constant for LISTAUTHSYSTEMS__AUTHSYSTEMS feature
         */
        static const int LISTAUTHSYSTEMS__AUTHSYSTEMS = 72;

        /**
         * \brief Constant for LISTAUTHSYSOPTIONS__LISTALLAUTHSYSTEMS feature
         */
        static const int LISTAUTHSYSOPTIONS__LISTALLAUTHSYSTEMS = 73;

        /**
         * \brief Constant for LISTAUTHSYSOPTIONS__LISTFULLINFO feature
         */
        static const int LISTAUTHSYSOPTIONS__LISTFULLINFO = 74;

        /**
         * \brief Constant for LISTAUTHSYSOPTIONS__USERID feature
         */
        static const int LISTAUTHSYSOPTIONS__USERID = 75;

        /**
         * \brief Constant for LISTAUTHSYSOPTIONS__AUTHSYSTEMID feature
         */
        static const int LISTAUTHSYSOPTIONS__AUTHSYSTEMID = 76;

        /**
         * \brief Constant for AUTHACCOUNT__AUTHSYSTEMID feature
         */
        static const int AUTHACCOUNT__AUTHSYSTEMID = 77;

        /**
         * \brief Constant for AUTHACCOUNT__USERID feature
         */
        static const int AUTHACCOUNT__USERID = 78;

        /**
         * \brief Constant for AUTHACCOUNT__ACLOGIN feature
         */
        static const int AUTHACCOUNT__ACLOGIN = 79;

        /**
         * \brief Constant for LISTAUTHACCOUNTS__AUTHACCOUNTS feature
         */
        static const int LISTAUTHACCOUNTS__AUTHACCOUNTS = 80;

        /**
         * \brief Constant for LISTAUTHACCOPTIONS__LISTALL feature
         */
        static const int LISTAUTHACCOPTIONS__LISTALL = 81;

        /**
         * \brief Constant for LISTAUTHACCOPTIONS__USERID feature
         */
        static const int LISTAUTHACCOPTIONS__USERID = 82;

        /**
         * \brief Constant for LISTAUTHACCOPTIONS__AUTHSYSTEMID feature
         */
        static const int LISTAUTHACCOPTIONS__AUTHSYSTEMID = 83;

        /**
         * \brief Constant for VERSION__MAJOR feature
         */
        static const int VERSION__MAJOR = 84;

        /**
         * \brief Constant for VERSION__MINOR feature
         */
        static const int VERSION__MINOR = 85;

        /**
         * \brief Constant for VERSION__PATCH feature
         */
        static const int VERSION__PATCH = 86;

        /**
         * \brief Constant for VERSION__STRINGFORMAT feature
         */
        static const int VERSION__STRINGFORMAT = 87;

        // EClassifiers methods

        /**
         * \brief Returns the reflective object for class ConnectOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getConnectOptions();

        /**
         * \brief Returns the reflective object for class Session
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getSession();

        /**
         * \brief Returns the reflective object for class ListSessions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListSessions();

        /**
         * \brief Returns the reflective object for class ListSessionOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListSessionOptions();

        /**
         * \brief Returns the reflective object for class User
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getUser();

        /**
         * \brief Returns the reflective object for class ListUsers
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListUsers();

        /**
         * \brief Returns the reflective object for class ListUsersOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListUsersOptions();

        /**
         * \brief Returns the reflective object for class Command
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getCommand();

        /**
         * \brief Returns the reflective object for class ListCommands
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListCommands();

        /**
         * \brief Returns the reflective object for class ListCmdOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListCmdOptions();

        /**
         * \brief Returns the reflective object for class LocalAccount
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getLocalAccount();

        /**
         * \brief Returns the reflective object for class ListLocalAccounts
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListLocalAccounts();

        /**
         * \brief Returns the reflective object for class ListLocalAccOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListLocalAccOptions();

        /**
         * \brief Returns the reflective object for class Machine
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getMachine();

        /**
         * \brief Returns the reflective object for class ListMachines
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListMachines();

        /**
         * \brief Returns the reflective object for class ListMachineOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListMachineOptions();

        /**
         * \brief Returns the reflective object for class SessionCloseType
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getSessionCloseType();

        /**
         * \brief Returns the reflective object for class PrivilegeType
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getPrivilegeType();

        /**
         * \brief Returns the reflective object for class StatusType
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getStatusType();

        /**
         * \brief Returns the reflective object for class CommandStatusType
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getCommandStatusType();

        /**
         * \brief Returns the reflective object for class AuthSystem
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getAuthSystem();

        /**
         * \brief Returns the reflective object for class ListAuthSystems
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListAuthSystems();

        /**
         * \brief Returns the reflective object for class ListAuthSysOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListAuthSysOptions();

        /**
         * \brief Returns the reflective object for class AuthType
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getAuthType();

        /**
         * \brief Returns the reflective object for class AuthAccount
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getAuthAccount();

        /**
         * \brief Returns the reflective object for class EncryptionMethod
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getEncryptionMethod();

        /**
         * \brief Returns the reflective object for class ListAuthAccounts
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListAuthAccounts();

        /**
         * \brief Returns the reflective object for class ListAuthAccOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getListAuthAccOptions();

        /**
         * \brief Returns the reflective object for class Version
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getVersion();

        // EStructuralFeatures methods

        /**
         * \brief Returns the reflective object for feature closePolicy of class ConnectOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getConnectOptions__closePolicy();

        /**
         * \brief Returns the reflective object for feature sessionInactivityDelay of class ConnectOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr
                getConnectOptions__sessionInactivityDelay();

        /**
         * \brief Returns the reflective object for feature substituteUserId of class ConnectOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getConnectOptions__substituteUserId();

        /**
         * \brief Returns the reflective object for feature sessionId of class Session
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSession__sessionId();

        /**
         * \brief Returns the reflective object for feature userId of class Session
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSession__userId();

        /**
         * \brief Returns the reflective object for feature sessionKey of class Session
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSession__sessionKey();

        /**
         * \brief Returns the reflective object for feature dateLastConnect of class Session
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSession__dateLastConnect();

        /**
         * \brief Returns the reflective object for feature dateCreation of class Session
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSession__dateCreation();

        /**
         * \brief Returns the reflective object for feature dateClosure of class Session
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSession__dateClosure();

        /**
         * \brief Returns the reflective object for feature status of class Session
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSession__status();

        /**
         * \brief Returns the reflective object for feature closePolicy of class Session
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSession__closePolicy();

        /**
         * \brief Returns the reflective object for feature timeout of class Session
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSession__timeout();

        /**
         * \brief Returns the reflective object for feature authenId of class Session
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getSession__authenId();

        /**
         * \brief Returns the reflective object for feature sessions of class ListSessions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getListSessions__sessions();

        /**
         * \brief Returns the reflective object for feature status of class ListSessionOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListSessionOptions__status();

        /**
         * \brief Returns the reflective object for feature sessionClosePolicy of class ListSessionOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr
                getListSessionOptions__sessionClosePolicy();

        /**
         * \brief Returns the reflective object for feature sessionInactivityDelay of class ListSessionOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr
                getListSessionOptions__sessionInactivityDelay();

        /**
         * \brief Returns the reflective object for feature machineId of class ListSessionOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListSessionOptions__machineId();

        /**
         * \brief Returns the reflective object for feature adminListOption of class ListSessionOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr
                getListSessionOptions__adminListOption();

        /**
         * \brief Returns the reflective object for feature userId of class ListSessionOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListSessionOptions__userId();

        /**
         * \brief Returns the reflective object for feature sessionId of class ListSessionOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListSessionOptions__sessionId();

        /**
         * \brief Returns the reflective object for feature startDateOption of class ListSessionOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr
                getListSessionOptions__startDateOption();

        /**
         * \brief Returns the reflective object for feature endDateOption of class ListSessionOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListSessionOptions__endDateOption();

        /**
         * \brief Returns the reflective object for feature userId of class User
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getUser__userId();

        /**
         * \brief Returns the reflective object for feature password of class User
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getUser__password();

        /**
         * \brief Returns the reflective object for feature firstname of class User
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getUser__firstname();

        /**
         * \brief Returns the reflective object for feature lastname of class User
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getUser__lastname();

        /**
         * \brief Returns the reflective object for feature privilege of class User
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getUser__privilege();

        /**
         * \brief Returns the reflective object for feature email of class User
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getUser__email();

        /**
         * \brief Returns the reflective object for feature status of class User
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getUser__status();

        /**
         * \brief Returns the reflective object for feature users of class ListUsers
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getListUsers__users();

        /**
         * \brief Returns the reflective object for feature userId of class ListUsersOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListUsersOptions__userId();

        /**
         * \brief Returns the reflective object for feature authSystemId of class ListUsersOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListUsersOptions__authSystemId();

        /**
         * \brief Returns the reflective object for feature commandId of class Command
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCommand__commandId();

        /**
         * \brief Returns the reflective object for feature sessionId of class Command
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCommand__sessionId();

        /**
         * \brief Returns the reflective object for feature machineId of class Command
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCommand__machineId();

        /**
         * \brief Returns the reflective object for feature cmdDescription of class Command
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCommand__cmdDescription();

        /**
         * \brief Returns the reflective object for feature cmdStartTime of class Command
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCommand__cmdStartTime();

        /**
         * \brief Returns the reflective object for feature cmdEndTime of class Command
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCommand__cmdEndTime();

        /**
         * \brief Returns the reflective object for feature status of class Command
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCommand__status();

        /**
         * \brief Returns the reflective object for feature Commands of class ListCommands
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getListCommands__Commands();

        /**
         * \brief Returns the reflective object for feature adminListOption of class ListCmdOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListCmdOptions__adminListOption();

        /**
         * \brief Returns the reflective object for feature userId of class ListCmdOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListCmdOptions__userId();

        /**
         * \brief Returns the reflective object for feature sessionId of class ListCmdOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListCmdOptions__sessionId();

        /**
         * \brief Returns the reflective object for feature startDateOption of class ListCmdOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListCmdOptions__startDateOption();

        /**
         * \brief Returns the reflective object for feature endDateOption of class ListCmdOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListCmdOptions__endDateOption();

        /**
         * \brief Returns the reflective object for feature userId of class LocalAccount
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLocalAccount__userId();

        /**
         * \brief Returns the reflective object for feature machineId of class LocalAccount
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLocalAccount__machineId();

        /**
         * \brief Returns the reflective object for feature acLogin of class LocalAccount
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLocalAccount__acLogin();

        /**
         * \brief Returns the reflective object for feature sshKeyPath of class LocalAccount
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLocalAccount__sshKeyPath();

        /**
         * \brief Returns the reflective object for feature homeDirectory of class LocalAccount
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLocalAccount__homeDirectory();

        /**
         * \brief Returns the reflective object for feature accounts of class ListLocalAccounts
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getListLocalAccounts__accounts();

        /**
         * \brief Returns the reflective object for feature adminListOption of class ListLocalAccOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr
                getListLocalAccOptions__adminListOption();

        /**
         * \brief Returns the reflective object for feature userId of class ListLocalAccOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListLocalAccOptions__userId();

        /**
         * \brief Returns the reflective object for feature machineId of class ListLocalAccOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListLocalAccOptions__machineId();

        /**
         * \brief Returns the reflective object for feature machineId of class Machine
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getMachine__machineId();

        /**
         * \brief Returns the reflective object for feature address of class Machine
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getMachine__address();

        /**
         * \brief Returns the reflective object for feature description of class Machine
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getMachine__description();

        /**
         * \brief Returns the reflective object for feature status of class Machine
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getMachine__status();

        /**
         * \brief Returns the reflective object for feature machines of class ListMachines
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getListMachines__machines();

        /**
         * \brief Returns the reflective object for feature userId of class ListMachineOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListMachineOptions__userId();

        /**
         * \brief Returns the reflective object for feature listAllMachine of class ListMachineOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListMachineOptions__listAllMachine();

        /**
         * \brief Returns the reflective object for feature machineId of class ListMachineOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListMachineOptions__machineId();

        /**
         * \brief Returns the reflective object for feature authSystemId of class AuthSystem
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthSystem__authSystemId();

        /**
         * \brief Returns the reflective object for feature name of class AuthSystem
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthSystem__name();

        /**
         * \brief Returns the reflective object for feature URI of class AuthSystem
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthSystem__URI();

        /**
         * \brief Returns the reflective object for feature authLogin of class AuthSystem
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthSystem__authLogin();

        /**
         * \brief Returns the reflective object for feature authPassword of class AuthSystem
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthSystem__authPassword();

        /**
         * \brief Returns the reflective object for feature userPasswordEncryption of class AuthSystem
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthSystem__userPasswordEncryption();

        /**
         * \brief Returns the reflective object for feature type of class AuthSystem
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthSystem__type();

        /**
         * \brief Returns the reflective object for feature status of class AuthSystem
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthSystem__status();

        /**
         * \brief Returns the reflective object for feature ldapBase of class AuthSystem
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthSystem__ldapBase();

        /**
         * \brief Returns the reflective object for feature AuthSystems of class ListAuthSystems
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getListAuthSystems__AuthSystems();

        /**
         * \brief Returns the reflective object for feature listAllAuthSystems of class ListAuthSysOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr
                getListAuthSysOptions__listAllAuthSystems();

        /**
         * \brief Returns the reflective object for feature listFullInfo of class ListAuthSysOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListAuthSysOptions__listFullInfo();

        /**
         * \brief Returns the reflective object for feature userId of class ListAuthSysOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListAuthSysOptions__userId();

        /**
         * \brief Returns the reflective object for feature authSystemId of class ListAuthSysOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListAuthSysOptions__authSystemId();

        /**
         * \brief Returns the reflective object for feature authSystemId of class AuthAccount
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthAccount__authSystemId();

        /**
         * \brief Returns the reflective object for feature userId of class AuthAccount
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthAccount__userId();

        /**
         * \brief Returns the reflective object for feature acLogin of class AuthAccount
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getAuthAccount__acLogin();

        /**
         * \brief Returns the reflective object for feature AuthAccounts of class ListAuthAccounts
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getListAuthAccounts__AuthAccounts();

        /**
         * \brief Returns the reflective object for feature listAll of class ListAuthAccOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListAuthAccOptions__listAll();

        /**
         * \brief Returns the reflective object for feature userId of class ListAuthAccOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListAuthAccOptions__userId();

        /**
         * \brief Returns the reflective object for feature authSystemId of class ListAuthAccOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getListAuthAccOptions__authSystemId();

        /**
         * \brief Returns the reflective object for feature major of class Version
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getVersion__major();

        /**
         * \brief Returns the reflective object for feature minor of class Version
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getVersion__minor();

        /**
         * \brief Returns the reflective object for feature patch of class Version
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getVersion__patch();

        /**
         * \brief Returns the reflective object for feature stringformat of class Version
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getVersion__stringformat();

    protected:

        /**
         * \brief The instance of the package
         */
        static std::auto_ptr< UMS_DataPackage > s_instance;

        UMS_DataPackage();

        // EClass instances 

        /**
         * \brief The instance for the class ConnectOptions
         */
        ::ecore::EClass_ptr m_ConnectOptionsEClass;

        /**
         * \brief The instance for the class Session
         */
        ::ecore::EClass_ptr m_SessionEClass;

        /**
         * \brief The instance for the class ListSessions
         */
        ::ecore::EClass_ptr m_ListSessionsEClass;

        /**
         * \brief The instance for the class ListSessionOptions
         */
        ::ecore::EClass_ptr m_ListSessionOptionsEClass;

        /**
         * \brief The instance for the class User
         */
        ::ecore::EClass_ptr m_UserEClass;

        /**
         * \brief The instance for the class ListUsers
         */
        ::ecore::EClass_ptr m_ListUsersEClass;

        /**
         * \brief The instance for the class ListUsersOptions
         */
        ::ecore::EClass_ptr m_ListUsersOptionsEClass;

        /**
         * \brief The instance for the class Command
         */
        ::ecore::EClass_ptr m_CommandEClass;

        /**
         * \brief The instance for the class ListCommands
         */
        ::ecore::EClass_ptr m_ListCommandsEClass;

        /**
         * \brief The instance for the class ListCmdOptions
         */
        ::ecore::EClass_ptr m_ListCmdOptionsEClass;

        /**
         * \brief The instance for the class LocalAccount
         */
        ::ecore::EClass_ptr m_LocalAccountEClass;

        /**
         * \brief The instance for the class ListLocalAccounts
         */
        ::ecore::EClass_ptr m_ListLocalAccountsEClass;

        /**
         * \brief The instance for the class ListLocalAccOptions
         */
        ::ecore::EClass_ptr m_ListLocalAccOptionsEClass;

        /**
         * \brief The instance for the class Machine
         */
        ::ecore::EClass_ptr m_MachineEClass;

        /**
         * \brief The instance for the class ListMachines
         */
        ::ecore::EClass_ptr m_ListMachinesEClass;

        /**
         * \brief The instance for the class ListMachineOptions
         */
        ::ecore::EClass_ptr m_ListMachineOptionsEClass;

        /**
         * \brief The instance for the class AuthSystem
         */
        ::ecore::EClass_ptr m_AuthSystemEClass;

        /**
         * \brief The instance for the class ListAuthSystems
         */
        ::ecore::EClass_ptr m_ListAuthSystemsEClass;

        /**
         * \brief The instance for the class ListAuthSysOptions
         */
        ::ecore::EClass_ptr m_ListAuthSysOptionsEClass;

        /**
         * \brief The instance for the class AuthAccount
         */
        ::ecore::EClass_ptr m_AuthAccountEClass;

        /**
         * \brief The instance for the class ListAuthAccounts
         */
        ::ecore::EClass_ptr m_ListAuthAccountsEClass;

        /**
         * \brief The instance for the class ListAuthAccOptions
         */
        ::ecore::EClass_ptr m_ListAuthAccOptionsEClass;

        /**
         * \brief The instance for the class Version
         */
        ::ecore::EClass_ptr m_VersionEClass;

        // EEnuminstances 

        /**
         * \brief The instance for the enum SessionCloseType
         */
        ::ecore::EEnum_ptr m_SessionCloseTypeEEnum;

        /**
         * \brief The instance for the enum PrivilegeType
         */
        ::ecore::EEnum_ptr m_PrivilegeTypeEEnum;

        /**
         * \brief The instance for the enum StatusType
         */
        ::ecore::EEnum_ptr m_StatusTypeEEnum;

        /**
         * \brief The instance for the enum CommandStatusType
         */
        ::ecore::EEnum_ptr m_CommandStatusTypeEEnum;

        /**
         * \brief The instance for the enum AuthType
         */
        ::ecore::EEnum_ptr m_AuthTypeEEnum;

        /**
         * \brief The instance for the enum EncryptionMethod
         */
        ::ecore::EEnum_ptr m_EncryptionMethodEEnum;

        // EDataType instances 


        // EStructuralFeatures instances

        /**
         * \brief The instance for the feature closePolicy of class ConnectOptions
         */
        ::ecore::EAttribute_ptr m_ConnectOptions__closePolicy;

        /**
         * \brief The instance for the feature sessionInactivityDelay of class ConnectOptions
         */
        ::ecore::EAttribute_ptr m_ConnectOptions__sessionInactivityDelay;

        /**
         * \brief The instance for the feature substituteUserId of class ConnectOptions
         */
        ::ecore::EAttribute_ptr m_ConnectOptions__substituteUserId;

        /**
         * \brief The instance for the feature sessionId of class Session
         */
        ::ecore::EAttribute_ptr m_Session__sessionId;

        /**
         * \brief The instance for the feature userId of class Session
         */
        ::ecore::EAttribute_ptr m_Session__userId;

        /**
         * \brief The instance for the feature sessionKey of class Session
         */
        ::ecore::EAttribute_ptr m_Session__sessionKey;

        /**
         * \brief The instance for the feature dateLastConnect of class Session
         */
        ::ecore::EAttribute_ptr m_Session__dateLastConnect;

        /**
         * \brief The instance for the feature dateCreation of class Session
         */
        ::ecore::EAttribute_ptr m_Session__dateCreation;

        /**
         * \brief The instance for the feature dateClosure of class Session
         */
        ::ecore::EAttribute_ptr m_Session__dateClosure;

        /**
         * \brief The instance for the feature status of class Session
         */
        ::ecore::EAttribute_ptr m_Session__status;

        /**
         * \brief The instance for the feature closePolicy of class Session
         */
        ::ecore::EAttribute_ptr m_Session__closePolicy;

        /**
         * \brief The instance for the feature timeout of class Session
         */
        ::ecore::EAttribute_ptr m_Session__timeout;

        /**
         * \brief The instance for the feature authenId of class Session
         */
        ::ecore::EAttribute_ptr m_Session__authenId;

        /**
         * \brief The instance for the feature sessions of class ListSessions
         */
        ::ecore::EReference_ptr m_ListSessions__sessions;

        /**
         * \brief The instance for the feature status of class ListSessionOptions
         */
        ::ecore::EAttribute_ptr m_ListSessionOptions__status;

        /**
         * \brief The instance for the feature sessionClosePolicy of class ListSessionOptions
         */
        ::ecore::EAttribute_ptr m_ListSessionOptions__sessionClosePolicy;

        /**
         * \brief The instance for the feature sessionInactivityDelay of class ListSessionOptions
         */
        ::ecore::EAttribute_ptr m_ListSessionOptions__sessionInactivityDelay;

        /**
         * \brief The instance for the feature machineId of class ListSessionOptions
         */
        ::ecore::EAttribute_ptr m_ListSessionOptions__machineId;

        /**
         * \brief The instance for the feature adminListOption of class ListSessionOptions
         */
        ::ecore::EAttribute_ptr m_ListSessionOptions__adminListOption;

        /**
         * \brief The instance for the feature userId of class ListSessionOptions
         */
        ::ecore::EAttribute_ptr m_ListSessionOptions__userId;

        /**
         * \brief The instance for the feature sessionId of class ListSessionOptions
         */
        ::ecore::EAttribute_ptr m_ListSessionOptions__sessionId;

        /**
         * \brief The instance for the feature startDateOption of class ListSessionOptions
         */
        ::ecore::EAttribute_ptr m_ListSessionOptions__startDateOption;

        /**
         * \brief The instance for the feature endDateOption of class ListSessionOptions
         */
        ::ecore::EAttribute_ptr m_ListSessionOptions__endDateOption;

        /**
         * \brief The instance for the feature userId of class User
         */
        ::ecore::EAttribute_ptr m_User__userId;

        /**
         * \brief The instance for the feature password of class User
         */
        ::ecore::EAttribute_ptr m_User__password;

        /**
         * \brief The instance for the feature firstname of class User
         */
        ::ecore::EAttribute_ptr m_User__firstname;

        /**
         * \brief The instance for the feature lastname of class User
         */
        ::ecore::EAttribute_ptr m_User__lastname;

        /**
         * \brief The instance for the feature privilege of class User
         */
        ::ecore::EAttribute_ptr m_User__privilege;

        /**
         * \brief The instance for the feature email of class User
         */
        ::ecore::EAttribute_ptr m_User__email;

        /**
         * \brief The instance for the feature status of class User
         */
        ::ecore::EAttribute_ptr m_User__status;

        /**
         * \brief The instance for the feature users of class ListUsers
         */
        ::ecore::EReference_ptr m_ListUsers__users;

        /**
         * \brief The instance for the feature userId of class ListUsersOptions
         */
        ::ecore::EAttribute_ptr m_ListUsersOptions__userId;

        /**
         * \brief The instance for the feature authSystemId of class ListUsersOptions
         */
        ::ecore::EAttribute_ptr m_ListUsersOptions__authSystemId;

        /**
         * \brief The instance for the feature commandId of class Command
         */
        ::ecore::EAttribute_ptr m_Command__commandId;

        /**
         * \brief The instance for the feature sessionId of class Command
         */
        ::ecore::EAttribute_ptr m_Command__sessionId;

        /**
         * \brief The instance for the feature machineId of class Command
         */
        ::ecore::EAttribute_ptr m_Command__machineId;

        /**
         * \brief The instance for the feature cmdDescription of class Command
         */
        ::ecore::EAttribute_ptr m_Command__cmdDescription;

        /**
         * \brief The instance for the feature cmdStartTime of class Command
         */
        ::ecore::EAttribute_ptr m_Command__cmdStartTime;

        /**
         * \brief The instance for the feature cmdEndTime of class Command
         */
        ::ecore::EAttribute_ptr m_Command__cmdEndTime;

        /**
         * \brief The instance for the feature status of class Command
         */
        ::ecore::EAttribute_ptr m_Command__status;

        /**
         * \brief The instance for the feature Commands of class ListCommands
         */
        ::ecore::EReference_ptr m_ListCommands__Commands;

        /**
         * \brief The instance for the feature adminListOption of class ListCmdOptions
         */
        ::ecore::EAttribute_ptr m_ListCmdOptions__adminListOption;

        /**
         * \brief The instance for the feature userId of class ListCmdOptions
         */
        ::ecore::EAttribute_ptr m_ListCmdOptions__userId;

        /**
         * \brief The instance for the feature sessionId of class ListCmdOptions
         */
        ::ecore::EAttribute_ptr m_ListCmdOptions__sessionId;

        /**
         * \brief The instance for the feature startDateOption of class ListCmdOptions
         */
        ::ecore::EAttribute_ptr m_ListCmdOptions__startDateOption;

        /**
         * \brief The instance for the feature endDateOption of class ListCmdOptions
         */
        ::ecore::EAttribute_ptr m_ListCmdOptions__endDateOption;

        /**
         * \brief The instance for the feature userId of class LocalAccount
         */
        ::ecore::EAttribute_ptr m_LocalAccount__userId;

        /**
         * \brief The instance for the feature machineId of class LocalAccount
         */
        ::ecore::EAttribute_ptr m_LocalAccount__machineId;

        /**
         * \brief The instance for the feature acLogin of class LocalAccount
         */
        ::ecore::EAttribute_ptr m_LocalAccount__acLogin;

        /**
         * \brief The instance for the feature sshKeyPath of class LocalAccount
         */
        ::ecore::EAttribute_ptr m_LocalAccount__sshKeyPath;

        /**
         * \brief The instance for the feature homeDirectory of class LocalAccount
         */
        ::ecore::EAttribute_ptr m_LocalAccount__homeDirectory;

        /**
         * \brief The instance for the feature accounts of class ListLocalAccounts
         */
        ::ecore::EReference_ptr m_ListLocalAccounts__accounts;

        /**
         * \brief The instance for the feature adminListOption of class ListLocalAccOptions
         */
        ::ecore::EAttribute_ptr m_ListLocalAccOptions__adminListOption;

        /**
         * \brief The instance for the feature userId of class ListLocalAccOptions
         */
        ::ecore::EAttribute_ptr m_ListLocalAccOptions__userId;

        /**
         * \brief The instance for the feature machineId of class ListLocalAccOptions
         */
        ::ecore::EAttribute_ptr m_ListLocalAccOptions__machineId;

        /**
         * \brief The instance for the feature machineId of class Machine
         */
        ::ecore::EAttribute_ptr m_Machine__machineId;

        /**
         * \brief The instance for the feature address of class Machine
         */
        ::ecore::EAttribute_ptr m_Machine__address;

        /**
         * \brief The instance for the feature description of class Machine
         */
        ::ecore::EAttribute_ptr m_Machine__description;

        /**
         * \brief The instance for the feature status of class Machine
         */
        ::ecore::EAttribute_ptr m_Machine__status;

        /**
         * \brief The instance for the feature machines of class ListMachines
         */
        ::ecore::EReference_ptr m_ListMachines__machines;

        /**
         * \brief The instance for the feature userId of class ListMachineOptions
         */
        ::ecore::EAttribute_ptr m_ListMachineOptions__userId;

        /**
         * \brief The instance for the feature listAllMachine of class ListMachineOptions
         */
        ::ecore::EAttribute_ptr m_ListMachineOptions__listAllMachine;

        /**
         * \brief The instance for the feature machineId of class ListMachineOptions
         */
        ::ecore::EAttribute_ptr m_ListMachineOptions__machineId;

        /**
         * \brief The instance for the feature authSystemId of class AuthSystem
         */
        ::ecore::EAttribute_ptr m_AuthSystem__authSystemId;

        /**
         * \brief The instance for the feature name of class AuthSystem
         */
        ::ecore::EAttribute_ptr m_AuthSystem__name;

        /**
         * \brief The instance for the feature URI of class AuthSystem
         */
        ::ecore::EAttribute_ptr m_AuthSystem__URI;

        /**
         * \brief The instance for the feature authLogin of class AuthSystem
         */
        ::ecore::EAttribute_ptr m_AuthSystem__authLogin;

        /**
         * \brief The instance for the feature authPassword of class AuthSystem
         */
        ::ecore::EAttribute_ptr m_AuthSystem__authPassword;

        /**
         * \brief The instance for the feature userPasswordEncryption of class AuthSystem
         */
        ::ecore::EAttribute_ptr m_AuthSystem__userPasswordEncryption;

        /**
         * \brief The instance for the feature type of class AuthSystem
         */
        ::ecore::EAttribute_ptr m_AuthSystem__type;

        /**
         * \brief The instance for the feature status of class AuthSystem
         */
        ::ecore::EAttribute_ptr m_AuthSystem__status;

        /**
         * \brief The instance for the feature ldapBase of class AuthSystem
         */
        ::ecore::EAttribute_ptr m_AuthSystem__ldapBase;

        /**
         * \brief The instance for the feature AuthSystems of class ListAuthSystems
         */
        ::ecore::EReference_ptr m_ListAuthSystems__AuthSystems;

        /**
         * \brief The instance for the feature listAllAuthSystems of class ListAuthSysOptions
         */
        ::ecore::EAttribute_ptr m_ListAuthSysOptions__listAllAuthSystems;

        /**
         * \brief The instance for the feature listFullInfo of class ListAuthSysOptions
         */
        ::ecore::EAttribute_ptr m_ListAuthSysOptions__listFullInfo;

        /**
         * \brief The instance for the feature userId of class ListAuthSysOptions
         */
        ::ecore::EAttribute_ptr m_ListAuthSysOptions__userId;

        /**
         * \brief The instance for the feature authSystemId of class ListAuthSysOptions
         */
        ::ecore::EAttribute_ptr m_ListAuthSysOptions__authSystemId;

        /**
         * \brief The instance for the feature authSystemId of class AuthAccount
         */
        ::ecore::EAttribute_ptr m_AuthAccount__authSystemId;

        /**
         * \brief The instance for the feature userId of class AuthAccount
         */
        ::ecore::EAttribute_ptr m_AuthAccount__userId;

        /**
         * \brief The instance for the feature acLogin of class AuthAccount
         */
        ::ecore::EAttribute_ptr m_AuthAccount__acLogin;

        /**
         * \brief The instance for the feature AuthAccounts of class ListAuthAccounts
         */
        ::ecore::EReference_ptr m_ListAuthAccounts__AuthAccounts;

        /**
         * \brief The instance for the feature listAll of class ListAuthAccOptions
         */
        ::ecore::EAttribute_ptr m_ListAuthAccOptions__listAll;

        /**
         * \brief The instance for the feature userId of class ListAuthAccOptions
         */
        ::ecore::EAttribute_ptr m_ListAuthAccOptions__userId;

        /**
         * \brief The instance for the feature authSystemId of class ListAuthAccOptions
         */
        ::ecore::EAttribute_ptr m_ListAuthAccOptions__authSystemId;

        /**
         * \brief The instance for the feature major of class Version
         */
        ::ecore::EAttribute_ptr m_Version__major;

        /**
         * \brief The instance for the feature minor of class Version
         */
        ::ecore::EAttribute_ptr m_Version__minor;

        /**
         * \brief The instance for the feature patch of class Version
         */
        ::ecore::EAttribute_ptr m_Version__patch;

        /**
         * \brief The instance for the feature stringformat of class Version
         */
        ::ecore::EAttribute_ptr m_Version__stringformat;

    };

} // UMS_Data


#endif // _UMS_DATAPACKAGE_HPP
