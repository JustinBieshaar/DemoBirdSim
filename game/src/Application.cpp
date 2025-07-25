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
    // Initialize GLFW (used for window + context creation)
    if (!glfwInit()) return false;

    // Configure GLFW context to use OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window with defined dimensions
    m_window = glfwCreateWindow(Window_Width, Window_Height, "", nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate(); // Cleanup on failure
        return false;
    }

    glfwMakeContextCurrent(m_window);     // Activate OpenGL context
    glfwSwapInterval(1);                  // Enable VSync for smoother visuals

    // Load OpenGL function pointers via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // ImGui initialization (UI library)
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark(); 
    ImGui_ImplGlfw_InitForOpenGL(m_window, true); // Backend binding
    ImGui_ImplOpenGL3_Init("#version 400"); // OpenGL shader version

    // Enable Z-buffering (important for depth testing)
    glEnable(GL_DEPTH_TEST);

    // Set up main dependency injection system (e.g., Input, Scene, etc.)
    m_mainBootstrapper = std::make_shared<MainBootstrapper>(m_window);
    m_mainBootstrapper->configureBindings();

    return true;
}

void Application::render()
{
    // Define the renderable area
    glViewport(0, 0, Window_Width, Window_Height);
    // Set background clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);  // Ensure depth buffer works
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear both buffers

    // Call scene-specific render logic
    m_mainBootstrapper->resolve<Scenes::ISceneManager>()->render();
}

// We only need one frame instance for this entire demo. So we generate one here in application
// and just structure who to render when they are active. With console always rendering last.
void Application::renderImGui()
{
    // Start new ImGui frame
    // Only using one frame in this case as there's no need for multi frame support by now.
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Call current scene's ImGui UI rendering
    m_mainBootstrapper->resolve<Scenes::ISceneManager>()->renderImGui();

#if _DEBUG
    // Only show developer UI in debug mode
    m_globalInspectorWindow->render();
    Console::Console::drawImGui();
#endif

    // Render all ImGui content collected this frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void Application::run()
{
    // Set up the scenes (e.g., menu and game)
    auto sceneManager = m_mainBootstrapper->resolve<Scenes::ISceneManager>();
    sceneManager->addScene("Menu", std::make_shared<MainMenuScene>(m_mainBootstrapper));
    sceneManager->addScene("Game", std::make_shared<GameScene>(m_mainBootstrapper));
    sceneManager->loadScene("Menu");
    // TODO: fix scene string bind. Maybe add some defines or auto generation for this at some point

    // Retrieve input manager
    auto inputManager = m_mainBootstrapper->resolve<IInputManager>();

    // Create global inspector (debug view of ECS)
    m_globalInspectorWindow = std::make_unique<GlobalInspectorWindow>(sceneManager);

    // Timing setup
    m_lastTime = glfwGetTime();

    // Main loop
    while (!glfwWindowShouldClose(m_window))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        glfwPollEvents(); // Process OS/window/input events

        // Update logic
        inputManager->update(deltaTime);
        sceneManager->update(deltaTime);

        // Handle tasks queued for the main thread
        ThreadUtils::processMainThreadTasks();

        // Perform late updates (input debouncing etc.)
        inputManager->lateUpdate(deltaTime);

        // Render 3D and UI
        render();
        renderImGui();

        // Swap buffers to present the frame
        glfwSwapBuffers(m_window);
    }

    cleanup(); // Cleanup on window close
}

void Application::cleanup()
{
    // Shutdown ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Close and destroy GLFW window
    glfwDestroyWindow(m_window);
    glfwTerminate();
}