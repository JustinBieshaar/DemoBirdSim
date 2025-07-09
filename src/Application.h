#pragma once

#include "Rendering/Renderer.h"
#include "ECS/Entity.h"


#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <vector>
#include "DI/Bootstrappers/MainBootstrapper.h"


class Application
{
public:
    bool init();

    void render();
    void renderUI();

    void run();

private:
    void cleanup();

    GLFWwindow* m_window;
    float m_lastTime;

    std::vector<Entity*> m_entities;
    MainBootstrapper* m_mainBootstrapper;
};

