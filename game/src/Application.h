#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <vector>
#include "Bootstrappers/MainBootstrapper.h"

#include "Debug/ImGuiDebug/GlobalInspectorWindow.h"


class Application
{
public:
    bool init();

    void render();
    void renderImGui();

    void run();

private:
    void cleanup();

    GLFWwindow* m_window;
    float m_lastTime;

    std::shared_ptr<MainBootstrapper> m_mainBootstrapper;
    std::shared_ptr<Scenes::ISceneManager> m_sceneManager;
    std::unique_ptr<GlobalInspectorWindow> m_globalInspectorWindow;
};

