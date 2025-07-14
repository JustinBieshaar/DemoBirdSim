#include "GameScene.h"
#include "../../Entities/Camera/Camera.h"
#include "../../Entities/Meshes/Capsule.h"

#include <iostream>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include "../../Entities/Terrain/Terrain.h"
#include "../../Entities/Playable/Player.h"
#include "../../ECS/Components/FollowTargetComponent.h"

GameScene::GameScene(MainBootstrapper* mainBootstrapper) : Scene(), m_mainBootstrapper(mainBootstrapper)
{
	m_renderer = new RenderSystem(*this, new Light({0,0,5}));
    m_debugWindow = new SceneGuiInspectorWindow("Game Scene", this);
}

/// <summary>
/// Constructs a new GameScene, initializing the render system and main bootstrapper.
/// </summary>
void GameScene::load()
{
	Scene::load();
	std::cout << "load game scene \n";
    auto cam = createEntity<Camera>(m_mainBootstrapper->getInputManager(), glm::vec3{ 0,10, 30 }, 20, 0);
    auto inputManager = m_mainBootstrapper->getInputManager();

    // Create various entities: player capsules and terrain chunks
	auto player = createEntity<Player>(m_loader, inputManager, glm::vec3{ 0,0,-5});
    createEntity<Capsule>(m_loader, glm::vec3(5, 0, -8));
    createEntity<Terrain>(m_loader, glm::vec3(0, 0, -1));
    createEntity<Terrain>(m_loader, glm::vec3(-1, 0, -1));
    createEntity<Terrain>(m_loader, glm::vec3(0, 0, 0));
    createEntity<Terrain>(m_loader, glm::vec3(-1, 0, 0));

    cam->addComponent<FollowTargetComponent>(player->getComponent<Transform>(), glm::vec3(0 , 10.0f, 30.0f));

	m_renderer->setCamera(cam);
    m_debugWindow->setEntities(m_entities);
}

/// <summary>
/// Unloads the game scene. Delegates cleanup to base Scene class.
/// </summary>
void GameScene::unload()
{
    Scene::unload();
    m_entities.clear();
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
	//TEMPORARY rendering of a back button
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
        m_mainBootstrapper->getSceneManager()->unloadScene("Game");
        m_mainBootstrapper->getSceneManager()->loadScene("Menu");
    }

    ImGui::End();

#ifdef _DEBUG
    m_debugWindow->render();
#endif

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
