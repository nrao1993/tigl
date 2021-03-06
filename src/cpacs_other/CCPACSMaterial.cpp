/* 
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2013-05-28 Martin Siggel <Martin.Siggel@dlr.de>
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "CCPACSMaterial.h"

#include "CTiglError.h"
#include "CTiglLogging.h"

namespace tigl
{

CCPACSMaterial::CCPACSMaterial()
    : isvalid(false) { }

void CCPACSMaterial::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
{
    generated::CPACSMaterialDefinition::ReadCPACS(tixiHandle, xpath);

    if (m_compositeUID_choice1) {
        is_composite = true;
    } else if (m_materialUID_choice2) {
        is_composite = false;
    } else {
        throw CTiglError("Neither materialUID nor compositeUID specified in " + xpath, TIGL_ERROR);
    }

    isvalid = true;
}

void CCPACSMaterial::Invalidate()
{
    isvalid = false;
}

bool CCPACSMaterial::isComposite() const
{
    return is_composite;
}

void CCPACSMaterial::SetComposite(bool composite)
{
    is_composite = composite;
}

bool CCPACSMaterial::IsValid() const
{
    return isvalid;
}

const std::string& CCPACSMaterial::GetUID() const
{
    if (isComposite())
        return *GetCompositeUID_choice1();
    else
        return *GetMaterialUID_choice2();
}

void CCPACSMaterial::SetUID(const std::string& uid)
{
    if (isComposite())
        return SetCompositeUID_choice1(uid);
    else
        return SetMaterialUID_choice2(uid);
}

} // namespace tigl
