// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * FMS_Data/FMS_DataPackage.hpp
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
 * \file FMS_DataPackage.hpp
 * \brief The FMS_DataPackage class
 * \author Generated file
 * \date 31/03/2011
 */

#ifndef _FMS_DATAPACKAGE_HPP
#define _FMS_DATAPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <FMS_Data_forward.hpp>

namespace FMS_Data
{
    /**
     * \class FMS_DataPackage
     * \brief The package class (reflective API) for generated model FMS_Data
     */
    class FMS_DataPackage: public virtual ::ecore::EPackage
    {
    public:

        /**
         * \brief To get the instance of the singleton
         * \return Pointer to the instance
         */
        static FMS_DataPackage_ptr _instance();

        // IDs for classifiers

        /**
         * \brief Constant for CpFileOptions class
         */
        static const int CPFILEOPTIONS = 0;

        /**
         * \brief Constant for FileStat class
         */
        static const int FILESTAT = 1;

        /**
         * \brief Constant for FileStatList class
         */
        static const int FILESTATLIST = 2;

        /**
         * \brief Constant for FileTransfer class
         */
        static const int FILETRANSFER = 3;

        /**
         * \brief Constant for FileTransferList class
         */
        static const int FILETRANSFERLIST = 4;

        /**
         * \brief Constant for FileType class
         */
        static const int FILETYPE = 5;

        /**
         * \brief Constant for HeadOfFileOptions class
         */
        static const int HEADOFFILEOPTIONS = 6;

        /**
         * \brief Constant for LsDirOptions class
         */
        static const int LSDIROPTIONS = 7;

        /**
         * \brief Constant for LsTransferOptions class
         */
        static const int LSTRANSFEROPTIONS = 8;

        /**
         * \brief Constant for MvFileOptions class
         */
        static const int MVFILEOPTIONS = 9;

        /**
         * \brief Constant for Status class
         */
        static const int STATUS = 10;

        /**
         * \brief Constant for StopTransferOptions class
         */
        static const int STOPTRANSFEROPTIONS = 11;

        /**
         * \brief Constant for StringList class
         */
        static const int STRINGLIST = 12;

        /**
         * \brief Constant for TailOfFileOptions class
         */
        static const int TAILOFFILEOPTIONS = 13;

        /**
         * \brief Constant for TransferCommand class
         */
        static const int TRANSFERCOMMAND = 14;

        /**
         * \brief Constant for STRINGLIST__STRINGS feature
         */
        static const int STRINGLIST__STRINGS = 0;

        /**
         * \brief Constant for FILESTAT__PATH feature
         */
        static const int FILESTAT__PATH = 1;

        /**
         * \brief Constant for FILESTAT__OWNER feature
         */
        static const int FILESTAT__OWNER = 2;

        /**
         * \brief Constant for FILESTAT__GROUP feature
         */
        static const int FILESTAT__GROUP = 3;

        /**
         * \brief Constant for FILESTAT__PERMS feature
         */
        static const int FILESTAT__PERMS = 4;

        /**
         * \brief Constant for FILESTAT__UID feature
         */
        static const int FILESTAT__UID = 5;

        /**
         * \brief Constant for FILESTAT__GID feature
         */
        static const int FILESTAT__GID = 6;

        /**
         * \brief Constant for FILESTAT__SIZE feature
         */
        static const int FILESTAT__SIZE = 7;

        /**
         * \brief Constant for FILESTAT__ATIME feature
         */
        static const int FILESTAT__ATIME = 8;

        /**
         * \brief Constant for FILESTAT__MTIME feature
         */
        static const int FILESTAT__MTIME = 9;

        /**
         * \brief Constant for FILESTAT__CTIME feature
         */
        static const int FILESTAT__CTIME = 10;

        /**
         * \brief Constant for FILESTAT__TYPE feature
         */
        static const int FILESTAT__TYPE = 11;

        /**
         * \brief Constant for CPFILEOPTIONS__ISRECURSIVE feature
         */
        static const int CPFILEOPTIONS__ISRECURSIVE = 12;

        /**
         * \brief Constant for CPFILEOPTIONS__TRCOMMAND feature
         */
        static const int CPFILEOPTIONS__TRCOMMAND = 13;

        /**
         * \brief Constant for LSDIROPTIONS__LONGFORMAT feature
         */
        static const int LSDIROPTIONS__LONGFORMAT = 14;

