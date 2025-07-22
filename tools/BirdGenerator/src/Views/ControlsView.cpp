#include "ControlsView.h"
#include <imgui.h>
#include <ImGuiFileDialog.h>
#include <PathManager.h>
#include <BirdsFactory.h>
#include <vector>
#include <fstream>

#include "../Signals/ChangeBirdSignal.h"
#include "../Global/Globals.h"
#include "../Debug/LogChannels.h"

#include <iostream>

ControlsView::ControlsView(std::shared_ptr<SignalHandler> signalHander, nlohmann::ordered_json json) : IView(signalHander), m_json(json)
{
}

void ControlsView::init()
{
    m_signalHandler->observeEvent<JsonUpdatedSignal>(
        [this](Event<JsonUpdatedSignal>& event) { onJsonUpdated(event); }
    );
    m_signalHandler->observeEvent<ChangeBirdSignal>(
        [this](Event<ChangeBirdSignal>& event) { m_currentActiveBird = event.data.name; }
    );
}

void ControlsView::render()
{
    ImGui::SetNextWindowPos(ImVec2(Window_Width - m_windowSize.x, Window_Height - m_windowSize.y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(m_windowSize.x, m_windowSize.y), ImGuiCond_Always);

    ImGui::Begin("Controls", nullptr,
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    if (ImGui::Button("Generate"))
    {
        PathManager::setResourceRoot(_SOLUTIONDIR);

        std::cout << "generating with json: " << m_json << "\n";
        BirdsFactory::generateBirds(m_json);
    }

    if (ImGui::Button("< Previous"))
    {
        selectBird(-1);
    }
    ImGui::SameLine();

    if (ImGui::Button("Next >"))
    {
        selectBird(1);
    }

    if (ImGui::Button("Add new bird"))
    {
        addNewBird();
    }

    ImGui::Spacing();

    if (ImGui::Button("Upload obj file"))
    {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseObjFile", "Select .obj File", ".obj");
    }

    ImGui::Spacing();

    if (ImGui::Button("Upload texture"))
    {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseTextureFile", "Select Texture", ".png,.jpeg,.jpg");
    }

    // Render dialog
    if (ImGuiFileDialog::Instance()->Display("ChooseObjFile"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();

            auto objsPath = PathManager::getObjFolderPath();
            std::filesystem::copy(filePath, objsPath + "/" + fileName, std::filesystem::copy_options::overwrite_existing);
            ControlsLogChannel.log("Uploaded OBJ: " + fileName);
        }
        ImGuiFileDialog::Instance()->Close();
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseTextureFile"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();

            auto texturesPath = PathManager::getTexturesFolderPath();
            std::filesystem::copy(filePath, texturesPath + "/" + fileName, std::filesystem::copy_options::overwrite_existing);
            ControlsLogChannel.log("Uploaded Texture: " + fileName);
        }
        ImGuiFileDialog::Instance()->Close();
    }

    ImGui::End();
}

void ControlsView::selectBird(int direction)
{
    if (m_json.empty()) return;

    std::vector<std::string> keys;
    for (auto& [key, _] : m_json.items())
        keys.push_back(key);

    // Find current index
    auto it = std::find(keys.begin(), keys.end(), m_currentActiveBird);
    size_t index = (it != keys.end()) ? std::distance(keys.begin(), it) : 0;

    // Compute new index with wrap-around
    int newIndex = static_cast<int>(index) + direction;
    if (newIndex < 0)
        newIndex = static_cast<int>(keys.size()) - 1;
    else if (newIndex >= static_cast<int>(keys.size()))
        newIndex = 0;

    const std::string& nextBirdName = keys[newIndex];
    m_currentActiveBird = nextBirdName;
    m_signalHandler->invokeEvent(ChangeBirdSignal{ nextBirdName, m_json[nextBirdName] });
}

void ControlsView::addNewBird()
{
    // Load the template entry
    const std::string baseName = "new";
    int index = 0;
    std::string newName = baseName;

    std::ifstream templateInput(PathManager::getConfigPath("template.json"));
    nlohmann::ordered_json templateJson;
    templateInput >> templateJson;

    // Ensure a unique name
    while (m_json.contains(newName))
    {
        newName = baseName + std::to_string(index++);
    }

    // Add a new entry based on the template
    if (templateJson.contains("new"))
    {
        m_json[newName] = templateJson["new"];
        m_currentActiveBird = newName;

        std::ofstream outFile(PathManager::getConfigPath("birds.json"));
        if (!outFile)
        {
            ControlsLogChannel.logError("Failed to write birds.json");
            return;
        }

        outFile << m_json.dump(4);

        m_signalHandler->invokeEvent(JsonUpdatedSignal{ m_json });
        m_signalHandler->invokeEvent(ChangeBirdSignal{ newName, m_json[newName] });

        ControlsLogChannel.log("new bird (" + newName + ") has been added!");
    }
    else
    {
        ControlsLogChannel.logError("Template missing 'default' key");
    }
}

void ControlsView::onJsonUpdated(Event<JsonUpdatedSignal>& signal)
{
    m_json = signal.data.json;
}

