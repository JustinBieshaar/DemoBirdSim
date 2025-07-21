#include "Console.h"
#include <iostream>
#include <imgui.h>

void Console::log(const std::string& channel, const std::string& message, const Color& color)
{
    std::lock_guard<std::mutex> lock(s_mutex);

    // Log to std::cout
    std::cout << "[" << channel << "] " << message << std::endl;

    // Store for ImGui rendering
    s_logs.push_back(LogEntry{ InfoStatusStr, m_infoColor, channel, message, color });
}

void Console::logErr(const std::string& channel, const std::string& message, const Color& color)
{
    std::lock_guard<std::mutex> lock(s_mutex);

    // Log to std::cout
    std::cerr << "[" << channel << "] " << message << std::endl;

    // Store for ImGui rendering
    s_logs.push_back(LogEntry{ WarningStatusStr, m_warningColor, channel, message , color });
}

void Console::logWarning(const std::string& channel, const std::string& message, const Color& color)
{
    std::lock_guard<std::mutex> lock(s_mutex);

    // Log to std::cout
    std::cout << "[" << channel << "] " << message << std::endl;

    // Store for ImGui rendering
    s_logs.push_back(LogEntry{ ErrorStatusStr, m_errorColor, channel, message, color });
}

const std::vector<LogEntry>& Console::getLogEntries()
{
    return s_logs;
}

void Console::clear()
{
    std::lock_guard<std::mutex> lock(s_mutex);
    s_logs.clear();
}

void Console::drawImGui()
{
    if (ImGui::Begin("Console"))
    {
        for (const auto& entry : s_logs)
        {
            ImVec4 statusColor(entry.statusColor.r / 255.0f, entry.statusColor.g / 255.0f, entry.statusColor.b / 255.0f, 1.0f);
            ImGui::PushStyleColor(ImGuiCol_Text, statusColor);
            ImGui::Text("[%s] ", entry.status.c_str());
            ImGui::PopStyleColor();

            ImGui::SameLine();

            ImVec4 color(entry.color.r / 255.0f, entry.color.g / 255.0f, entry.color.b / 255.0f, 1.0f);
            ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::Text("[%s] %s", entry.channel.c_str(), entry.message.c_str());
            ImGui::PopStyleColor();
        }

        if (ImGui::Button("Clear")) clear();
    }
    ImGui::End();
}