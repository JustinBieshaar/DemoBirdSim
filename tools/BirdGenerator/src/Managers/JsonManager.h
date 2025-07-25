#pragma once
#include <json.hpp>
#include <SignalHandler.h>

#include "../Signals/JsonUpdatedSignal.h"

/// <summary>
/// Holds all data regarding the json's used in this tool.
/// This so no new instances are being fetched at random places, but remains ownership here.
/// 
/// We are using ordered jsons to keep the order of the jsons based on how they are constructed.
/// Not based on each key name which nlohman::json does. ;)
/// </summary>
class JsonManager
{
public:
	JsonManager(std::shared_ptr<Signals::SignalHandler> signalHandler);

	void modifyBirdsJson(const nlohmann::json& json, bool log = true);

	void reset();

	inline nlohmann::ordered_json& getBirdsJson() { return m_birdsJson; }
	inline nlohmann::ordered_json& getTemplateJson() { return m_templateJson; }

private:

	std::shared_ptr<Signals::SignalHandler> m_signalHandler;

	// used jsons.
	nlohmann::ordered_json m_birdsJson;
	nlohmann::ordered_json m_templateJson;
};