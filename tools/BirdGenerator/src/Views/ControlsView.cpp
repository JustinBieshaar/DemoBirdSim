#include "ControlsView.h"
#include <imgui.h>
#include <PathManager.h>
#include <BirdsFactory.h>

#include "../Signals/ChangeBirdSignal.h"
#include "../Global/Globals.h"

#include <iostream>

ControlsView::ControlsView(std::shared_ptr<SignalHandler> signalHander, nlohmann::ordered_json json) : IView(signalHander), m_json(json)
{
}

void ControlsView::init()
{
    m_signalHandler->observeEvent<JsonUpdatedSignal>(
        [this](Event<JsonUpdatedSignal>& event) { onJsonUpdated(event); }
    );
}

void ControlsView::render()
{
    ImGui::SetNextWindowPos(ImVec2(Window_Width - m_windowSize.x, Window_Height - m_windowSize.y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(m_windowSize.x, m_windowSize.y), ImGuiCond_Always);

    ImGui::Begin("Controls");
    if (ImGui::Button("Generate"))
    {
        PathManager::setResourceRoot(_SOLUTIONDIR);

        std::cout << "generating with json: " << m_json << "\n";
        BirdsFactory::generateBirds(m_json);
    }

    if (ImGui::Button("Next"))
    {
        m_signalHandler->invokeEvent(ChangeBirdSignal{ "robin", m_json["robin"] });
    }

    if (ImGui::Button("Add new bird"))
    {
        // add logic
    }

    ImGui::End();
}

void ControlsView::onJsonUpdated(Event<JsonUpdatedSignal>& signal)
{
    m_json = signal.data.json;
}

