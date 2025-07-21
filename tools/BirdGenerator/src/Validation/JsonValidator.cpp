#include "JsonValidator.h"

static void mergeWithTemplate(nlohmann::ordered_json& target, const nlohmann::ordered_json& tmpl)
{
    for (auto& [key, tmplValue] : tmpl.items())
    {
        if (!target.contains(key))
        {
            // Add missing key with template value
            target[key] = tmplValue;
        }
        else if (tmplValue.is_object() && target[key].is_object())
        {
            // Recursively merge nested objects
            mergeWithTemplate(target[key], tmplValue);
        }
    }
}

void JsonValidator::validate(nlohmann::ordered_json& json, nlohmann::ordered_json& templateJson)
{
    if (!templateJson.contains("default"))
        return;

    const auto& defaultTemplate = templateJson.at("default");

    for (auto& [birdName, birdData] : json.items())
    {
        mergeWithTemplate(birdData, defaultTemplate);
    }
}