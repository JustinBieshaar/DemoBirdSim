#include "MainMenuScene.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include "../Global/Globals.h"
#include <iostream>

MainMenuScene::MainMenuScene(MainBootstrapper* mainBootstrapper) : Scene(), m_mainBootstrapper(mainBootstrapper), m_loader(new Loader())
{
}

void MainMenuScene::load()
{
    Scene::load();
}

void MainMenuScene::unload()
{
    Scene::unload();
}

bool MainMenuScene::isLoaded()
{
	return false; // todo, add check
}

void MainMenuScene::update(float deltaTime)
{
}

void MainMenuScene::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowSize(ImVec2(500, 200));

    ImGui::Begin("Main Menu");

    ImGui::SetWindowSize(ImVec2(500, 200));
    ImGui::SetWindowPos(ImVec2(Window_Width/2 - 250, Window_Height/2));

    if (ImGui::Button("Play Game", ImVec2(200, 50)))
    {
        // Trigger scene transition
        std::cout << " pressed play! \n";

        m_mainBootstrapper->getSceneManager()->unloadScene("Menu");
        m_mainBootstrapper->getSceneManager()->loadScene("Game");

    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
