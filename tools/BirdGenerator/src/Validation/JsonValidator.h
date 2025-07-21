#pragma once
#include <json.hpp>

/// <summary>
/// Validates if the birds json is having all entries as described in template. (resources/config/template.json)
/// </summary>
class JsonValidator
{
public:
	static void validate(nlohmann::ordered_json& json, nlohmann::ordered_json& templateJson);
};