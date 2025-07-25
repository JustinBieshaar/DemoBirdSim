#include "Console.h"
#include "LogChannel.h"
#include "Color.h"

Console::LogChannel::LogChannel(std::string name, const Color& color)
    : m_name(std::move(name)), m_color(color)
{
}

void Console::LogChannel::log(const std::string& message) const
{
    Console::log(m_name, message, m_color);
}

void Console::LogChannel::logWarning(const std::string& message) const
{
    Console::logWarning(m_name, message, m_color);
}

void Console::LogChannel::logError(const std::string& message) const
{
    Console::logError(m_name, message, m_color);
}
