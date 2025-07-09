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
#include "ECS/Components/TextureComponent.h"
#include "ECS/Components/Transform.h"
#include "Entities/Camera/Camera.h"
#include "Entities/Meshes/Cube.h"
#include "Entities/Meshes/Capsule.h"

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

    m_mainBootstrapper = new MainBootstrapper(m_window);
    m_mainBootstrapper->configureBindings();
    m_mainBootstrapper->initialize();

    return true;
}

void Application::processInput(float deltaTime)
{
    m_mainBootstrapper->getInputManager()->update(deltaTime);
}

void Application::render(Renderer& renderer)
{
    glViewport(0, 0, Window_Width, Window_Height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer.render(m_entities);
}

void Application::renderUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowSize(ImVec2(100, 50));

    ImGui::Begin("Debug Info");
    ImGui::Text("Demo config");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::run()
{
    Loader* loader = new Loader();

    Camera camera(m_mainBootstrapper->getInputManager(), { 0,0,-3 }, 0, 0);
    Light light({ 0,0,5 });

    Renderer renderer(&camera, &light);

    Cube* cube = new Cube(loader);
    cube->addComponent<Transform>(glm::vec3(5,0,-8), glm::vec3(0,0,0));
    cube->addComponent<TextureComponent>(loader);

    Capsule* capsule = new Capsule(loader);
    capsule->addComponent<Transform>(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0));
    capsule->addComponent<TextureComponent>(loader);

    std::cout << "Run!" << "\n";

    m_entities.push_back(capsule);
    m_entities.push_back(cube);
    while (!glfwWindowShouldClose(m_window))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        glfwPollEvents();
        processInput(deltaTime);
        camera.update();

        render(renderer);
        renderUI();

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