        /**
         * \brief Constant for LSDIROPTIONS__ALLFILES feature
         */
        static const int LSDIROPTIONS__ALLFILES = 15;

        /**
         * \brief Constant for MVFILEOPTIONS__TRCOMMAND feature
         */
        static const int MVFILEOPTIONS__TRCOMMAND = 16;

        /**
         * \brief Constant for LSTRANSFEROPTIONS__TRANSFERID feature
         */
        static const int LSTRANSFEROPTIONS__TRANSFERID = 17;

        /**
         * \brief Constant for LSTRANSFEROPTIONS__FROMMACHINEID feature
         */
        static const int LSTRANSFEROPTIONS__FROMMACHINEID = 18;

        /**
         * \brief Constant for LSTRANSFEROPTIONS__USERID feature
         */
        static const int LSTRANSFEROPTIONS__USERID = 19;

        /**
         * \brief Constant for LSTRANSFEROPTIONS__STATUS feature
         */
        static const int LSTRANSFEROPTIONS__STATUS = 20;

        /**
         * \brief Constant for FILESTATLIST__FILESTATS feature
         */
        static const int FILESTATLIST__FILESTATS = 21;

        /**
         * \brief Constant for STOPTRANSFEROPTIONS__TRANSFERID feature
         */
        static const int STOPTRANSFEROPTIONS__TRANSFERID = 22;

        /**
         * \brief Constant for STOPTRANSFEROPTIONS__FROMMACHINEID feature
         */
        static const int STOPTRANSFEROPTIONS__FROMMACHINEID = 23;

        /**
         * \brief Constant for STOPTRANSFEROPTIONS__USERID feature
         */
        static const int STOPTRANSFEROPTIONS__USERID = 24;

        /**
         * \brief Constant for FILETRANSFER__TRANSFERID feature
         */
        static const int FILETRANSFER__TRANSFERID = 25;

        /**
         * \brief Constant for FILETRANSFER__STATUS feature
         */
        static const int FILETRANSFER__STATUS = 26;

        /**
         * \brief Constant for FILETRANSFER__USERID feature
         */
        static const int FILETRANSFER__USERID = 27;

        /**
         * \brief Constant for FILETRANSFER__CLIENTMACHINEID feature
         */
        static const int FILETRANSFER__CLIENTMACHINEID = 28;

        /**
         * \brief Constant for FILETRANSFER__SOURCEMACHINEID feature
         */
        static const int FILETRANSFER__SOURCEMACHINEID = 29;

        /**
         * \brief Constant for FILETRANSFER__DESTINATIONMACHINEID feature
         */
        static const int FILETRANSFER__DESTINATIONMACHINEID = 30;

        /**
         * \brief Constant for FILETRANSFER__SOURCEFILEPATH feature
         */
        static const int FILETRANSFER__SOURCEFILEPATH = 31;

        /**
         * \brief Constant for FILETRANSFER__DESTINATIONFILEPATH feature
         */
        static const int FILETRANSFER__DESTINATIONFILEPATH = 32;

        /**
         * \brief Constant for FILETRANSFER__SIZE feature
         */
        static const int FILETRANSFER__SIZE = 33;

        /**
         * \brief Constant for FILETRANSFER__START_TIME feature
         */
        static const int FILETRANSFER__START_TIME = 34;

        /**
         * \brief Constant for FILETRANSFER__TRCOMMAND feature
         */
        static const int FILETRANSFER__TRCOMMAND = 35;

        /**
         * \brief Constant for FILETRANSFER__ERRORMSG feature
         */
        static const int FILETRANSFER__ERRORMSG = 36;

        /**
         * \brief Constant for FILETRANSFERLIST__FILETRANSFERS feature
         */
        static const int FILETRANSFERLIST__FILETRANSFERS = 37;

        /**
         * \brief Constant for HEADOFFILEOPTIONS__NLINE feature
         */
        static const int HEADOFFILEOPTIONS__NLINE = 38;

        /**
         * \brief Constant for TAILOFFILEOPTIONS__NLINE feature
         */
        static const int TAILOFFILEOPTIONS__NLINE = 39;

        // EClassifiers methods

