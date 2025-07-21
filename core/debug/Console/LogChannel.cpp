#include "Console.h"
#include "LogChannel.h"
#include "Color.h"

LogChannel::LogChannel(std::string name, const Color& color)
    : m_name(std::move(name)), m_color(color)
{
}

void LogChannel::log(const std::string& message) const
{
    Console::log(m_name, message, m_color);
}