#include "SceneManager.h"
#include "Debug/SceneLogChannels.h"

/// <summary>
/// Adds a new scene to the scene registry. (surprise ;P)
/// </summary>
void SceneManager::addScene(const std::string& sceneName, std::shared_ptr<Scene> scene)
{
	m_scenes[sceneName] = scene;
}

/// <summary>
/// Loads a scene by name and adds it to the active scenes if it's not already loaded.
/// </summary>
/// <param name="sceneName"></param>
void SceneManager::loadScene(const std::string& sceneName)
{
	auto target = m_scenes.find(sceneName);
	if (target == m_scenes.end()) return;

	auto sceneToAdd = target->second;

	SceneLogChannel.log("Loading scene: " + sceneName);

	if (!sceneToAdd->isLoaded())
	{
		sceneToAdd->load();
	}

	m_activeScenes.push_back(sceneToAdd);
}

/// <summary>
/// Unloads a scene by name and removes it from the active scenes list.
/// </summary>
void SceneManager::unloadScene(const std::string& sceneName)
{
	auto target = m_scenes.find(sceneName);
	if (target == m_scenes.end()) return;

	auto sceneToRemove = target->second;

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

void SceneManager::renderImGui()
{
	for (std::shared_ptr<Scene> scene : m_activeScenes)
	{
		scene->renderImGui();
	}
}
