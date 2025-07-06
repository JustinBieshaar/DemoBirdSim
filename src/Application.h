#pragma once

#include "Rendering/Renderer.h"
#include "ECS/Entity.h"

#include "GLFW/glfw3.h"
#include <vector>
#include "DI/Bootstrappers/MainBootstrapper.h"


class Application
{
public:
    bool init();
    void processInput(float deltaTime);

    void render(Renderer& renderer);
    void renderUI();

    void run();

private:
    void cleanup();

    GLFWwindow* m_window;
    float m_lastTime;

    std::vector<Entity*> m_entities;
    MainBootstrapper* m_mainBootstrapper;
};

