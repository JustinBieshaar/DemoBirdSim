#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <vector>
#include <Loader.h>
#include <json.hpp>
#include <SignalHandler.h>

#include "Previewer/BirdPreviewer.h"
#include "Views/IView.h"
#include "Managers/JsonManager.h"

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

    std::vector<std::unique_ptr<IView>> m_views;

    std::shared_ptr<Loader> m_loader;
    std::shared_ptr<Signals::SignalHandler> m_signalHandler;
    std::unique_ptr<BirdPreviewer> m_previewer;
    std::unique_ptr<JsonManager> m_jsonManager;
};

