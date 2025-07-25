#pragma once
#include "IView.h"
#include <json.hpp>
#include <string>
#include "../Managers/JsonManager.h"

/// <summary>
/// Renders all data of the current inspecting bird.
/// </summary>
class BirdDataView : public IView
{
public:
	BirdDataView(std::shared_ptr<Signals::SignalHandler> signalHandler, JsonManager* jsonManager);
	void render();

	// Inherited via IView
	void init() override;

private:

	void renderJson(nlohmann::ordered_json& json, const std::string& path = "");

	JsonManager* m_jsonManager;
	std::string m_name;
	std::string m_editingBirdKey;
};