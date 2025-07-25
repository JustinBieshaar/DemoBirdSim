#pragma once
#include <Scene.h>
#include <memory>
#include "../Bootstrappers/MainBootstrapper.h"
#include "../Systems/RenderSystem.h"
#include "../Debug/ImGuiDebug/SceneGuiInspectorWindow.h"

class GameScene : public Scenes::Scene
{
public:
	GameScene(std::shared_ptr<MainBootstrapper> mainBootstrapper);

	// Inherited via Scene
	void load() override;
	void unload() override;
	bool isLoaded() override;
	void update(float deltaTime) override;
	void render() override;
	void renderImGui() override;

private:
	std::shared_ptr<MainBootstrapper> m_mainBootstrapper;
	std::unique_ptr<SceneGuiInspectorWindow> m_debugWindow;

	RenderSystem* m_renderer;
};

