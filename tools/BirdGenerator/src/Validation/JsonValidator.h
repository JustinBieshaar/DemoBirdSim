#pragma once
#include <json.hpp>

/// <summary>
/// Validates if the birds json is having all entries as described in template. (resources/config/template.json)
/// </summary>
class JsonValidator
{
public:
	/// <summary>
	/// Validate json by checking all entries using the template json.
	/// If a field from template is missing, it will add it automatically.
	/// </summary>
	static bool validate(nlohmann::ordered_json& json, nlohmann::ordered_json& templateJson);
};