#pragma once
#include "IView.h"
#include <json.hpp>
#include <SignalHandler.h>
#include "../Signals/JsonUpdatedSignal.h"
#include <Event.h>
#include <glm/vec2.hpp>

class ControlsView : public IView
{
public:
	ControlsView(std::shared_ptr<SignalHandler> signalHander, nlohmann::ordered_json json);

	// Inherited via IView
	void render() override;

private:
	void onJsonUpdated(Event<JsonUpdatedSignal>& signal);

	nlohmann::ordered_json m_json;
	std::string m_currentActiveBird;

	// Inherited via IView
	void init() override;

	glm::vec2 m_windowSize = glm::vec2{ 200, 100 };
};