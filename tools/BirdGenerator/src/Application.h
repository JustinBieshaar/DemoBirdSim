#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

class Application
{
public:
    bool init();

    void render();

    void run();

private:
    void cleanup();

    GLFWwindow* m_window;
    float m_lastTime;
};

