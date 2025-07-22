#pragma once
#include <vector>
#include <string>
#include <mutex>
#include <queue>

#include "Color.h"

struct LogEntry
{
    std::string status;
    Color statusColor;

    std::string channel;
    std::string message;
    Color color;
};

class Console
{
public:
    static void log(const std::string& channel, const std::string& message, const Color& color);
    static void logError(const std::string& channel, const std::string& message, const Color& color);
    static void logWarning(const std::string& channel, const std::string& message, const Color& color);

    static const std::vector<LogEntry>& getLogEntries();
    static void clear();

    static void drawImGui();

private:
    static void logInternal(const std::string& statusMessage, const Color& statusColor, const std::string& channel, const std::string& message, const Color& color);
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