        /**
         * \brief Returns the reflective object for class FileType
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getFileType();

        /**
         * \brief Returns the reflective object for class StringList
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getStringList();

        /**
         * \brief Returns the reflective object for class Status
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getStatus();

        /**
         * \brief Returns the reflective object for class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getFileStat();

        /**
         * \brief Returns the reflective object for class CpFileOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getCpFileOptions();

        /**
         * \brief Returns the reflective object for class TransferCommand
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EEnum_ptr getTransferCommand();

        /**
         * \brief Returns the reflective object for class LsDirOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getLsDirOptions();

        /**
         * \brief Returns the reflective object for class MvFileOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getMvFileOptions();

        /**
         * \brief Returns the reflective object for class LsTransferOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getLsTransferOptions();

        /**
         * \brief Returns the reflective object for class FileStatList
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getFileStatList();

        /**
         * \brief Returns the reflective object for class StopTransferOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getStopTransferOptions();

        /**
         * \brief Returns the reflective object for class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getFileTransfer();

        /**
         * \brief Returns the reflective object for class FileTransferList
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getFileTransferList();

        /**
         * \brief Returns the reflective object for class HeadOfFileOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getHeadOfFileOptions();

        /**
         * \brief Returns the reflective object for class TailOfFileOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EClass_ptr getTailOfFileOptions();

        // EStructuralFeatures methods

        /**
         * \brief Returns the reflective object for feature strings of class StringList
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getStringList__strings();

        /**
         * \brief Returns the reflective object for feature path of class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileStat__path();

        /**
         * \brief Returns the reflective object for feature owner of class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileStat__owner();

        /**
         * \brief Returns the reflective object for feature group of class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileStat__group();

        /**
         * \brief Returns the reflective object for feature perms of class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileStat__perms();

        /**
         * \brief Returns the reflective object for feature uid of class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileStat__uid();

        /**
         * \brief Returns the reflective object for feature gid of class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileStat__gid();

        /**
         * \brief Returns the reflective object for feature size of class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileStat__size();

        /**
         * \brief Returns the reflective object for feature atime of class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileStat__atime();

        /**
         * \brief Returns the reflective object for feature mtime of class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileStat__mtime();

        /**
         * \brief Returns the reflective object for feature ctime of class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileStat__ctime();

        /**
         * \brief Returns the reflective object for feature type of class FileStat
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileStat__type();

        /**
         * \brief Returns the reflective object for feature isRecursive of class CpFileOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCpFileOptions__isRecursive();

        /**
         * \brief Returns the reflective object for feature trCommand of class CpFileOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getCpFileOptions__trCommand();

        /**
         * \brief Returns the reflective object for feature longFormat of class LsDirOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLsDirOptions__longFormat();

        /**
         * \brief Returns the reflective object for feature allFiles of class LsDirOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLsDirOptions__allFiles();

        /**
         * \brief Returns the reflective object for feature trCommand of class MvFileOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getMvFileOptions__trCommand();

        /**
         * \brief Returns the reflective object for feature transferId of class LsTransferOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLsTransferOptions__transferId();

        /**
         * \brief Returns the reflective object for feature fromMachineId of class LsTransferOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLsTransferOptions__fromMachineId();

        /**
         * \brief Returns the reflective object for feature userId of class LsTransferOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLsTransferOptions__userId();

        /**
         * \brief Returns the reflective object for feature status of class LsTransferOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getLsTransferOptions__status();

        /**
         * \brief Returns the reflective object for feature fileStats of class FileStatList
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getFileStatList__fileStats();

        /**
         * \brief Returns the reflective object for feature transferId of class StopTransferOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getStopTransferOptions__transferId();

        /**
         * \brief Returns the reflective object for feature fromMachineId of class StopTransferOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getStopTransferOptions__fromMachineId();

        /**
         * \brief Returns the reflective object for feature userId of class StopTransferOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getStopTransferOptions__userId();

        /**
         * \brief Returns the reflective object for feature transferId of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__transferId();

        /**
         * \brief Returns the reflective object for feature status of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__status();

        /**
         * \brief Returns the reflective object for feature userId of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__userId();

        /**
         * \brief Returns the reflective object for feature clientMachineId of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__clientMachineId();

        /**
         * \brief Returns the reflective object for feature sourceMachineId of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__sourceMachineId();

        /**
         * \brief Returns the reflective object for feature destinationMachineId of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__destinationMachineId();

        /**
         * \brief Returns the reflective object for feature sourceFilePath of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__sourceFilePath();

        /**
         * \brief Returns the reflective object for feature destinationFilePath of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__destinationFilePath();

        /**
         * \brief Returns the reflective object for feature size of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__size();

        /**
         * \brief Returns the reflective object for feature start_time of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__start_time();

        /**
         * \brief Returns the reflective object for feature trCommand of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__trCommand();

        /**
         * \brief Returns the reflective object for feature errorMsg of class FileTransfer
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getFileTransfer__errorMsg();

        /**
         * \brief Returns the reflective object for feature fileTransfers of class FileTransferList
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EReference_ptr getFileTransferList__fileTransfers();

        /**
         * \brief Returns the reflective object for feature nline of class HeadOfFileOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getHeadOfFileOptions__nline();

        /**
         * \brief Returns the reflective object for feature nline of class TailOfFileOptions
         * \return A pointer to the reflective object
         */
        virtual ::ecore::EAttribute_ptr getTailOfFileOptions__nline();

