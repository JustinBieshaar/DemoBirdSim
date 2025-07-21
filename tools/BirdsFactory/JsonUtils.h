#pragma once
#include <json.hpp>
#include <string>
#include <StringUtils.h>

// Potentially move this to a dedicated json-utils library. But for now this is fine as only this factory
// library uses it.

namespace JsonUtils
{
	std::string getJsonFieldTypeToString(std::string key, nlohmann::json& json)
	{
        std::string returnType;

        if (json.is_string()) returnType = "std::string";
        else if (json.is_number_integer()) returnType = "int";
        else if (json.is_number_unsigned()) returnType = "unsigned int";
        else if (json.is_number_float()) returnType = "float";
        else if (json.is_boolean()) returnType = "bool";
        else returnType = "ERR_TYPE_NOT_SUPPORTED"; // Fallback or unknown

        std::string methodName = "get" + StringUtils::toPascalCase(key);
        return returnType;
	}

    std::string getJsonFieldValueToString(nlohmann::json& json)
    {
        std::string returnValue;

        // Convert JSON value to valid C++ code
        if (json.is_string())
        {
            returnValue = "\"" + json.get<std::string>() + "\"";
        }
        else if (json.is_boolean())
        {
            returnValue = json.get<bool>() ? "true" : "false";
        }
        else if (json.is_number())
        {
            returnValue = json.dump();  // Already a valid number
        }
        else
        {
            returnValue = "{}"; // Fallback for unsupported types
        }

        return returnValue;
    }
}