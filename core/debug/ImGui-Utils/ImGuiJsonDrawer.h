#pragma once
#include <json.hpp>
#include <imgui.h>
#include <string>
#include <filesystem>

namespace ImGuiJsonDrawer
{
	bool drawJsonValue(const std::string& key, nlohmann::ordered_json& json)
	{
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", key.c_str());
        ImGui::SameLine();
        ImGui::PushItemWidth(100); // fixed size

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

    bool drawJsonDropdown(const std::string& key, nlohmann::ordered_json& json, const std::vector<std::string>& options)
    {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", key.c_str());
        ImGui::SameLine();

        std::string inputId = "##" + key;
        std::string current = json.is_string() ? json.get<std::string>() : "";

        bool changed = false;
        if (ImGui::BeginCombo(inputId.c_str(), current.c_str()))
        {
            for (const auto& option : options)
            {
                bool isSelected = (option == current);
                if (ImGui::Selectable(option.c_str(), isSelected))
                {
                    json = option;
                    changed = true;
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        return changed;
    }

    bool drawJsonDropdownBasedOnFolderPath(const std::string& key, nlohmann::ordered_json& json, const std::string& folder)
    {
        std::vector<std::string> objNames;
        std::filesystem::path fullPath = std::filesystem::current_path() / folder;

        if (std::filesystem::exists(fullPath) && std::filesystem::is_directory(fullPath))
        {
            for (const auto& entry : std::filesystem::directory_iterator(fullPath))
            {
                if (entry.is_regular_file())
                    objNames.push_back(entry.path().filename().string());
            }
        }
        else
        {
            std::cerr << "Directory not found: " << fullPath << std::endl;
        }

        return ImGuiJsonDrawer::drawJsonDropdown(key, json, objNames);
    }
}