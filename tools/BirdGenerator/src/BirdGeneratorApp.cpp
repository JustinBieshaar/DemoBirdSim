#include <glad/glad.h>
#include "BirdGeneratorApp.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Views/ControlsView.h"

#include "Global/Globals.h"

#include <BirdsFactory.h>
#include <fstream>

#include <PathManager.h>

#include <string>
#include <iostream>
#include "Views/BirdDataView.h"
#include "Validation/JsonValidator.h"
#include "Debug/LoadingScreen.h"

#include <Console.h>
#include <ThreadUtils.h>

bool BirdGeneratorApp::init()
{
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(Window_Width, Window_Height, "", nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate();
        return false;
    }

    glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, false);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glEnable(GL_DEPTH_TEST);

    PathManager::setResourceRoot(_SOLUTIONDIR);

    return true;
}

void BirdGeneratorApp::render3D()
{
    glViewport(0, 0, Window_Width, Window_Height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_previewer->render();
}

void BirdGeneratorApp::renderUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    for (auto& view : m_views)
    {
        view->render();
    }

    Console::Console::drawImGui();

    LoadingScreen::render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void BirdGeneratorApp::run()
{
    m_loader = std::make_shared<Loader>();
    m_signalHandler = std::make_shared<Signals::SignalHandler>();

    m_jsonManager = std::make_unique<JsonManager>(m_signalHandler);

    m_previewer = std::make_unique<BirdPreviewer>(m_loader);
    m_views.push_back(std::make_unique<BirdDataView>(m_signalHandler, m_jsonManager.get()));
    m_views.push_back(std::make_unique<ControlsView>(m_signalHandler, m_jsonManager.get()));

    m_previewer->subscribeSignals(m_signalHandler);
    for (auto& view : m_views)
    {
        view->init();
    }

    auto json = m_jsonManager->getBirdsJson();
    auto firstIt = json.begin();
    if (firstIt != json.end())
    {
        m_signalHandler->invokeSignal(ChangeBirdSignal{ firstIt.key(), firstIt.value() });
    }

    m_lastTime = glfwGetTime(); // otherwise we get extreme first value
    while (!glfwWindowShouldClose(m_window))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        glfwPollEvents();

        m_previewer->update(deltaTime);

        ThreadUtils::processMainThreadTasks(); // important to keep running the main thread tasks for async operations.

        render3D();
        renderUI();

        glfwSwapBuffers(m_window);
    }

    cleanup();
}

void BirdGeneratorApp::cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}
