#include "SceneManager.h"

void SceneManager::addScene(const std::string& sceneName, std::shared_ptr<Scene> scene)
{
	m_scenes[sceneName] = scene;
}

void SceneManager::loadScene(const std::string& sceneName)
{
	auto target = m_scenes.find(sceneName);
	if (target == m_scenes.end()) return;

	auto sceneToAdd = target->second;

	if (!sceneToAdd->isLoaded())
	{
		sceneToAdd->load();
	}

	m_activeScenes.push_back(sceneToAdd);
}

void SceneManager::unloadScene(const std::string& sceneName)
{
	auto target = m_scenes.find(sceneName);
	if (target == m_scenes.end()) return;

	auto sceneToRemove = target->second;

	// Call unload hook
	sceneToRemove->unload();

	// Remove from active list
	auto it = std::remove(m_activeScenes.begin(), m_activeScenes.end(), sceneToRemove);
	m_activeScenes.erase(it, m_activeScenes.end());
}

void SceneManager::update(float deltaTime)
{
	for (std::shared_ptr<Scene> scene : m_activeScenes)
	{
		scene->update(deltaTime);
	}
}

void SceneManager::render()
{
	for (std::shared_ptr<Scene> scene : m_activeScenes)
	{
		scene->render();
	}
}
