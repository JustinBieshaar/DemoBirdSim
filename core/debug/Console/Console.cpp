/*
* Yes, you are right...
* Console::Console looks a bit weird...
*/

#include "Console.h"
#include <iostream>
#include <imgui.h>

void Console::Console::log(const std::string& channel, const std::string& message, const Color& color)
{
    logInternal(InfoStatusStr, m_infoColor, channel, message, color);
}

void Console::Console::logWarning(const std::string& channel, const std::string& message, const Color& color)
{
    logInternal(WarningStatusStr, m_errorColor, channel, message, color);
}

void Console::Console::logError(const std::string& channel, const std::string& message, const Color& color)
{
    logInternal(ErrorStatusStr, m_errorColor, channel, message, color);
}

void Console::Console::logInternal(const std::string& statusMessage, const Color& statusColor, const std::string& channel, const std::string& message, const Color& color)
{
    std::lock_guard<std::mutex> lock(s_logMutex);

    // Log to standard error output (for real-time debug visibility)
    std::cerr << "[" << channel << "] " << message << std::endl;

    // Queue message for ImGui rendering
    s_pendingLogs.push(LogEntry{ statusMessage, statusColor, channel, message , color });

    // Flag for scrolling to bottom of console
    m_scrollDown = true;
}

void Console::Console::flushPendingLogs()
{
    std::lock_guard<std::mutex> lock(s_logMutex);

    while (!s_pendingLogs.empty())
    {
        s_logs.push_back(std::move(s_pendingLogs.front()));
        s_pendingLogs.pop();
        m_scrollDown = true;
    }
}

const std::vector<Console::LogEntry>& Console::Console::getLogEntries()
{
    return s_logs;
}

void Console::Console::clear()
{
    std::lock_guard<std::mutex> lock(s_logMutex);
    s_logs.clear();
}

void Console::Console::drawImGui()
{
    if (ImGui::Begin("Console"))
    {
        // Move queued logs into main log list
        flushPendingLogs();

        // Begin scrollable log view
        ImGui::BeginChild("ConsoleScrollRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);

        for (const auto& entry : s_logs)
        {
            // Display status tag with color (INFO, WARNING, ERROR)
            ImGui::PushStyleColor(ImGuiCol_Text, toImVec4(entry.statusColor));
            ImGui::Text("[%s] ", entry.status.c_str());
            ImGui::PopStyleColor();

            ImGui::SameLine();

            // Display main log message with its own color
            ImGui::PushStyleColor(ImGuiCol_Text, toImVec4(entry.color));
            ImGui::Text("[%s] %s", entry.channel.c_str(), entry.message.c_str());
            ImGui::PopStyleColor();
        }

        // If scroll is enabled and flagged, scroll to bottom
        if (m_scrollDown && m_autoScrollEnabled)
        {
            ImGui::SetScrollHereY(1.0f);
            m_scrollDown = false;
        }

        ImGui::EndChild(); // End scrollable log region

        // Action buttons
        if (ImGui::Button("Clear")) clear();       // Clear all logs
        ImGui::SameLine();
        ImGui::Checkbox("Auto Scroll", &m_autoScrollEnabled); // Toggle scroll behavior
    }
    ImGui::End();
}