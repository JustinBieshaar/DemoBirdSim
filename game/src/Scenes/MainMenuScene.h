#pragma once
#include <Scene.h>
#include <Loader.h>
#include "../Bootstrappers/MainBootstrapper.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(MainBootstrapper* mainBootstrapper);

	// Inherited via Scene
	void load() override;
	void unload() override;
	bool isLoaded() override;
	void update(float deltaTime) override;
	void render() override;

private:
	MainBootstrapper* m_mainBootstrapper;
	Loader* m_loader;
};

