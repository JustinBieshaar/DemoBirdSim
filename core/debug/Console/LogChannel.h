#pragma once
#include <string>
#include "Color.h"

class LogChannel
{
public:
    LogChannel(std::string name, const Color& color);

    void log(const std::string& message) const;
    void logWarning(const std::string& message) const;
    void logError(const std::string& message) const;

private:
    std::string m_name;
    Color m_color;

    friend class Console;
};