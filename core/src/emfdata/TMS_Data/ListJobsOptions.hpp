// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TMS_Data/ListJobsOptions.hpp
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
 * \file ListJobsOptions.hpp
 * \brief The ListJobsOptions class
 * \author Generated file
 * \date 31/03/2011
 */

#ifndef TMS_DATA_LISTJOBSOPTIONS_HPP
#define TMS_DATA_LISTJOBSOPTIONS_HPP

#include <TMS_Data_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <ecore_forward.hpp>

#include <ecore/EObject.hpp>

/*PROTECTED REGION ID(ListJobsOptions_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace TMS_Data
{

    /**
     * \class ListJobsOptions
     * \brief Implementation of the ListJobsOptions class
     */
    class ListJobsOptions: public virtual ::ecore::EObject

    {
    public:
        /**
         * \brief The default constructor for ListJobsOptions
         */
        ListJobsOptions();
        /**
         * \brief The destructor for ListJobsOptions
         */
        virtual ~ListJobsOptions();

        /**
         * \brief Internal method
         */
        virtual void _initialize();

        // Operations


        // Attributes
        /**
         * \brief To get the jobId
         * \return The jobId attribute value
         **/
        ::ecore::EString const& getJobId() const;
        /**
         * \brief To set the jobId
         * \param _jobId The jobId value
         **/
        void setJobId(::ecore::EString const& _jobId);

        /**
         * \brief To get the nbCpu
         * \return The nbCpu attribute value
         **/
        ::ecore::EInt getNbCpu() const;
        /**
         * \brief To set the nbCpu
         * \param _nbCpu The nbCpu value
         **/
        void setNbCpu(::ecore::EInt _nbCpu);

        /**
         * \brief To get the fromSubmitDate
         * \return The fromSubmitDate attribute value
         **/
        ::ecore::ELong getFromSubmitDate() const;
        /**
         * \brief To set the fromSubmitDate
         * \param _fromSubmitDate The fromSubmitDate value
         **/
        void setFromSubmitDate(::ecore::ELong _fromSubmitDate);

        /**
         * \brief To get the toSubmitDate
         * \return The toSubmitDate attribute value
         **/
        ::ecore::ELong getToSubmitDate() const;
        /**
         * \brief To set the toSubmitDate
         * \param _toSubmitDate The toSubmitDate value
         **/
        void setToSubmitDate(::ecore::ELong _toSubmitDate);

        /**
         * \brief To get the owner
         * \return The owner attribute value
         **/
        ::ecore::EString const& getOwner() const;
        /**
         * \brief To set the owner
         * \param _owner The owner value
         **/
        void setOwner(::ecore::EString const& _owner);

        /**
         * \brief To get the status
         * \return The status attribute value
         **/
        ::TMS_Data::JobStatus getStatus() const;
        /**
         * \brief To set the status
         * \param _status The status value
         **/
        void setStatus(::TMS_Data::JobStatus _status);

        /**
         * \brief To get the priority
         * \return The priority attribute value
         **/
        ::TMS_Data::JobPriority getPriority() const;
        /**
         * \brief To set the priority
         * \param _priority The priority value
         **/
        void setPriority(::TMS_Data::JobPriority _priority);

        /**
         * \brief To get the queue
         * \return The queue attribute value
         **/
        ::ecore::EString const& getQueue() const;
        /**
         * \brief To set the queue
         * \param _queue The queue value
         **/
        void setQueue(::ecore::EString const& _queue);

        /**
         * \brief To get the multipleStatus
         * \return The multipleStatus attribute value
         **/
        ::ecore::EString const& getMultipleStatus() const;
        /**
         * \brief To set the multipleStatus
         * \param _multipleStatus The multipleStatus value
         **/
        void setMultipleStatus(::ecore::EString const& _multipleStatus);

        /**
         * \brief To get the batchJob
         * \return The batchJob attribute value
         **/
        ::ecore::EBoolean isBatchJob() const;
        /**
         * \brief To set the batchJob
         * \param _batchJob The batchJob value
         **/
        void setBatchJob(::ecore::EBoolean _batchJob);

        /**
         * \brief To get the workId
         * \return The workId attribute value
         **/
        ::ecore::ELong getWorkId() const;
        /**
         * \brief To set the workId
         * \param _workId The workId value
         **/
        void setWorkId(::ecore::ELong _workId);

        /**
         * \brief To get the listAll
         * \return The listAll attribute value
         **/
        ::ecore::EBoolean isListAll() const;
        /**
         * \brief To set the listAll
         * \param _listAll The listAll value
         **/
        void setListAll(::ecore::EBoolean _listAll);

        /**
         * \brief To get the machineId
         * \return The machineId attribute value
         **/
        ::ecore::EString const& getMachineId() const;
        /**
         * \brief To set the machineId
         * \param _machineId The machineId value
         **/
        void setMachineId(::ecore::EString const& _machineId);

        // References


        /*PROTECTED REGION ID(ListJobsOptions) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet(::ecore::EInt _featureID,
                ::ecore::EBoolean _resolve);
        virtual void eSet(::ecore::EInt _featureID,
                ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet(::ecore::EInt _featureID);
        virtual void eUnset(::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass();

        /*PROTECTED REGION ID(ListJobsOptionsImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EString m_jobId;

        ::ecore::EInt m_nbCpu;

        ::ecore::ELong m_fromSubmitDate;

        ::ecore::ELong m_toSubmitDate;

        ::ecore::EString m_owner;

        ::TMS_Data::JobStatus m_status;

        ::TMS_Data::JobPriority m_priority;

        ::ecore::EString m_queue;

        ::ecore::EString m_multipleStatus;

        ::ecore::EBoolean m_batchJob;

        ::ecore::ELong m_workId;

        ::ecore::EBoolean m_listAll;

        ::ecore::EString m_machineId;

        // References

    };

} // TMS_Data

#endif // TMS_DATA_LISTJOBSOPTIONS_HPP
