#include "BirdDataView.h"

#include <imgui.h>
#include <ImGuiJsonDrawer.h>
#include <PathManager.h>

#include "../Global/Globals.h"
#include "../Signals/ChangeBirdSignal.h"

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
            m_editingBirdKey = std::string(buffer);
        }

        renderJson(bird);

        if (ImGui::Button("Save"))
        {
            if (m_editingBirdKey != currentKey)
            {
                // Rename key in json
                m_json[m_editingBirdKey] = bird;
                m_json.erase(currentKey);
            }

            std::cout << m_json.dump(4) << std::endl;
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
}

void BirdDataView::renderJson(nlohmann::ordered_json& json, const std::string& path)
{
    std::vector<std::string> priority = { "obj_name", "texture" };
    std::map<std::string, std::string> dropDowns = {
        { "obj_name", PathManager::getObjFolderPath()},
        { "texture", PathManager::getTexturesFolderPath()},
    };

    // Render prioritized fields first
    for ( auto& [key, path] : dropDowns)
    {
        if (json.contains(key))
        {
            std::string fullPath = path.empty() ? key : path + "." + key;
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
