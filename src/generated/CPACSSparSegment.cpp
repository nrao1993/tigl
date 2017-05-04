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
#include "CCPACSWingSparSegments.h"
#include "CPACSSparSegment.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSSparSegment::CPACSSparSegment(CCPACSWingSparSegments* parent, CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr), 
            m_sparCrossSection(reinterpret_cast<CCPACSWingSparSegment*>(this), m_uidMgr)
        {
            //assert(parent != NULL);
            m_parent = parent;
        }
        
        CPACSSparSegment::~CPACSSparSegment()
        {
            if (m_uidMgr && m_uID) m_uidMgr->UnregisterObject(*m_uID);
        }
        
        CCPACSWingSparSegments* CPACSSparSegment::GetParent() const
        {
            return m_parent;
        }
        
        void CPACSSparSegment::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read attribute uID
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "uID")) {
                m_uID = tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "uID");
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
            else {
                LOG(ERROR) << "Required element description is missing at xpath " << xpath;
            }
            
            // read element sparPositionUIDs
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sparPositionUIDs")) {
                m_sparPositionUIDs.ReadCPACS(tixiHandle, xpath + "/sparPositionUIDs");
            }
            else {
                LOG(ERROR) << "Required element sparPositionUIDs is missing at xpath " << xpath;
            }
            
            // read element sparCrossSection
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sparCrossSection")) {
                m_sparCrossSection.ReadCPACS(tixiHandle, xpath + "/sparCrossSection");
            }
            else {
                LOG(ERROR) << "Required element sparCrossSection is missing at xpath " << xpath;
            }
            
            if (m_uidMgr && m_uID) m_uidMgr->RegisterObject(*m_uID, *this);
        }
        
        void CPACSSparSegment::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write attribute uID
            if (m_uID) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/uID");
                tixihelper::TixiSaveAttribute(tixiHandle, xpath, "uID", *m_uID);
            }
            
            // write element name
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/name");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/name", m_name);
            
            // write element description
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/description");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/description", m_description);
            
            // write element sparPositionUIDs
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sparPositionUIDs");
            m_sparPositionUIDs.WriteCPACS(tixiHandle, xpath + "/sparPositionUIDs");
            
            // write element sparCrossSection
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sparCrossSection");
            m_sparCrossSection.WriteCPACS(tixiHandle, xpath + "/sparCrossSection");
            
        }
        
        const boost::optional<std::string>& CPACSSparSegment::GetUID() const
        {
            return m_uID;
        }
        
        void CPACSSparSegment::SetUID(const std::string& value)
        {
            m_uID = value;
        }
        
        void CPACSSparSegment::SetUID(const boost::optional<std::string>& value)
        {
            m_uID = value;
        }
        
        const std::string& CPACSSparSegment::GetName() const
        {
            return m_name;
        }
        
        void CPACSSparSegment::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        const std::string& CPACSSparSegment::GetDescription() const
        {
            return m_description;
        }
        
        void CPACSSparSegment::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        const CCPACSWingSparPositionUIDs& CPACSSparSegment::GetSparPositionUIDs() const
        {
            return m_sparPositionUIDs;
        }
        
        CCPACSWingSparPositionUIDs& CPACSSparSegment::GetSparPositionUIDs()
        {
            return m_sparPositionUIDs;
        }
        
        const CPACSSparCrossSection& CPACSSparSegment::GetSparCrossSection() const
        {
            return m_sparCrossSection;
        }
        
        CPACSSparCrossSection& CPACSSparSegment::GetSparCrossSection()
        {
            return m_sparCrossSection;
        }
        
    }
}
