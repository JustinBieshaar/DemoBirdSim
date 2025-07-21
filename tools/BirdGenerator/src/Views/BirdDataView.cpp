#include "BirdDataView.h"

#include <imgui.h>
#include <ImGuiJsonDrawer.h>

BirdDataView::BirdDataView(std::shared_ptr<SignalHandler> signalHandler, nlohmann::ordered_json json) : IView(signalHandler), m_json(json)
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
        auto it = m_json.begin();
        std::string currentKey = it.key();
        nlohmann::ordered_json& bird = it.value();

        // Initialize editable key once
        if (m_editingBirdKey.empty())
        {
            m_editingBirdKey = currentKey;
        }

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
}

void BirdDataView::renderJson(nlohmann::ordered_json& json, const std::string& path)
{
    std::vector<std::string> priority = { "obj_name", "texture" };

    // Render prioritized fields first
    for (const auto& key : priority)
    {
        if (json.contains(key))
        {
            std::string fullPath = path.empty() ? key : path + "." + key;
            ImGuiJsonDrawer::drawJsonValue(key, json[key]);
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
