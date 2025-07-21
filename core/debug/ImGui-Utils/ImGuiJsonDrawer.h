#pragma once
#include <json.hpp>
#include <imgui.h>
#include <string>

namespace ImGuiJsonDrawer
{
	bool drawJsonValue(const std::string& key, nlohmann::ordered_json& json)
	{
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", key.c_str());
        ImGui::SameLine();

        std::string inputId = "##" + key;  // Unique but invisible label

        if (json.is_string())
        {
            std::string val = json.get<std::string>();
            char buffer[256];
            std::strncpy(buffer, val.c_str(), sizeof(buffer));
            buffer[sizeof(buffer) - 1] = '\0';
            if (ImGui::InputText(inputId.c_str(), buffer, sizeof(buffer)))
            {
                json = std::string(buffer);
                return true;
            }
        }
        else if (json.is_number_float())
        {
            float val = json.get<float>();
            if (ImGui::InputFloat(inputId.c_str(), &val))
            {
                json = val;
                return true;
            }
        }
        else if (json.is_number_integer())
        {
            int val = json.get<int>();
            if (ImGui::InputInt(inputId.c_str(), &val))
            {
                json = val;
                return true;
            }
        }
        else if (json.is_boolean())
        {
            bool val = json.get<bool>();
            if (ImGui::Checkbox(inputId.c_str(), &val))
            {
                json = val;
                return true;
            }
        }

        return false;
	}
}