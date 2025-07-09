#include "GameScene.h"
#include "../../Entities/Camera/Camera.h"
#include "../../Entities/Meshes/Capsule.h"

#include <iostream>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include "../../Entities/Terrain/Terrain.h"

GameScene::GameScene(MainBootstrapper* mainBootstrapper) : Scene(), m_mainBootstrapper(mainBootstrapper)
{
	m_renderer = new RenderSystem(*this, new Light({0,0,5}));
}

void GameScene::load()
{
	Scene::load();
	std::cout << "load game scene \n";
    auto cam = createEntity<Camera>(m_mainBootstrapper->getInputManager(), glm::vec3{ 0,-8, -20 }, 20, 0);
	createEntity<Capsule>(m_loader, glm::vec3{ 0,0,-5});
    createEntity<Capsule>(m_loader, glm::vec3(5, 0, -8));
    createEntity<Terrain>(m_loader, glm::vec3(0, 0, -1));
    createEntity<Terrain>(m_loader, glm::vec3(-1, 0, -1));
    createEntity<Terrain>(m_loader, glm::vec3(0, 0, 0));
    createEntity<Terrain>(m_loader, glm::vec3(-1, 0, 0));
    //createEntity<Terrain>(m_loader, glm::vec3(-1, 0, -1));

	m_renderer->setCamera(cam);
}

void GameScene::unload()
{
    Scene::unload();
}

bool GameScene::isLoaded()
{
	return false;
}

void GameScene::update(float deltaTime)
{
	Scene::update(deltaTime);
	m_renderer->update(deltaTime);
}

void GameScene::render()
{
	//std::cout << "render game scene \n";
	m_renderer->render();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowSize(ImVec2(80, 80));

    ImGui::Begin(" ");

    ImGui::SetWindowSize(ImVec2(80, 80));
    ImGui::SetWindowPos(ImVec2(10, 10));

    if (ImGui::Button("<", ImVec2(50, 50)))
    {
        // Trigger scene transition
        std::cout << " pressed play! \n";

        m_mainBootstrapper->getSceneManager()->unloadScene("Game");
        m_mainBootstrapper->getSceneManager()->loadScene("Menu");

    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
