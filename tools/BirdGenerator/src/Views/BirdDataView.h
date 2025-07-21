#pragma once
#include "IView.h"
#include <json.hpp>
#include <string>

class BirdDataView : public IView
{
public:
	BirdDataView(std::shared_ptr<SignalHandler> signalHandler, nlohmann::json json);
	void render();

	// Inherited via IView
	void init() override;

private:

	void renderJson(nlohmann::json& json, const std::string& path = "");
	bool renderJsonField(const std::string& fieldLabel, nlohmann::json& json);

	nlohmann::json m_json;
	std::string m_editingBirdKey;
};