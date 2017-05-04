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
#include "CCPACSRotorBlades.h"
#include "CCPACSWings.h"
#include "CPACSWing.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSWing::CPACSWing(CCPACSRotorBlades* parent, CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr), 
            m_transformation(m_uidMgr), 
            m_sections(m_uidMgr), 
            m_segments(reinterpret_cast<CCPACSWing*>(this), m_uidMgr)
        {
            //assert(parent != NULL);
            m_parent = parent;
            m_parentType = &typeid(CCPACSRotorBlades);
        }
        
        CPACSWing::CPACSWing(CCPACSWings* parent, CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr), 
            m_transformation(m_uidMgr), 
            m_sections(m_uidMgr), 
            m_segments(reinterpret_cast<CCPACSWing*>(this), m_uidMgr)
        {
            //assert(parent != NULL);
            m_parent = parent;
            m_parentType = &typeid(CCPACSWings);
        }
        
        CPACSWing::~CPACSWing()
        {
            if (m_uidMgr) m_uidMgr->UnregisterObject(m_uID);
        }
        
        void CPACSWing::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read attribute uID
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "uID")) {
                m_uID = tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "uID");
            }
            else {
                LOG(ERROR) << "Required attribute uID is missing at xpath " << xpath;
            }
            
            // read attribute symmetry
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "symmetry")) {
                m_symmetry = stringToTiglSymmetryAxis(tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "symmetry"));
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
            
            // read element parentUID
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/parentUID")) {
                m_parentUID = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/parentUID");
            }
            
            // read element transformation
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/transformation")) {
                m_transformation.ReadCPACS(tixiHandle, xpath + "/transformation");
            }
            else {
                LOG(ERROR) << "Required element transformation is missing at xpath " << xpath;
            }
            
            // read element sections
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/sections")) {
                m_sections.ReadCPACS(tixiHandle, xpath + "/sections");
            }
            else {
                LOG(ERROR) << "Required element sections is missing at xpath " << xpath;
            }
            
            // read element positionings
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/positionings")) {
                m_positionings = boost::in_place(m_uidMgr);
                try {
                    m_positionings->ReadCPACS(tixiHandle, xpath + "/positionings");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read positionings at xpath " << xpath << ": " << e.what();
                    m_positionings = boost::none;
                } catch(const CTiglError& e) {
                    LOG(ERROR) << "Failed to read positionings at xpath " << xpath << ": " << e.getError();
                    m_positionings = boost::none;
                }
            }
            
            // read element segments
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/segments")) {
                m_segments.ReadCPACS(tixiHandle, xpath + "/segments");
            }
            else {
                LOG(ERROR) << "Required element segments is missing at xpath " << xpath;
            }
            
            // read element componentSegments
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/componentSegments")) {
                m_componentSegments = boost::in_place(reinterpret_cast<CCPACSWing*>(this), m_uidMgr);
                try {
                    m_componentSegments->ReadCPACS(tixiHandle, xpath + "/componentSegments");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read componentSegments at xpath " << xpath << ": " << e.what();
                    m_componentSegments = boost::none;
                } catch(const CTiglError& e) {
                    LOG(ERROR) << "Failed to read componentSegments at xpath " << xpath << ": " << e.getError();
                    m_componentSegments = boost::none;
                }
            }
            
            if (m_uidMgr) m_uidMgr->RegisterObject(m_uID, *this);
        }
        
        void CPACSWing::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write attribute uID
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/uID");
            tixihelper::TixiSaveAttribute(tixiHandle, xpath, "uID", m_uID);
            
            // write attribute symmetry
            if (m_symmetry) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/symmetry");
                tixihelper::TixiSaveAttribute(tixiHandle, xpath, "symmetry", TiglSymmetryAxisToString(*m_symmetry));
            }
            
            // write element name
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/name");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/name", m_name);
            
            // write element description
            if (m_description) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/description");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/description", *m_description);
            }
            
            // write element parentUID
            if (m_parentUID) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/parentUID");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/parentUID", *m_parentUID);
            }
            
            // write element transformation
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/transformation");
            m_transformation.WriteCPACS(tixiHandle, xpath + "/transformation");
            
            // write element sections
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/sections");
            m_sections.WriteCPACS(tixiHandle, xpath + "/sections");
            
            // write element positionings
            if (m_positionings) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/positionings");
                m_positionings->WriteCPACS(tixiHandle, xpath + "/positionings");
            }
            
            // write element segments
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/segments");
            m_segments.WriteCPACS(tixiHandle, xpath + "/segments");
            
            // write element componentSegments
            if (m_componentSegments) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/componentSegments");
                m_componentSegments->WriteCPACS(tixiHandle, xpath + "/componentSegments");
            }
            
        }
        
        const std::string& CPACSWing::GetUID() const
        {
            return m_uID;
        }
        
        void CPACSWing::SetUID(const std::string& value)
        {
            m_uID = value;
        }
        
        const boost::optional<TiglSymmetryAxis>& CPACSWing::GetSymmetry() const
        {
            return m_symmetry;
        }
        
        void CPACSWing::SetSymmetry(const TiglSymmetryAxis& value)
        {
            m_symmetry = value;
        }
        
        void CPACSWing::SetSymmetry(const boost::optional<TiglSymmetryAxis>& value)
        {
            m_symmetry = value;
        }
        
        const std::string& CPACSWing::GetName() const
        {
            return m_name;
        }
        
        void CPACSWing::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        const boost::optional<std::string>& CPACSWing::GetDescription() const
        {
            return m_description;
        }
        
        void CPACSWing::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        void CPACSWing::SetDescription(const boost::optional<std::string>& value)
        {
            m_description = value;
        }
        
        const boost::optional<std::string>& CPACSWing::GetParentUID() const
        {
            return m_parentUID;
        }
        
        void CPACSWing::SetParentUID(const std::string& value)
        {
            m_parentUID = value;
        }
        
        void CPACSWing::SetParentUID(const boost::optional<std::string>& value)
        {
            m_parentUID = value;
        }
        
        const CCPACSTransformation& CPACSWing::GetTransformation() const
        {
            return m_transformation;
        }
        
        CCPACSTransformation& CPACSWing::GetTransformation()
        {
            return m_transformation;
        }
        
        const CCPACSWingSections& CPACSWing::GetSections() const
        {
            return m_sections;
        }
        
        CCPACSWingSections& CPACSWing::GetSections()
        {
            return m_sections;
        }
        
        const boost::optional<CCPACSPositionings>& CPACSWing::GetPositionings() const
        {
            return m_positionings;
        }
        
        boost::optional<CCPACSPositionings>& CPACSWing::GetPositionings()
        {
            return m_positionings;
        }
        
        const CCPACSWingSegments& CPACSWing::GetSegments() const
        {
            return m_segments;
        }
        
        CCPACSWingSegments& CPACSWing::GetSegments()
        {
            return m_segments;
        }
        
        const boost::optional<CCPACSWingComponentSegments>& CPACSWing::GetComponentSegments() const
        {
            return m_componentSegments;
        }
        
        boost::optional<CCPACSWingComponentSegments>& CPACSWing::GetComponentSegments()
        {
            return m_componentSegments;
        }
        
    }
}
