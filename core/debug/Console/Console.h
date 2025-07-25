/* This file contains summaries for even the most obvious methods as it's acting as a library.
That way each method can be understood without diving into the code. I know some like and other dislike this.
So hence the heads up. ;) */

#pragma once
#include <vector>
#include <string>
#include <mutex>
#include <queue>

#include "Color.h"

namespace Console
{
    struct LogEntry
    {
        std::string status;
        Color statusColor;

        std::string channel;
        std::string message;
        Color color;
    };

    /// <summary>
    /// This is a basic logger that allows easy logging access.
    /// Use LogChannels to control this console for predefined formatting (prefix + color).
    /// 
    /// Furthermore this is a basic console with not too many options beside allowing rendering it
    /// using imgui.
    /// For future iterations it could use some filtering or search functionalities. But not a necessity for now.
    /// </summary>
    class Console
    {
    public:
        /// <summary>
        /// Logs information
        /// Internally uses logInternal for consistent formatting and storage.
        /// </summary>
        static void log(const std::string& channel, const std::string& message, const Color& color);

        /// <summary>
        /// Logs warning
        /// Internally uses logInternal for consistent formatting and storage.
        /// </summary>
        static void logWarning(const std::string& channel, const std::string& message, const Color& color);

        /// <summary>
        /// Logs error
        /// Internally uses logInternal for consistent formatting and storage.
        /// </summary>
        static void logError(const std::string& channel, const std::string& message, const Color& color);

        static const std::vector<LogEntry>& getLogEntries();

        /// <summary>
        /// Clears all logs
        /// </summary>
        static void clear();

        /// <summary>
        /// Draws the console to imgui.
        /// Make sure there's a new frame already created as this is only doing ImGui::begin .. ImGui::end
        /// </summary>
        static void drawImGui();

    private:

        /// <summary>
        /// Utility to convert Console::Color to imgui color
        /// </summary>
        inline static ImVec4 toImVec4(const Color& color)
        {
            return ImVec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, 1.0f);
        }

        /// <summary>
        /// Internal helper for all log types.
        /// Adds a message to the pending queue and writes to std::cerr.
        /// This separation allows queued rendering to ImGui while keeping logging thread-safe.
        /// </summary>
        static void logInternal(const std::string& statusMessage, const Color& statusColor, const std::string& channel, const std::string& message, const Color& color);

        /// <summary>
        /// Flushes queued log messages into the main log vector for rendering.
        /// Called during ImGui render loop to ensure new messages are shown.
        /// </summary>
        static void flushPendingLogs();

        static inline std::mutex s_logMutex;
        static inline std::vector<LogEntry> s_logs;
        static inline std::queue<LogEntry> s_pendingLogs;

        static inline Color m_infoColor = Color(100, 100, 255); // Blue-ish
        static inline Color m_errorColor = Color(255, 0, 0); // red
        static inline Color m_warningColor = Color(255, 255, 0); // yellow

        static inline std::string InfoStatusStr = "INFO";
        static inline  std::string WarningStatusStr = "WARNING";
        static inline  std::string ErrorStatusStr = "ERROR";

        static inline bool m_scrollDown = true;
        static inline bool m_autoScrollEnabled = true;
    };
}