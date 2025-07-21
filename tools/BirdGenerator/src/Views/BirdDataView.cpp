#include "BirdDataView.h"

#include <imgui.h>

BirdDataView::BirdDataView(std::shared_ptr<SignalHandler> signalHandler, nlohmann::json json) : IView(signalHandler), m_json(json)
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
        nlohmann::json& bird = it.value();

        // Initialize editable key once
        if (m_editingBirdKey.empty())
        {
            m_editingBirdKey = currentKey;
        }

        char buffer[256];
        std::strncpy(buffer, m_editingBirdKey.c_str(), sizeof(buffer));
        buffer[sizeof(buffer) - 1] = '\0';

        if (ImGui::InputText("name", buffer, sizeof(buffer)))
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
	// subscribe signals
}

void BirdDataView::renderJson(nlohmann::json& json, const std::string& path)
{
    std::vector<std::string> priority = { "obj_name", "texture" };

    // Render prioritized fields first
    for (const auto& key : priority)
    {
        if (json.contains(key))
        {
            std::string fullPath = path.empty() ? key : path + "." + key;
            renderJsonField(key, json[key]);
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
            renderJsonField(key, value);
        }
    }
}

bool BirdDataView::renderJsonField(const std::string& fieldLabel, nlohmann::json& json)
{
    if (json.is_string())
    {
        std::string val = json.get<std::string>();
        char buffer[256];
        std::strncpy(buffer, val.c_str(), sizeof(buffer));
        buffer[sizeof(buffer) - 1] = '\0'; // Ensure null-termination
        if (ImGui::InputText(fieldLabel.c_str(), buffer, sizeof(buffer)))
        {
            json = std::string(buffer);
            return true;
        }
    }
    else if (json.is_number_float())
    {
        float val = json.get<float>();
        if (ImGui::InputFloat(fieldLabel.c_str(), &val))
        {
            json = val;
            return true;
        }
    }
    else if (json.is_number_integer())
    {
        int val = json.get<int>();
        if (ImGui::InputInt(fieldLabel.c_str(), &val))
        {
            json = val;
            return true;
        }
    }
    else if (json.is_boolean())
    {
        bool val = json.get<bool>();
        if (ImGui::Checkbox(fieldLabel.c_str(), &val))
        {
            json = val;
            return true;
        }
    }

    // todo: handle other types (arrays, nulls, etc.)
    return false;
}
