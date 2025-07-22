#include "Console.h"
#include <iostream>
#include <imgui.h>

void Console::log(const std::string& channel, const std::string& message, const Color& color)
{
    logInternal(InfoStatusStr, m_infoColor, channel, message, color);
}

void Console::logWarning(const std::string& channel, const std::string& message, const Color& color)
{
    logInternal(WarningStatusStr, m_errorColor, channel, message, color);
}

void Console::logError(const std::string& channel, const std::string& message, const Color& color)
{
    logInternal(ErrorStatusStr, m_errorColor, channel, message, color);
}

void Console::logInternal(const std::string& statusMessage, const Color& statusColor, const std::string& channel, const std::string& message, const Color& color)
{
    std::lock_guard<std::mutex> lock(s_logMutex);

    // Log to std::cout
    std::cerr << "[" << channel << "] " << message << std::endl;

    // Store for ImGui rendering
    s_pendingLogs.push(LogEntry{ statusMessage, statusColor, channel, message , color });

    m_scrollDown = true; // mark scroll down
}

void Console::flushPendingLogs()
{
    std::lock_guard<std::mutex> lock(s_logMutex);

    while (!s_pendingLogs.empty())
    {
        s_logs.push_back(std::move(s_pendingLogs.front()));
        s_pendingLogs.pop();
        m_scrollDown = true;
    }
}

const std::vector<LogEntry>& Console::getLogEntries()
{
    return s_logs;
}

void Console::clear()
{
    std::lock_guard<std::mutex> lock(s_logMutex);
    s_logs.clear();
}

void Console::drawImGui()
{
    if (ImGui::Begin("Console"))
    {
        flushPendingLogs();

        ImGui::BeginChild("ConsoleScrollRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);

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

        if (m_scrollDown && m_autoScrollEnabled)
        {
            ImGui::SetScrollHereY(1.0f);
            m_scrollDown = false;
        }

        ImGui::EndChild(); // End of scrollable region

        // 2. Buttons below scroll
        if (ImGui::Button("Clear")) clear();

        ImGui::SameLine();

        ImGui::Checkbox("Auto Scroll", &m_autoScrollEnabled);
    }
    ImGui::End();
}