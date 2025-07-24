#include "JsonManager.h"
#include <ObjLoader.h>
#include "../Validation/JsonValidator.h"
#include "../Debug/BirdGenLogChannels.h"

JsonManager::JsonManager(std::shared_ptr<Signals::SignalHandler> signalHandler) : m_signalHandler(signalHandler)
{
    reset();
}

void JsonManager::modifyBirdsJson(const nlohmann::json& json, bool log)
{
    // Save updated birds.json back to file
    std::ofstream outFile(PathManager::getConfigPath("birds.json"));
    if (!outFile)
    {
        JsonLogChannel.logError("Failed to write birds.json..");
        return;
    }
    outFile << json.dump(4);

    if (log)
    {
        JsonLogChannel.log("Saved successfully!");
    }

    // Update internal state and notify listeners
    m_signalHandler->invokeEvent(JsonUpdatedSignal{ json });
}

void JsonManager::reset()
{
    // Load birds.json
    std::ifstream input(PathManager::getConfigPath("birds.json"));
    if (!input)
    {
        JsonLogChannel.logError("Failed to open birds.json..");
        return;
    }

    input >> m_birdsJson;

    // Load template.json
    std::ifstream templateInput(PathManager::getConfigPath("template.json"));
    if (!templateInput)
    {
        JsonLogChannel.logError("Failed to open template.json..");
        return;
    }

    nlohmann::ordered_json templateJson;
    templateInput >> templateJson;

    // Validate and update birds json
    if (JsonValidator::validate(m_birdsJson, templateJson))
    {
        modifyBirdsJson(m_birdsJson, false);
        JsonLogChannel.log("Loaded and validated successfully.");
    }
    else
    {
        JsonLogChannel.log("Loaded successfully!");
    }
}
