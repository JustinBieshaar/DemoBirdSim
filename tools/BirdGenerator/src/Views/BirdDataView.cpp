#include "BirdDataView.h"

#include <imgui.h>
#include <ImGuiJsonDrawer.h>
#include <PathManager.h>
#include <fstream>

#include "../Global/Globals.h"
#include "../Signals/ChangeBirdSignal.h"
#include "../Debug/LogChannels.h"
#include "../Signals/JsonUpdatedSignal.h"

BirdDataView::BirdDataView(std::shared_ptr<SignalHandler> signalHandler, nlohmann::ordered_json json) : IView(signalHandler), m_json(json), m_editingBirdKey(DefaultBird)
{
}

void BirdDataView::render()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

    ImGui::Begin("BirdData", nullptr,
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |  ImGuiWindowFlags_NoCollapse);

    if (!m_json.empty())
    {
        // Get first bird entry

        auto it = m_json.find(m_editingBirdKey);
        if (it == m_json.end())
        {
            ImGui::End();
            return;
        }

        std::string currentKey = it.key();
        nlohmann::ordered_json& bird = it.value();

        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", "name");
        ImGui::SameLine();

        std::string inputId = "##name";  // Unique but invisible label

        char buffer[256];
        std::strncpy(buffer, m_editingBirdKey.c_str(), sizeof(buffer));
        buffer[sizeof(buffer) - 1] = '\0';

        if (ImGui::InputText(inputId.c_str(), buffer, sizeof(buffer)))
        {
            m_name = std::string(buffer);
        }

        renderJson(bird);

        if (ImGui::Button("Save"))
        {
            if (m_name != currentKey)
            {
                // Rename key in json
                m_json[m_name] = bird;
                m_json.erase(currentKey); // todo: try and find a way without erasing or reordering to remain the original order.
                m_editingBirdKey = m_name;
            }

            try
            {
                std::ofstream outFile(PathManager::getConfigPath("birds.json"));
                if (!outFile)
                {
                    throw;
                }
                outFile << m_json.dump(4);
                DataLogChannel.log("Saved successfully!");

                m_signalHandler->invokeEvent(JsonUpdatedSignal{ m_json });
                m_signalHandler->invokeEvent(ChangeBirdSignal{ m_editingBirdKey, m_json[m_editingBirdKey]}); // invoking change bird to same instance to refresh
            }
            catch (const std::exception& e)
            {
                DataLogChannel.logError("Failed to save... Exception (" + std::string(e.what()) + ")");
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Delete"))
        {
            if (m_json.size() <= 1)
            {
                DataLogChannel.logError("This is the last item, we can't delete it.");
                ImGui::End();
                return;
            }

            int index = -1;
            int counter = 0;
            for (auto it = m_json.begin(); it != m_json.end(); ++it, ++counter)
            {
                if (it.key() == currentKey)
                {
                    index = counter;
                    break;
                }
            }

            // fix edge case if you delete the last one.
            if (index > 0 && index == m_json.size() - 1)
            {
                index--;
            }

            // Rename key in json
            m_json.erase(currentKey);

            std::ofstream outFile(PathManager::getConfigPath("birds.json"));
            if (!outFile)
            {
                DataLogChannel.logError("Failed to delete..!");
                return;
            }
            outFile << m_json.dump(4);
            DataLogChannel.log("Deleted " + m_editingBirdKey + " successfully!");

            auto refreshSelectedBirdJsonKey = std::next(m_json.begin(), 0).key();
            auto refreshSelectedBirdJsonValue = std::next(m_json.begin(), 0).value();

            m_signalHandler->invokeEvent(JsonUpdatedSignal{ m_json });
            m_signalHandler->invokeEvent(ChangeBirdSignal{ refreshSelectedBirdJsonKey, refreshSelectedBirdJsonValue }); // invoking change bird to same instance to refresh
        }
    }

    ImGui::End();
}

void BirdDataView::init()
{
	// subscribe signals (if needed)
    m_signalHandler->observeEvent<ChangeBirdSignal>(
        [this](Event<ChangeBirdSignal>& event) { m_editingBirdKey = event.data.name; }
    );

    m_signalHandler->observeEvent<JsonUpdatedSignal>(
        [this](Event<JsonUpdatedSignal>& event) { m_json = event.data.json; }
    );
}

void BirdDataView::renderJson(nlohmann::ordered_json& json, const std::string& path)
{
    std::vector<std::string> priority = { "obj_name", "texture" };
    std::map<std::string, std::string> dropDowns = {
        { "obj_name", PathManager::getObjFolderPath() },
        { "texture", PathManager::getTexturesFolderPath()},
    };

    // Render prioritized fields first
    for ( auto& [key, path] : dropDowns)
    {
        if (json.contains(key))
        {
            ImGuiJsonDrawer::drawJsonDropdownBasedOnFolderPath(key, json[key], path);
        }
    }

    // Then render everything else
    for (auto& [key, value] : json.items())
    {
        if (std::find(priority.begin(), priority.end(), key) != priority.end())
            continue;

        std::string fullPath = path.empty() ? key : path + "." + key;

        if (value.is_object())
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once); // only opens it once at the start so it can be closed. 
            if (ImGui::TreeNode(key.c_str()))
            {
                renderJson(value, fullPath);
                ImGui::TreePop();
            }
        }
        else
        {
            ImGuiJsonDrawer::drawJsonValue(key, value);
        }
    }
}
