#include "JsonValidator.h"

static bool mergeWithTemplate(nlohmann::ordered_json& target, const nlohmann::ordered_json& tmpl)
{
    bool mergedValues = false;

    // Iterate over all key-value pairs in the template
    for (auto& [key, tmplValue] : tmpl.items())
    {
        if (!target.contains(key))
        {
            // If the key is missing in the target, add it from the template
            target[key] = tmplValue;
            mergedValues = true;
        }
        else if (tmplValue.is_object() && target[key].is_object())
        {
            // If both the template value and target value are objects,
            // recursively merge them to fill in missing nested fields
            mergedValues |= mergeWithTemplate(target[key], tmplValue);
        }
    }

    return mergedValues;
}

bool JsonValidator::validate(nlohmann::ordered_json& json, nlohmann::ordered_json& templateJson)
{
    // Get the root template key and value (assuming template is like: { "default": { ... } })
    auto defaultTemplateIt = templateJson.begin();

    const std::string& templateKey = defaultTemplateIt.key();
    const nlohmann::ordered_json& templateValue = defaultTemplateIt.value(); 

    bool didRevalidate = false;

    // Iterate through all top-level entries in the input JSON (e.g., all birds)
    for (auto& [birdName, birdData] : json.items())
    {
        // Merge missing values from the template into each item
        didRevalidate |= mergeWithTemplate(birdData, templateValue);
    }

    // Return whether any updates were made (true = structure changed)
    return didRevalidate;
}