#include <glad/glad.h>
#include "Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Global/Globals.h"

#include <iostream>
#include <Components/TextureComponent.h>
#include <Components/Transform.h>
#include <Console.h>

#include "Prefabs/Camera/Camera.h"
#include "Prefabs/Meshes/Capsule.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/GameScene.h"

#include <ThreadUtils.h>

bool Application::init()
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

    m_mainBootstrapper = std::make_shared<MainBootstrapper>(m_window);
    m_mainBootstrapper->configureBindings();
    m_mainBootstrapper->initialize();

    return true;
}

void Application::render()
{
    glViewport(0, 0, Window_Width, Window_Height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_mainBootstrapper->getSceneManager()->render();
}

// We only need one frame instance for this entire demo. So we generate one here in application
// and just structure who to render when they are active. With console always rendering last.
void Application::renderImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_mainBootstrapper->getSceneManager()->renderImGui();

#if _DEBUG
    m_globalInspectorWindow->render();
    Console::Console::drawImGui();
#endif

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void Application::run()
{
    auto sceneManager = m_mainBootstrapper->getSceneManager();
    sceneManager->addScene("Menu", std::make_shared<MainMenuScene>(m_mainBootstrapper));
    sceneManager->addScene("Game", std::make_shared<GameScene>(m_mainBootstrapper));

    sceneManager->loadScene("Menu");

    m_globalInspectorWindow = std::make_unique<GlobalInspectorWindow>(sceneManager);

    m_lastTime = glfwGetTime(); // otherwise we get extreme first value
    while (!glfwWindowShouldClose(m_window))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        glfwPollEvents();

        // update all
        m_mainBootstrapper->getInputManager()->update(deltaTime);
        m_mainBootstrapper->getSceneManager()->update(deltaTime);

        ThreadUtils::processMainThreadTasks(); // important to call main thread tasks

        // late update all
        m_mainBootstrapper->getInputManager()->lateUpdate(deltaTime);

        render();
        renderImGui();

        glfwSwapBuffers(m_window);
    }

    cleanup();
}

void Application::cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}