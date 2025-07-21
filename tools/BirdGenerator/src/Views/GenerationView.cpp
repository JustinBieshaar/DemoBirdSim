#include "GenerationView.h"
#include <imgui.h>
#include <PathManager.h>
#include <BirdsFactory.h>

#include "../Signals/ChangeBirdSignal.h"

#include <iostream>

GenerationView::GenerationView(std::shared_ptr<SignalHandler> signalHander, nlohmann::json json) : IView(signalHander), m_json(json)
{
}

void GenerationView::init()
{
    m_signalHandler->observeEvent<JsonUpdatedSignal>(
        [this](Event<JsonUpdatedSignal>& event) { onJsonUpdated(event); }
    );
}

void GenerationView::render()
{
    ImGui::Begin("Testing");
    if (ImGui::Button("Generate"))
    {
        PathManager::setResourceRoot(_SOLUTIONDIR);

        std::cout << "generating with json: " << m_json << "\n";
        BirdsFactory::generateBirds(m_json);
    }

    if (ImGui::Button("Next"))
    {
        m_signalHandler->invokeEvent(ChangeBirdSignal{"robin", m_json["robin"]});
    }

    ImGui::End();
}

void GenerationView::onJsonUpdated(Event<JsonUpdatedSignal>& signal)
{
    m_json = signal.data.json;
}

