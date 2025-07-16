#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Scene.h"
#include "ISceneManager.h"

class SceneManager : ISceneManager
{
public:
	void addScene(const std::string& sceneName, std::shared_ptr<Scene> scene);

	void loadScene(const std::string& sceneName);
	void unloadScene(const std::string& sceneName);

	void update(float deltaTime);
	void render();

private:
	std::unordered_map <std::string, std::shared_ptr<Scene>> m_scenes;
	std::vector<std::shared_ptr<Scene>> m_activeScenes;
};