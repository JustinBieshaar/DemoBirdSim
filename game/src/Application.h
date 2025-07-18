#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <vector>
#include "Bootstrappers/MainBootstrapper.h"


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

    MainBootstrapper* m_mainBootstrapper;
};

