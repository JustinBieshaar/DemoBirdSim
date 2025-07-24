#pragma once
#include <json.hpp>
#include <SignalHandler.h>

#include "../Signals/JsonUpdatedSignal.h"

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

	nlohmann::ordered_json m_birdsJson;
	nlohmann::ordered_json m_templateJson;
};