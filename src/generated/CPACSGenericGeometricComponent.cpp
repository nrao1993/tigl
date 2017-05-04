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
#include "CCPACSExternalObjects.h"
#include "CPACSGenericGeometricComponent.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSGenericGeometricComponent::CPACSGenericGeometricComponent(CCPACSExternalObjects* parent, CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr), 
            m_transformation(m_uidMgr)
        {
            //assert(parent != NULL);
            m_parent = parent;
        }
        
        CPACSGenericGeometricComponent::~CPACSGenericGeometricComponent()
        {
            if (m_uidMgr) m_uidMgr->UnregisterObject(m_uID);
        }
        
        CCPACSExternalObjects* CPACSGenericGeometricComponent::GetParent() const
        {
            return m_parent;
        }
        
        void CPACSGenericGeometricComponent::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
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
            
            // read element linkToFile
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/linkToFile")) {
                m_linkToFile.ReadCPACS(tixiHandle, xpath + "/linkToFile");
            }
            else {
                LOG(ERROR) << "Required element linkToFile is missing at xpath " << xpath;
            }
            
            if (m_uidMgr) m_uidMgr->RegisterObject(m_uID, *this);
        }
        
        void CPACSGenericGeometricComponent::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
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
            
            // write element linkToFile
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/linkToFile");
            m_linkToFile.WriteCPACS(tixiHandle, xpath + "/linkToFile");
            
        }
        
        const std::string& CPACSGenericGeometricComponent::GetUID() const
        {
            return m_uID;
        }
        
        void CPACSGenericGeometricComponent::SetUID(const std::string& value)
        {
            m_uID = value;
        }
        
        const boost::optional<TiglSymmetryAxis>& CPACSGenericGeometricComponent::GetSymmetry() const
        {
            return m_symmetry;
        }
        
        void CPACSGenericGeometricComponent::SetSymmetry(const TiglSymmetryAxis& value)
        {
            m_symmetry = value;
        }
        
        void CPACSGenericGeometricComponent::SetSymmetry(const boost::optional<TiglSymmetryAxis>& value)
        {
            m_symmetry = value;
        }
        
        const std::string& CPACSGenericGeometricComponent::GetName() const
        {
            return m_name;
        }
        
        void CPACSGenericGeometricComponent::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        const boost::optional<std::string>& CPACSGenericGeometricComponent::GetDescription() const
        {
            return m_description;
        }
        
        void CPACSGenericGeometricComponent::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        void CPACSGenericGeometricComponent::SetDescription(const boost::optional<std::string>& value)
        {
            m_description = value;
        }
        
        const boost::optional<std::string>& CPACSGenericGeometricComponent::GetParentUID() const
        {
            return m_parentUID;
        }
        
        void CPACSGenericGeometricComponent::SetParentUID(const std::string& value)
        {
            m_parentUID = value;
        }
        
        void CPACSGenericGeometricComponent::SetParentUID(const boost::optional<std::string>& value)
        {
            m_parentUID = value;
        }
        
        const CCPACSTransformation& CPACSGenericGeometricComponent::GetTransformation() const
        {
            return m_transformation;
        }
        
        CCPACSTransformation& CPACSGenericGeometricComponent::GetTransformation()
        {
            return m_transformation;
        }
        
        const CPACSLinkToFile& CPACSGenericGeometricComponent::GetLinkToFile() const
        {
            return m_linkToFile;
        }
        
        CPACSLinkToFile& CPACSGenericGeometricComponent::GetLinkToFile()
        {
            return m_linkToFile;
        }
        
    }
}
