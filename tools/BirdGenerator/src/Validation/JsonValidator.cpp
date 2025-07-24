#include "JsonValidator.h"

static bool mergeWithTemplate(nlohmann::ordered_json& target, const nlohmann::ordered_json& tmpl)
{
    bool mergedValues = false;
    for (auto& [key, tmplValue] : tmpl.items())
    {
        if (!target.contains(key))
        {
            // Add missing key with template value
            target[key] = tmplValue;
            mergedValues = true;
        }
        else if (tmplValue.is_object() && target[key].is_object())
        {
            // Recursively merge nested objects
            mergedValues = mergeWithTemplate(target[key], tmplValue);
        }
    }

    return mergedValues;
}

bool JsonValidator::validate(nlohmann::ordered_json& json, nlohmann::ordered_json& templateJson)
{
    auto defaultTemplateIt = templateJson.begin();
    const std::string& templateKey = defaultTemplateIt.key();
    const nlohmann::ordered_json& templateValue = defaultTemplateIt.value();

    bool didRevalidate = false;
    for (auto& [birdName, birdData] : json.items())
    {
        didRevalidate |= mergeWithTemplate(birdData, templateValue);
    }

    return didRevalidate; // if true means we adjusted it.
}