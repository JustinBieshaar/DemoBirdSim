#pragma once
#include "IView.h"

class BirdDataView : public IView
{
public:
	BirdDataView(std::shared_ptr<SignalHandler> signalHandler);
	void render();

	// Inherited via IView
	void init() override;
};