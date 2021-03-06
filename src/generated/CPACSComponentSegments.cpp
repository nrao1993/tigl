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
#include <CCPACSWingComponentSegment.h>
#include "CCPACSWing.h"
#include "CPACSComponentSegments.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSComponentSegments::CPACSComponentSegments(CCPACSWing* parent, CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr)
        {
            //assert(parent != NULL);
            m_parent = parent;
        }
        
        CPACSComponentSegments::~CPACSComponentSegments() {}
        
        CCPACSWing* CPACSComponentSegments::GetParent() const
        {
            return m_parent;
        }
        
        CTiglUIDManager& CPACSComponentSegments::GetUIDManager()
        {
            return *m_uidMgr;
        }
        
        const CTiglUIDManager& CPACSComponentSegments::GetUIDManager() const
        {
            return *m_uidMgr;
        }
        
        void CPACSComponentSegments::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read element componentSegment
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/componentSegment")) {
                tixihelper::TixiReadElements(tixiHandle, xpath + "/componentSegment", m_componentSegments, reinterpret_cast<CCPACSWingComponentSegments*>(this), m_uidMgr);
            }
            
        }
        
        void CPACSComponentSegments::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write element componentSegment
            tixihelper::TixiSaveElements(tixiHandle, xpath + "/componentSegment", m_componentSegments);
            
        }
        
        const std::vector<unique_ptr<CCPACSWingComponentSegment> >& CPACSComponentSegments::GetComponentSegments() const
        {
            return m_componentSegments;
        }
        
        std::vector<unique_ptr<CCPACSWingComponentSegment> >& CPACSComponentSegments::GetComponentSegments()
        {
            return m_componentSegments;
        }
        
    }
}
