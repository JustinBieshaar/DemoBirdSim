#include "ControlsView.h"
#include <imgui.h>
#include <ImGuiFileDialog.h>
#include <PathManager.h>
#include <BirdsFactory.h>
#include <vector>
#include <fstream>

#include "../Signals/ChangeBirdSignal.h"
#include "../Global/Globals.h"
#include "../Debug/BirdGenLogChannels.h"

#include <iostream>

ControlsView::ControlsView(std::shared_ptr<Signals::SignalHandler> signalHander, JsonManager* jsonManager) : IView(signalHander), m_jsonManager(jsonManager)
{
}

void ControlsView::init()
{
    m_signalHandler->observeSignal<ChangeBirdSignal>(
        [this](Signals::Signal<ChangeBirdSignal>& event) { m_currentActiveBird = event.data.name; }
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

        auto json = m_jsonManager->getBirdsJson();
        BirdsFactory::generateBirds(json);

        BirdLogChannel.log("Generated successfully!");
    }

    ImGui::Text("Select bird");

    if (ImGui::ArrowButton("Previous", ImGuiDir_Left))
    {
        selectBird(-1);
    }

    ImGui::SameLine();

    if (ImGui::ArrowButton("Next", ImGuiDir_Right))
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
    // Get reference to the birds JSON data (assumed to be a map of birdName -> birdData)
    auto& json = m_jsonManager->getBirdsJson();

    // If JSON is empty, there are no birds to select
    if (json.empty()) return;

    // Build a list of all bird keys (names) from the JSON
    std::vector<std::string> keys;
    for (auto& [key, _] : json.items())
        keys.push_back(key);

    // Try to find the index of the currently active bird in the keys list
    auto it = std::find(keys.begin(), keys.end(), m_currentActiveBird);
    size_t index = (it != keys.end()) ? std::distance(keys.begin(), it) : 0;

    // Compute the new index based on direction, with wrap-around logic
    int newIndex = static_cast<int>(index) + direction;
    if (newIndex < 0)
        newIndex = static_cast<int>(keys.size()) - 1; // wrap to last element
    else if (newIndex >= static_cast<int>(keys.size()))
        newIndex = 0; // wrap to first element

    // Get the bird name at the new index
    const std::string& nextBirdName = keys[newIndex];

    // Update the currently active bird
    m_currentActiveBird = nextBirdName;

    // Notify the system that the bird has changed
    m_signalHandler->invokeSignal(ChangeBirdSignal{ nextBirdName, json[nextBirdName] });
}

void ControlsView::addNewBird()
{
    auto& json = m_jsonManager->getBirdsJson();
    auto& templateJson = m_jsonManager->getTemplateJson();

    // Load the template entry
    const std::string baseName = "new";
    int index = 0;
    std::string newName = baseName;

    // Ensure a unique name
    while (json.contains(newName))
    {
        newName = baseName + std::to_string(index++);
    }

    // Add a new entry based on the template
    if (templateJson.contains("new"))
    {
        json[newName] = templateJson["new"];
        m_currentActiveBird = newName;

        m_jsonManager->modifyBirdsJson(json);
        m_signalHandler->invokeSignal(ChangeBirdSignal{ newName, json[newName] });

        ControlsLogChannel.log("new bird (" + newName + ") has been added!");
    }
    else
    {
        ControlsLogChannel.logError("Template missing 'default' key");
    }
}

