#pragma once
#include <json.hpp>
#include <string>
#include <StringUtils.h>

// Potentially move this to a dedicated json-utils library. But for now this is fine as only this factory
// library uses it.

namespace JsonUtils
{
    /// <summary>
    /// Infers the C++ type name of a JSON value and returns it as a string.
    /// This does not actually look up a field by key but assumes the value is passed in.
    /// </summary>
	std::string getJsonFieldTypeToString(std::string key, nlohmann::ordered_json& json)
	{
        std::string returnType;

        // Identify the JSON value's type and map it to a C++ type string
        if (json.is_string()) returnType = "std::string";
        else if (json.is_number_integer()) returnType = "int";
        else if (json.is_number_unsigned()) returnType = "unsigned int";
        else if (json.is_number_float()) returnType = "float";
        else if (json.is_boolean()) returnType = "bool";
        else returnType = "ERR_TYPE_NOT_SUPPORTED"; // Unknown or unsupported type

        // Could be used to generate getter method name, e.g. getHealth, getName, etc.
        std::string methodName = "get" + StringUtils::toPascalCase(key);

        return returnType;
	}

   /// <summary>
   /// Converts a JSON value into a valid C++ literal (as a string).
   /// For example: true -> "true", "hello" -> "\"hello\"", 5.0 -> "5.0"
   /// </summary>
    std::string getJsonFieldValueToString(nlohmann::ordered_json& json)
    {
        std::string returnValue;

        // Convert the JSON value to a string representing C++ source code
        if (json.is_string())
        {
            returnValue = "\"" + json.get<std::string>() + "\""; // Wrap string with quotes
        }
        else if (json.is_boolean())
        {
            returnValue = json.get<bool>() ? "true" : "false";   // Convert to "true" or "false"
        }
        else if (json.is_number())
        {
            returnValue = json.dump(); // Directly converts number to string
        }
        else
        {
            returnValue = "{}"; // Fallback for unsupported or complex types
        }

        return returnValue;
    }
}