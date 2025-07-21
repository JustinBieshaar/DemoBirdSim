#pragma once
#include "IView.h"
#include <json.hpp>
#include <SignalHandler.h>
#include "../Signals/JsonUpdatedSignal.h"
#include <Event.h>

class GenerationView : public IView
{
public:
	GenerationView(std::shared_ptr<SignalHandler> signalHander, nlohmann::json json);

	// Inherited via IView
	void render() override;

private:
	void onJsonUpdated(Event<JsonUpdatedSignal>& signal);

	nlohmann::json m_json;

	// Inherited via IView
	void init() override;
};