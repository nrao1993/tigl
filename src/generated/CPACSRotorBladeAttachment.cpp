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
#include "CCPACSRotorBladeAttachments.h"
#include "CPACSRotorBladeAttachment.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSRotorBladeAttachment::CPACSRotorBladeAttachment(CCPACSRotorBladeAttachments* parent, CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr)
        {
            //assert(parent != NULL);
            m_parent = parent;
        }
        
        CPACSRotorBladeAttachment::~CPACSRotorBladeAttachment()
        {
            if (m_uidMgr && m_uID) m_uidMgr->TryUnregisterObject(*m_uID);
        }
        
        CCPACSRotorBladeAttachments* CPACSRotorBladeAttachment::GetParent() const
        {
            return m_parent;
        }
        
        CTiglUIDManager& CPACSRotorBladeAttachment::GetUIDManager()
        {
            return *m_uidMgr;
        }
        
        const CTiglUIDManager& CPACSRotorBladeAttachment::GetUIDManager() const
        {
            return *m_uidMgr;
        }
        
        void CPACSRotorBladeAttachment::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
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
            
            // read element hinges
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/hinges")) {
                m_hinges = boost::in_place(reinterpret_cast<CCPACSRotorBladeAttachment*>(this), m_uidMgr);
                try {
                    m_hinges->ReadCPACS(tixiHandle, xpath + "/hinges");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read hinges at xpath " << xpath << ": " << e.what();
                    m_hinges = boost::none;
                }
            }
            
            // read element rotorBladeUID
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/rotorBladeUID")) {
                m_rotorBladeUID = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/rotorBladeUID");
                if (m_rotorBladeUID.empty()) {
                    LOG(ERROR) << "Required element rotorBladeUID is empty at xpath " << xpath;
                }
            }
            else {
                LOG(ERROR) << "Required element rotorBladeUID is missing at xpath " << xpath;
            }
            
            // read element azimuthAngles
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/azimuthAngles")) {
                m_azimuthAngles_choice1 = boost::in_place();
                try {
                    m_azimuthAngles_choice1->ReadCPACS(tixiHandle, xpath + "/azimuthAngles");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read azimuthAngles at xpath " << xpath << ": " << e.what();
                    m_azimuthAngles_choice1 = boost::none;
                }
            }
            
            // read element numberOfBlades
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/numberOfBlades")) {
                m_numberOfBlades_choice2 = tixihelper::TixiGetElement<int>(tixiHandle, xpath + "/numberOfBlades");
            }
            
            if (m_uidMgr && m_uID) m_uidMgr->RegisterObject(*m_uID, *this);
            if (!ValidateChoices()) {
                LOG(ERROR) << "Invalid choice configuration at xpath " << xpath;
            }
        }
        
        void CPACSRotorBladeAttachment::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
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
            
            // write element hinges
            if (m_hinges) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/hinges");
                m_hinges->WriteCPACS(tixiHandle, xpath + "/hinges");
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/hinges")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/hinges");
                }
            }
            
            // write element rotorBladeUID
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/rotorBladeUID");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/rotorBladeUID", m_rotorBladeUID);
            
            // write element azimuthAngles
            if (m_azimuthAngles_choice1) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/azimuthAngles");
                m_azimuthAngles_choice1->WriteCPACS(tixiHandle, xpath + "/azimuthAngles");
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/azimuthAngles")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/azimuthAngles");
                }
            }
            
            // write element numberOfBlades
            if (m_numberOfBlades_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/numberOfBlades");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/numberOfBlades", *m_numberOfBlades_choice2);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/numberOfBlades")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/numberOfBlades");
                }
            }
            
        }
        
        bool CPACSRotorBladeAttachment::ValidateChoices() const
        {
            return
            (
                (
                    (
                        m_azimuthAngles_choice1.is_initialized()
                    )
                    +
                    (
                        m_numberOfBlades_choice2.is_initialized()
                    )
                    == 1
                )
            )
            ;
        }
        
        const boost::optional<std::string>& CPACSRotorBladeAttachment::GetUID() const
        {
            return m_uID;
        }
        
        void CPACSRotorBladeAttachment::SetUID(const std::string& value)
        {
            if (m_uidMgr) {
                if (m_uID) m_uidMgr->TryUnregisterObject(*m_uID);
                m_uidMgr->RegisterObject(value, *this);
            }
            m_uID = value;
        }
        
        void CPACSRotorBladeAttachment::SetUID(const boost::optional<std::string>& value)
        {
            if (m_uidMgr) {
                if (m_uID) m_uidMgr->TryUnregisterObject(*m_uID);
                if (value) m_uidMgr->RegisterObject(*value, *this);
            }
            m_uID = value;
        }
        
        const boost::optional<std::string>& CPACSRotorBladeAttachment::GetName() const
        {
            return m_name;
        }
        
        void CPACSRotorBladeAttachment::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        void CPACSRotorBladeAttachment::SetName(const boost::optional<std::string>& value)
        {
            m_name = value;
        }
        
        const boost::optional<std::string>& CPACSRotorBladeAttachment::GetDescription() const
        {
            return m_description;
        }
        
        void CPACSRotorBladeAttachment::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        void CPACSRotorBladeAttachment::SetDescription(const boost::optional<std::string>& value)
        {
            m_description = value;
        }
        
        const boost::optional<CCPACSRotorHinges>& CPACSRotorBladeAttachment::GetHinges() const
        {
            return m_hinges;
        }
        
        boost::optional<CCPACSRotorHinges>& CPACSRotorBladeAttachment::GetHinges()
        {
            return m_hinges;
        }
        
        const std::string& CPACSRotorBladeAttachment::GetRotorBladeUID() const
        {
            return m_rotorBladeUID;
        }
        
        void CPACSRotorBladeAttachment::SetRotorBladeUID(const std::string& value)
        {
            m_rotorBladeUID = value;
        }
        
        const boost::optional<CCPACSStringVector>& CPACSRotorBladeAttachment::GetAzimuthAngles_choice1() const
        {
            return m_azimuthAngles_choice1;
        }
        
        boost::optional<CCPACSStringVector>& CPACSRotorBladeAttachment::GetAzimuthAngles_choice1()
        {
            return m_azimuthAngles_choice1;
        }
        
        const boost::optional<int>& CPACSRotorBladeAttachment::GetNumberOfBlades_choice2() const
        {
            return m_numberOfBlades_choice2;
        }
        
        void CPACSRotorBladeAttachment::SetNumberOfBlades_choice2(const int& value)
        {
            m_numberOfBlades_choice2 = value;
        }
        
        void CPACSRotorBladeAttachment::SetNumberOfBlades_choice2(const boost::optional<int>& value)
        {
            m_numberOfBlades_choice2 = value;
        }
        
    }
}
