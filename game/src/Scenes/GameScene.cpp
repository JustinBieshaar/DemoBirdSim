#include "GameScene.h"
#include "../Prefabs/Camera/Camera.h"
#include "../Prefabs/Meshes/Capsule.h"

#include <iostream>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include "../Prefabs/Terrain/Terrain.h"
#include "../Prefabs/Playable/Player.h"
#include "../Prefabs/Lighting/Light.h"
#include "../Components/FollowTargetComponent.h"

GameScene::GameScene(std::shared_ptr<MainBootstrapper> mainBootstrapper) : Scene(), m_mainBootstrapper(mainBootstrapper)
{
    m_debugWindow = std::make_unique<SceneGuiInspectorWindow>("Game Scene", this);
}

/// <summary>
/// Constructs a new GameScene, initializing the render system and main bootstrapper.
/// </summary>
void GameScene::load()
{
	Scene::load();

    m_renderer = m_systemManager->addSystem<RenderSystem>(*this, glm::vec3{ 100, 10, 5 });

    auto cam = createEntity<Camera>(m_mainBootstrapper->getInputManager(), glm::vec3{ 0,10, 30 }, 20, 0);
    auto inputManager = m_mainBootstrapper->getInputManager();

    // Create various entities: player capsules and terrain chunks
    auto player = createEntity<Player>(m_loader, inputManager, m_mainBootstrapper->getPlayerManager()->getBird() , glm::vec3{ 0,0,-5 });
    createEntity<Capsule>(m_loader, glm::vec3(5, 0, -8));
    createEntity<Terrain>(m_loader, glm::vec3(0, 0, -1));
    createEntity<Terrain>(m_loader, glm::vec3(-1, 0, -1));
    createEntity<Terrain>(m_loader, glm::vec3(0, 0, 0));
    createEntity<Terrain>(m_loader, glm::vec3(-1, 0, 0));

    cam->addComponent<FollowTargetComponent>(player->getComponent<ECS::Transform>(), glm::vec3(0 , 10.0f, 30.0f));

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
	m_renderer->render();
}

void GameScene::renderImGui()
{
    ImGui::SetNextWindowSize(ImVec2(80, 80));

    // Window flags to hide title bar, make non-resizable, non-movable, etc.
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNav;

    ImGui::Begin(" ", nullptr, windowFlags);

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
}
