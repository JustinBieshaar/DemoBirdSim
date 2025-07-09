#include "GameScene.h"
#include "../../Entities/Camera/Camera.h"
#include "../../Entities/Meshes/Capsule.h"

GameScene::GameScene(MainBootstrapper* mainBootstrapper) : Scene(), m_mainBootstrapper(mainBootstrapper)
{
}

void GameScene::load()
{
	createEntity<Camera>(m_mainBootstrapper->getInputManager());
	createEntity<Capsule>(m_loader);
}

void GameScene::unload()
{
}

bool GameScene::isLoaded()
{
	return false;
}

void GameScene::update(float deltaTime)
{
}

void GameScene::render()
{
}
