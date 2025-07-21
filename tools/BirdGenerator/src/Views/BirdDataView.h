#pragma once
#include "IView.h"
#include <json.hpp>
#include <string>

class BirdDataView : public IView
{
public:
	BirdDataView(std::shared_ptr<SignalHandler> signalHandler, nlohmann::ordered_json json);
	void render();

	// Inherited via IView
	void init() override;

private:

	void renderJson(nlohmann::ordered_json& json, const std::string& path = "");

	nlohmann::ordered_json m_json;
	std::string m_editingBirdKey;
};