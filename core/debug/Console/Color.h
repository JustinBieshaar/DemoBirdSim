#pragma once

#include <imgui.h>

namespace Console
{
    struct Color
    {
        float r, g, b;

        Color(float r = 255.0f, float g = 255.0f, float b = 255.0f)
            : r(r), g(g), b(b)
        {
        }
    };
}