    protected:

        /**
         * \brief The instance of the package
         */
        static std::auto_ptr< FMS_DataPackage > s_instance;

        FMS_DataPackage();

        // EClass instances 

        /**
         * \brief The instance for the class StringList
         */
        ::ecore::EClass_ptr m_StringListEClass;

        /**
         * \brief The instance for the class FileStat
         */
        ::ecore::EClass_ptr m_FileStatEClass;

        /**
         * \brief The instance for the class CpFileOptions
         */
        ::ecore::EClass_ptr m_CpFileOptionsEClass;

        /**
         * \brief The instance for the class LsDirOptions
         */
        ::ecore::EClass_ptr m_LsDirOptionsEClass;

        /**
         * \brief The instance for the class MvFileOptions
         */
        ::ecore::EClass_ptr m_MvFileOptionsEClass;

        /**
         * \brief The instance for the class LsTransferOptions
         */
        ::ecore::EClass_ptr m_LsTransferOptionsEClass;

        /**
         * \brief The instance for the class FileStatList
         */
        ::ecore::EClass_ptr m_FileStatListEClass;

        /**
         * \brief The instance for the class StopTransferOptions
         */
        ::ecore::EClass_ptr m_StopTransferOptionsEClass;

        /**
         * \brief The instance for the class FileTransfer
         */
        ::ecore::EClass_ptr m_FileTransferEClass;

        /**
         * \brief The instance for the class FileTransferList
         */
        ::ecore::EClass_ptr m_FileTransferListEClass;

        /**
         * \brief The instance for the class HeadOfFileOptions
         */
        ::ecore::EClass_ptr m_HeadOfFileOptionsEClass;

        /**
         * \brief The instance for the class TailOfFileOptions
         */
        ::ecore::EClass_ptr m_TailOfFileOptionsEClass;

        // EEnuminstances 

        /**
         * \brief The instance for the enum FileType
         */
        ::ecore::EEnum_ptr m_FileTypeEEnum;

        /**
         * \brief The instance for the enum Status
         */
        ::ecore::EEnum_ptr m_StatusEEnum;

        /**
         * \brief The instance for the enum TransferCommand
         */
        ::ecore::EEnum_ptr m_TransferCommandEEnum;

        // EDataType instances 


        // EStructuralFeatures instances

        /**
         * \brief The instance for the feature strings of class StringList
         */
        ::ecore::EAttribute_ptr m_StringList__strings;

        /**
         * \brief The instance for the feature path of class FileStat
         */
        ::ecore::EAttribute_ptr m_FileStat__path;

        /**
         * \brief The instance for the feature owner of class FileStat
         */
        ::ecore::EAttribute_ptr m_FileStat__owner;

        /**
         * \brief The instance for the feature group of class FileStat
         */
        ::ecore::EAttribute_ptr m_FileStat__group;

        /**
         * \brief The instance for the feature perms of class FileStat
         */
        ::ecore::EAttribute_ptr m_FileStat__perms;

        /**
         * \brief The instance for the feature uid of class FileStat
         */
        ::ecore::EAttribute_ptr m_FileStat__uid;

        /**
         * \brief The instance for the feature gid of class FileStat
         */
        ::ecore::EAttribute_ptr m_FileStat__gid;

