#pragma once
#include "../Scene.h"
#include "../../DI/Bootstrappers/MainBootstrapper.h"

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
};

