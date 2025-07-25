#pragma once
#include <string>
#include "Color.h"

namespace Console
{
    /// <summary>
    /// A wrapper to use Console with given formatting.
    /// You can create log channels using name for prefix and color for message color.
    /// This to make the console more readable and easy to follow and find specific logs.
    /// </summary>
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

        friend class Console; // gives access to private members ;)
    };
}