// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * UMS_Data/MachineImpl.cpp
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

#include "Machine.hpp"
#include <UMS_Data/UMS_DataPackage.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::UMS_Data;

/*PROTECTED REGION ID(MachineImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void Machine::_initialize()
{
    // Supertypes

    // Rerefences

    /*PROTECTED REGION ID(MachineImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject Machine::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean _resolve)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::UMS_Data::UMS_DataPackage::MACHINE__MACHINEID:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_machineId);
    }
        return _any;
    case ::UMS_Data::UMS_DataPackage::MACHINE__ADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_address);
    }
        return _any;
    case ::UMS_Data::UMS_DataPackage::MACHINE__DESCRIPTION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_description);
    }
        return _any;
    case ::UMS_Data::UMS_DataPackage::MACHINE__STATUS:
    {
        ::ecorecpp::mapping::any_traits< ::UMS_Data::StatusType >::toAny(_any,
                m_status);
    }
        return _any;

    }
    throw "Error";
}

void Machine::eSet(::ecore::EInt _featureID,
        ::ecore::EJavaObject const& _newValue)
{
    switch (_featureID)
    {
    case ::UMS_Data::UMS_DataPackage::MACHINE__MACHINEID:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_machineId);
    }
        return;
    case ::UMS_Data::UMS_DataPackage::MACHINE__ADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_address);
    }
        return;
    case ::UMS_Data::UMS_DataPackage::MACHINE__DESCRIPTION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_description);
    }
        return;
    case ::UMS_Data::UMS_DataPackage::MACHINE__STATUS:
    {
        ::ecorecpp::mapping::any_traits< ::UMS_Data::StatusType >::fromAny(
                _newValue, m_status);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean Machine::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::UMS_Data::UMS_DataPackage::MACHINE__MACHINEID:
        return m_machineId != "";
    case ::UMS_Data::UMS_DataPackage::MACHINE__ADDRESS:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_address);
    case ::UMS_Data::UMS_DataPackage::MACHINE__DESCRIPTION:
        return m_description != "";
    case ::UMS_Data::UMS_DataPackage::MACHINE__STATUS:
        return m_status != -1;

    }
    throw "Error";
}

void Machine::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr Machine::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::UMS_Data::UMS_DataPackage_ptr > (::UMS_Data::UMS_DataPackage::_instance())->getMachine();
    return _eclass;
}

