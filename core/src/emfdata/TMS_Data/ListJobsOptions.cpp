// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TMS_Data/ListJobsOptions.cpp
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

#include "ListJobsOptions.hpp"
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "TMS_Data/TMS_DataPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::TMS_Data;

// Default constructor
ListJobsOptions::ListJobsOptions() :
    m_jobId(""), m_nbCpu(-1), m_fromSubmitDate(-1), m_toSubmitDate(-1),
            m_status(-1), m_priority(-1), m_batchJob(false), m_workId(-1),
            m_listAll(false)
{

    /*PROTECTED REGION ID(ListJobsOptionsImpl__ListJobsOptionsImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

ListJobsOptions::~ListJobsOptions()
{
}

/*PROTECTED REGION ID(ListJobsOptions.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EString const& ListJobsOptions::getJobId() const
{
    return m_jobId;
}

void ListJobsOptions::setJobId(::ecore::EString const& _jobId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_jobId = m_jobId;
#endif
    m_jobId = _jobId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__jobId(),
                _old_jobId,
                m_jobId
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt ListJobsOptions::getNbCpu() const
{
    return m_nbCpu;
}

void ListJobsOptions::setNbCpu(::ecore::EInt _nbCpu)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_nbCpu = m_nbCpu;
#endif
    m_nbCpu = _nbCpu;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__nbCpu(),
                _old_nbCpu,
                m_nbCpu
        );
        eNotify(&notification);
    }
#endif
}

::ecore::ELong ListJobsOptions::getFromSubmitDate() const
{
    return m_fromSubmitDate;
}

void ListJobsOptions::setFromSubmitDate(::ecore::ELong _fromSubmitDate)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::ELong _old_fromSubmitDate = m_fromSubmitDate;
#endif
    m_fromSubmitDate = _fromSubmitDate;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__fromSubmitDate(),
                _old_fromSubmitDate,
                m_fromSubmitDate
        );
        eNotify(&notification);
    }
#endif
}

::ecore::ELong ListJobsOptions::getToSubmitDate() const
{
    return m_toSubmitDate;
}

void ListJobsOptions::setToSubmitDate(::ecore::ELong _toSubmitDate)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::ELong _old_toSubmitDate = m_toSubmitDate;
#endif
    m_toSubmitDate = _toSubmitDate;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__toSubmitDate(),
                _old_toSubmitDate,
                m_toSubmitDate
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& ListJobsOptions::getOwner() const
{
    return m_owner;
}

void ListJobsOptions::setOwner(::ecore::EString const& _owner)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_owner = m_owner;
#endif
    m_owner = _owner;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__owner(),
                _old_owner,
                m_owner
        );
        eNotify(&notification);
    }
#endif
}

::TMS_Data::JobStatus ListJobsOptions::getStatus() const
{
    return m_status;
}

void ListJobsOptions::setStatus(::TMS_Data::JobStatus _status)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::TMS_Data::JobStatus _old_status = m_status;
#endif
    m_status = _status;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__status(),
                _old_status,
                m_status
        );
        eNotify(&notification);
    }
#endif
}

::TMS_Data::JobPriority ListJobsOptions::getPriority() const
{
    return m_priority;
}

void ListJobsOptions::setPriority(::TMS_Data::JobPriority _priority)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::TMS_Data::JobPriority _old_priority = m_priority;
#endif
    m_priority = _priority;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__priority(),
                _old_priority,
                m_priority
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& ListJobsOptions::getQueue() const
{
    return m_queue;
}

void ListJobsOptions::setQueue(::ecore::EString const& _queue)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_queue = m_queue;
#endif
    m_queue = _queue;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__queue(),
                _old_queue,
                m_queue
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& ListJobsOptions::getMultipleStatus() const
{
    return m_multipleStatus;
}

void ListJobsOptions::setMultipleStatus(::ecore::EString const& _multipleStatus)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_multipleStatus = m_multipleStatus;
#endif
    m_multipleStatus = _multipleStatus;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__multipleStatus(),
                _old_multipleStatus,
                m_multipleStatus
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean ListJobsOptions::isBatchJob() const
{
    return m_batchJob;
}

void ListJobsOptions::setBatchJob(::ecore::EBoolean _batchJob)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_batchJob = m_batchJob;
#endif
    m_batchJob = _batchJob;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__batchJob(),
                _old_batchJob,
                m_batchJob
        );
        eNotify(&notification);
    }
#endif
}

::ecore::ELong ListJobsOptions::getWorkId() const
{
    return m_workId;
}

void ListJobsOptions::setWorkId(::ecore::ELong _workId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::ELong _old_workId = m_workId;
#endif
    m_workId = _workId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__workId(),
                _old_workId,
                m_workId
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean ListJobsOptions::isListAll() const
{
    return m_listAll;
}

void ListJobsOptions::setListAll(::ecore::EBoolean _listAll)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_listAll = m_listAll;
#endif
    m_listAll = _listAll;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__listAll(),
                _old_listAll,
                m_listAll
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& ListJobsOptions::getMachineId() const
{
    return m_machineId;
}

void ListJobsOptions::setMachineId(::ecore::EString const& _machineId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_machineId = m_machineId;
#endif
    m_machineId = _machineId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getListJobsOptions__machineId(),
                _old_machineId,
                m_machineId
        );
        eNotify(&notification);
    }
#endif
}

// References

