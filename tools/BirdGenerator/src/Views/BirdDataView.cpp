#include "BirdDataView.h"

#include <imgui.h>

BirdDataView::BirdDataView(std::shared_ptr<SignalHandler> signalHandler) : IView(signalHandler)
{
}

void BirdDataView::render()
{
	ImGui::Begin("BirdData");
}

void BirdDataView::init()
{
	// subscribe signals
}
