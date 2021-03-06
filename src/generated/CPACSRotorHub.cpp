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

#include <cassert>
#include "CCPACSRotor.h"
#include "CPACSRotorHub.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSRotorHub::CPACSRotorHub(CCPACSRotor* parent, CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr), 
            m_rotorBladeAttachments(reinterpret_cast<CCPACSRotorHub*>(this), m_uidMgr)
        {
            //assert(parent != NULL);
            m_parent = parent;
        }
        
        CPACSRotorHub::~CPACSRotorHub()
        {
            if (m_uidMgr && m_uID) m_uidMgr->TryUnregisterObject(*m_uID);
        }
        
        CCPACSRotor* CPACSRotorHub::GetParent() const
        {
            return m_parent;
        }
        
        CTiglUIDManager& CPACSRotorHub::GetUIDManager()
        {
            return *m_uidMgr;
        }
        
        const CTiglUIDManager& CPACSRotorHub::GetUIDManager() const
        {
            return *m_uidMgr;
        }
        
        void CPACSRotorHub::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read attribute uID
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "uID")) {
                m_uID = tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "uID");
                if (m_uID->empty()) {
                    LOG(ERROR) << "Optional attribute uID is present but empty at xpath " << xpath;
                }
            }
            
            // read element name
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/name")) {
                m_name = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/name");
                if (m_name->empty()) {
                    LOG(ERROR) << "Optional element name is present but empty at xpath " << xpath;
                }
            }
            
            // read element description
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/description")) {
                m_description = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/description");
                if (m_description->empty()) {
                    LOG(ERROR) << "Optional element description is present but empty at xpath " << xpath;
                }
            }
            
            // read element type
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/type")) {
                m_type = stringToTiglRotorHubType(tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/type"));
            }
            
            // read element rotorBladeAttachments
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/rotorBladeAttachments")) {
                m_rotorBladeAttachments.ReadCPACS(tixiHandle, xpath + "/rotorBladeAttachments");
            }
            else {
                LOG(ERROR) << "Required element rotorBladeAttachments is missing at xpath " << xpath;
            }
            
            if (m_uidMgr && m_uID) m_uidMgr->RegisterObject(*m_uID, *this);
        }
        
        void CPACSRotorHub::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write attribute uID
            if (m_uID) {
                tixihelper::TixiSaveAttribute(tixiHandle, xpath, "uID", *m_uID);
            } else {
                if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "uID")) {
                    tixihelper::TixiRemoveAttribute(tixiHandle, xpath, "uID");
                }
            }
            
            // write element name
            if (m_name) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/name");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/name", *m_name);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/name")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/name");
                }
            }
            
            // write element description
            if (m_description) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/description");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/description", *m_description);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/description")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/description");
                }
            }
            
            // write element type
            if (m_type) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/type");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/type", TiglRotorHubTypeToString(*m_type));
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/type")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/type");
                }
            }
            
            // write element rotorBladeAttachments
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/rotorBladeAttachments");
            m_rotorBladeAttachments.WriteCPACS(tixiHandle, xpath + "/rotorBladeAttachments");
            
        }
        
        const boost::optional<std::string>& CPACSRotorHub::GetUID() const
        {
            return m_uID;
        }
        
        void CPACSRotorHub::SetUID(const std::string& value)
        {
            if (m_uidMgr) {
                if (m_uID) m_uidMgr->TryUnregisterObject(*m_uID);
                m_uidMgr->RegisterObject(value, *this);
            }
            m_uID = value;
        }
        
        void CPACSRotorHub::SetUID(const boost::optional<std::string>& value)
        {
            if (m_uidMgr) {
                if (m_uID) m_uidMgr->TryUnregisterObject(*m_uID);
                if (value) m_uidMgr->RegisterObject(*value, *this);
            }
            m_uID = value;
        }
        
        const boost::optional<std::string>& CPACSRotorHub::GetName() const
        {
            return m_name;
        }
        
        void CPACSRotorHub::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        void CPACSRotorHub::SetName(const boost::optional<std::string>& value)
        {
            m_name = value;
        }
        
        const boost::optional<std::string>& CPACSRotorHub::GetDescription() const
        {
            return m_description;
        }
        
        void CPACSRotorHub::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        void CPACSRotorHub::SetDescription(const boost::optional<std::string>& value)
        {
            m_description = value;
        }
        
        const boost::optional<TiglRotorHubType>& CPACSRotorHub::GetType() const
        {
            return m_type;
        }
        
        void CPACSRotorHub::SetType(const TiglRotorHubType& value)
        {
            m_type = value;
        }
        
        void CPACSRotorHub::SetType(const boost::optional<TiglRotorHubType>& value)
        {
            m_type = value;
        }
        
        const CCPACSRotorBladeAttachments& CPACSRotorHub::GetRotorBladeAttachments() const
        {
            return m_rotorBladeAttachments;
        }
        
        CCPACSRotorBladeAttachments& CPACSRotorHub::GetRotorBladeAttachments()
        {
            return m_rotorBladeAttachments;
        }
        
    }
}
