// Copyright (c) 2016 RISC Software GmbH
//
// This file was generated by CPACSGen from CPACS XML Schema (c) German Aerospace Center (DLR/SC).
// Do not edit, all changes are lost when files are re-generated.
//
// Licensed under the Apache License, Version 2.0 (the "License")
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "CPACSAircraftModel.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSAircraftModel::CPACSAircraftModel(CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr) {}
        
        CPACSAircraftModel::~CPACSAircraftModel()
        {
            if (m_uidMgr) m_uidMgr->UnregisterObject(m_uID);
        }
        
        void CPACSAircraftModel::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read attribute uID
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "uID")) {
                m_uID = tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "uID");
            }
            else {
                LOG(ERROR) << "Required attribute uID is missing at xpath " << xpath;
            }
            
            // read element name
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/name")) {
                m_name = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/name");
            }
            else {
                LOG(ERROR) << "Required element name is missing at xpath " << xpath;
            }
            
            // read element description
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/description")) {
                m_description = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/description");
            }
            
            // read element fuselages
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/fuselages")) {
                m_fuselages = boost::in_place(reinterpret_cast<CCPACSAircraftModel*>(this), m_uidMgr);
                try {
                    m_fuselages->ReadCPACS(tixiHandle, xpath + "/fuselages");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read fuselages at xpath " << xpath << ": " << e.what();
                    m_fuselages = boost::none;
                } catch(const CTiglError& e) {
                    LOG(ERROR) << "Failed to read fuselages at xpath " << xpath << ": " << e.getError();
                    m_fuselages = boost::none;
                }
            }
            
            // read element wings
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/wings")) {
                m_wings = boost::in_place(reinterpret_cast<CCPACSAircraftModel*>(this), m_uidMgr);
                try {
                    m_wings->ReadCPACS(tixiHandle, xpath + "/wings");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read wings at xpath " << xpath << ": " << e.what();
                    m_wings = boost::none;
                } catch(const CTiglError& e) {
                    LOG(ERROR) << "Failed to read wings at xpath " << xpath << ": " << e.getError();
                    m_wings = boost::none;
                }
            }
            
            // read element genericGeometryComponents
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/genericGeometryComponents")) {
                m_genericGeometryComponents = boost::in_place(reinterpret_cast<CCPACSAircraftModel*>(this), m_uidMgr);
                try {
                    m_genericGeometryComponents->ReadCPACS(tixiHandle, xpath + "/genericGeometryComponents");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read genericGeometryComponents at xpath " << xpath << ": " << e.what();
                    m_genericGeometryComponents = boost::none;
                } catch(const CTiglError& e) {
                    LOG(ERROR) << "Failed to read genericGeometryComponents at xpath " << xpath << ": " << e.getError();
                    m_genericGeometryComponents = boost::none;
                }
            }
            
            if (m_uidMgr) m_uidMgr->RegisterObject(m_uID, *this);
        }
        
        void CPACSAircraftModel::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write attribute uID
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/uID");
            tixihelper::TixiSaveAttribute(tixiHandle, xpath, "uID", m_uID);
            
            // write element name
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/name");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/name", m_name);
            
            // write element description
            if (m_description) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/description");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/description", *m_description);
            }
            
            // write element fuselages
            if (m_fuselages) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/fuselages");
                m_fuselages->WriteCPACS(tixiHandle, xpath + "/fuselages");
            }
            
            // write element wings
            if (m_wings) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/wings");
                m_wings->WriteCPACS(tixiHandle, xpath + "/wings");
            }
            
            // write element genericGeometryComponents
            if (m_genericGeometryComponents) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/genericGeometryComponents");
                m_genericGeometryComponents->WriteCPACS(tixiHandle, xpath + "/genericGeometryComponents");
            }
            
        }
        
        const std::string& CPACSAircraftModel::GetUID() const
        {
            return m_uID;
        }
        
        void CPACSAircraftModel::SetUID(const std::string& value)
        {
            m_uID = value;
        }
        
        const std::string& CPACSAircraftModel::GetName() const
        {
            return m_name;
        }
        
        void CPACSAircraftModel::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        const boost::optional<std::string>& CPACSAircraftModel::GetDescription() const
        {
            return m_description;
        }
        
        void CPACSAircraftModel::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        void CPACSAircraftModel::SetDescription(const boost::optional<std::string>& value)
        {
            m_description = value;
        }
        
        const boost::optional<CCPACSFuselages>& CPACSAircraftModel::GetFuselages() const
        {
            return m_fuselages;
        }
        
        boost::optional<CCPACSFuselages>& CPACSAircraftModel::GetFuselages()
        {
            return m_fuselages;
        }
        
        const boost::optional<CCPACSWings>& CPACSAircraftModel::GetWings() const
        {
            return m_wings;
        }
        
        boost::optional<CCPACSWings>& CPACSAircraftModel::GetWings()
        {
            return m_wings;
        }
        
        const boost::optional<CCPACSExternalObjects>& CPACSAircraftModel::GetGenericGeometryComponents() const
        {
            return m_genericGeometryComponents;
        }
        
        boost::optional<CCPACSExternalObjects>& CPACSAircraftModel::GetGenericGeometryComponents()
        {
            return m_genericGeometryComponents;
        }
        
    }
}
