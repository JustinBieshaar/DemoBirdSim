#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <vector>

class BirdGeneratorApp
{
public:
    bool init();

    void render3D();
    void renderUI();

    void run();

private:
    void cleanup();

    GLFWwindow* m_window;
    float m_lastTime;

    
};

