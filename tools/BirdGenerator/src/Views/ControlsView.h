#pragma once
#include "IView.h"
#include <json.hpp>
#include <SignalHandler.h>
#include <Signal.h>
#include <glm/vec2.hpp>

#include "../Signals/JsonUpdatedSignal.h"
#include "../Managers/JsonManager.h"

/// <summary>
/// Has all the controls of the tool like;
/// Generation, selection, adding new instances and uploads
/// </summary>
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