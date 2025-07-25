#pragma once
#include <Scene.h>
#include <Loader.h>
#include <memory>
#include "../Bootstrappers/MainBootstrapper.h"
#include "../UI/CharacterSelectionView.h"
#include "../Systems/RenderSystem.h"
#include "../Debug/ImGuiDebug/SceneGuiInspectorWindow.h"

/// <summary>
/// Constructs the entire main menu scene including a character selection.
/// </summary>
class MainMenuScene : public Scenes::Scene
{
public:
	MainMenuScene(std::shared_ptr<MainBootstrapper> mainBootstrapper);

	// Inherited via Scene
	void load() override;
	void unload() override;
	bool isLoaded() override;
	void update(float deltaTime) override;
	void render() override;
	void renderImGui() override;

private:
	std::shared_ptr<MainBootstrapper> m_mainBootstrapper;
	std::unique_ptr<CharacterSelectionView> m_characterSelection;
	std::unique_ptr<SceneGuiInspectorWindow> m_debugWindow;
	RenderSystem* m_renderer;
};

