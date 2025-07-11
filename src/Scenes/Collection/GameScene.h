#pragma once
#include "../Scene.h"
#include "../../DI/Bootstrappers/MainBootstrapper.h"
#include "../../Systems/RenderSystem.h"
#include "../../Tools/ImGuiDebug/SceneGuiInspectorWindow.h"

class GameScene : public Scene
{
public:
	GameScene(MainBootstrapper* mainBootstrapper);

	// Inherited via Scene
	void load() override;
	void unload() override;
	bool isLoaded() override;
	void update(float deltaTime) override;
	void render() override;

private:
	MainBootstrapper* m_mainBootstrapper;

	SceneGuiInspectorWindow* m_debugWindow;

	RenderSystem* m_renderer;
};

