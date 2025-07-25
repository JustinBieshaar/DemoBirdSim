#pragma once
#include "IView.h"
#include <json.hpp>
#include <SignalHandler.h>
#include "../Signals/JsonUpdatedSignal.h"
#include <Signal.h>
#include <glm/vec2.hpp>
#include "../Managers/JsonManager.h"

class ControlsView : public IView
{
public:
	ControlsView(std::shared_ptr<Signals::SignalHandler> signalHander, JsonManager* jsonManager);

	// Inherited via IView
	void render() override;

private:
	void selectBird(int direction);
	void addNewBird();

	JsonManager* m_jsonManager;
	std::string m_currentActiveBird;

	// Inherited via IView
	void init() override;

	glm::vec2 m_windowSize = glm::vec2{ 200, 200 };
};