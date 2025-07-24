#include "MainMenuScene.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include "../Prefabs/Preview/MainMenuBirdPreview.h"
#include "../Global/Globals.h"
#include "../Debug/GameLogChannels.h"
#include "../Prefabs/Camera/Camera.h"
#include <iostream>
#include "../Components/FollowTargetComponent.h"

MainMenuScene::MainMenuScene(std::shared_ptr<MainBootstrapper> mainBootstrapper) :
    Scene(), m_mainBootstrapper(mainBootstrapper)
{
    m_renderer = std::make_unique<RenderSystem>(*this, new Light({ 100,10,5 }));
    m_debugWindow = std::make_unique<SceneGuiInspectorWindow>("MainMenu Scene", this);
}

void MainMenuScene::load()
{
    Scene::load();
    auto cam = createEntity<Camera>(m_mainBootstrapper->getInputManager(), glm::vec3{ 0,10, 30 }, 20, 0);
    auto inputManager = m_mainBootstrapper->getInputManager();

    //todo: make init for this so it's not created on every load. But for now this works :)

    auto signalHandler = m_mainBootstrapper->getSignalHandler();
    m_characterSelection = std::make_unique<CharacterSelectionView>(signalHandler);
    auto player = createEntity<MainMenuBirdPreview>(m_loader, signalHandler);

    // just so it's at right location
    cam->addComponent<FollowTargetComponent>(player->getComponent<ECS::Transform>(), glm::vec3(0, 4.0f, 10.0f));

    m_characterSelection->init();

    m_renderer->setCamera(cam);
    m_debugWindow->setEntities(m_entities);
}

void MainMenuScene::unload()
{
    Scene::unload();
    m_entities.clear();
    m_renderer->clear();
    m_debugWindow->clear();
}

bool MainMenuScene::isLoaded()
{
	return false; // todo, add check
}

void MainMenuScene::update(float deltaTime)
{
    Scene::update(deltaTime);
    m_renderer->update(deltaTime);
}

void MainMenuScene::render()
{
    m_renderer->render();
}

void MainMenuScene::renderImGui()
{
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNav;

    ImGui::SetNextWindowSize({ Window_Width, Window_Height });
    ImGui::SetNextWindowPos({ 0,0 });

    ImGui::Begin("Main Menu", nullptr, windowFlags);

    m_characterSelection->renderImGui();

    // === Centered Play Button ===
    ImVec2 buttonSize = ImVec2(200, 50);
    float buttonX = (Window_Width - buttonSize.x) * 0.5f;
    float buttonY = Window_Height - 200.0f;

    ImGui::SetCursorPos(ImVec2(buttonX, buttonY));
    if (ImGui::Button("Play Game", buttonSize))
    {
        MainMenuSceneLogChannel.log("Start loading game scene!");

        m_mainBootstrapper->getSceneManager()->loadScene("Game");
        m_mainBootstrapper->getSceneManager()->unloadScene("Menu");
    }

    m_debugWindow->render();

    ImGui::End();
}
