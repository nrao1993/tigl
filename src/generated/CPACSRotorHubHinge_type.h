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

#pragma once

#include <string>
#include <cctype>

#include "CTiglError.h"
#include "to_string.h"

namespace tigl
{
    namespace generated
    {
        // This enum is used in:
        // CPACSRotorHubHinge
        
        // generated from /xsd:schema/xsd:complexType[740]/xsd:complexContent/xsd:extension/xsd:all/xsd:element[4]/xsd:simpleType
        enum CPACSRotorHubHinge_type
        {
            flap,
            pitch,
            leadLag
        };
        
        inline std::string CPACSRotorHubHinge_typeToString(const CPACSRotorHubHinge_type& value)
        {
            switch(value) {
            case flap: return "flap";
            case pitch: return "pitch";
            case leadLag: return "leadLag";
            default: throw CTiglError("Invalid enum value \"" + std_to_string(static_cast<int>(value)) + "\" for enum type CPACSRotorHubHinge_type");
            }
        }
        inline CPACSRotorHubHinge_type stringToCPACSRotorHubHinge_type(const std::string& value)
        {
            struct ToLower { std::string operator()(std::string str) { for (std::size_t i = 0; i < str.length(); i++) { str[i] = std::tolower(str[i]); } return str; } } toLower;
            if (toLower(value) == "flap") { return flap; }
            if (toLower(value) == "pitch") { return pitch; }
            if (toLower(value) == "leadlag") { return leadLag; }
            throw CTiglError("Invalid string value \"" + value + "\" for enum type CPACSRotorHubHinge_type");
        }
    }
    
    // Aliases in tigl namespace
    #ifdef HAVE_CPP11
    using ECPACSRotorHubHinge_type = generated::CPACSRotorHubHinge_type;
    #else
    typedef generated::CPACSRotorHubHinge_type ECPACSRotorHubHinge_type;
    #endif
    using generated::flap;
    using generated::pitch;
    using generated::leadLag;
}