        /**
         * \brief The instance for the feature size of class FileStat
         */
        ::ecore::EAttribute_ptr m_FileStat__size;

        /**
         * \brief The instance for the feature atime of class FileStat
         */
        ::ecore::EAttribute_ptr m_FileStat__atime;

        /**
         * \brief The instance for the feature mtime of class FileStat
         */
        ::ecore::EAttribute_ptr m_FileStat__mtime;

        /**
         * \brief The instance for the feature ctime of class FileStat
         */
        ::ecore::EAttribute_ptr m_FileStat__ctime;

        /**
         * \brief The instance for the feature type of class FileStat
         */
        ::ecore::EAttribute_ptr m_FileStat__type;

        /**
         * \brief The instance for the feature isRecursive of class CpFileOptions
         */
        ::ecore::EAttribute_ptr m_CpFileOptions__isRecursive;

        /**
         * \brief The instance for the feature trCommand of class CpFileOptions
         */
        ::ecore::EAttribute_ptr m_CpFileOptions__trCommand;

        /**
         * \brief The instance for the feature longFormat of class LsDirOptions
         */
        ::ecore::EAttribute_ptr m_LsDirOptions__longFormat;

        /**
         * \brief The instance for the feature allFiles of class LsDirOptions
         */
        ::ecore::EAttribute_ptr m_LsDirOptions__allFiles;

        /**
         * \brief The instance for the feature trCommand of class MvFileOptions
         */
        ::ecore::EAttribute_ptr m_MvFileOptions__trCommand;

        /**
         * \brief The instance for the feature transferId of class LsTransferOptions
         */
        ::ecore::EAttribute_ptr m_LsTransferOptions__transferId;

        /**
         * \brief The instance for the feature fromMachineId of class LsTransferOptions
         */
        ::ecore::EAttribute_ptr m_LsTransferOptions__fromMachineId;

        /**
         * \brief The instance for the feature userId of class LsTransferOptions
         */
        ::ecore::EAttribute_ptr m_LsTransferOptions__userId;

        /**
         * \brief The instance for the feature status of class LsTransferOptions
         */
        ::ecore::EAttribute_ptr m_LsTransferOptions__status;

        /**
         * \brief The instance for the feature fileStats of class FileStatList
         */
        ::ecore::EReference_ptr m_FileStatList__fileStats;

        /**
         * \brief The instance for the feature transferId of class StopTransferOptions
         */
        ::ecore::EAttribute_ptr m_StopTransferOptions__transferId;

        /**
         * \brief The instance for the feature fromMachineId of class StopTransferOptions
         */
        ::ecore::EAttribute_ptr m_StopTransferOptions__fromMachineId;

        /**
         * \brief The instance for the feature userId of class StopTransferOptions
         */
        ::ecore::EAttribute_ptr m_StopTransferOptions__userId;

        /**
         * \brief The instance for the feature transferId of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__transferId;

        /**
         * \brief The instance for the feature status of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__status;

        /**
         * \brief The instance for the feature userId of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__userId;

        /**
         * \brief The instance for the feature clientMachineId of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__clientMachineId;

        /**
         * \brief The instance for the feature sourceMachineId of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__sourceMachineId;

        /**
         * \brief The instance for the feature destinationMachineId of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__destinationMachineId;

        /**
         * \brief The instance for the feature sourceFilePath of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__sourceFilePath;

        /**
         * \brief The instance for the feature destinationFilePath of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__destinationFilePath;

        /**
         * \brief The instance for the feature size of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__size;

        /**
         * \brief The instance for the feature start_time of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__start_time;

        /**
         * \brief The instance for the feature trCommand of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__trCommand;

        /**
         * \brief The instance for the feature errorMsg of class FileTransfer
         */
        ::ecore::EAttribute_ptr m_FileTransfer__errorMsg;

        /**
         * \brief The instance for the feature fileTransfers of class FileTransferList
         */
        ::ecore::EReference_ptr m_FileTransferList__fileTransfers;

        /**
         * \brief The instance for the feature nline of class HeadOfFileOptions
         */
        ::ecore::EAttribute_ptr m_HeadOfFileOptions__nline;

        /**
         * \brief The instance for the feature nline of class TailOfFileOptions
         */
        ::ecore::EAttribute_ptr m_TailOfFileOptions__nline;

    };

} // FMS_Data


#endif // _FMS_DATAPACKAGE_HPP
