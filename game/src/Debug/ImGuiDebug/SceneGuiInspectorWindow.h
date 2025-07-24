#pragma once
#include "ImGuiInspectorWindow.h"

#include <vector>
#include <memory>
#include <Entity.h>
#include <Scene.h>

class SceneGuiInspectorWindow : public ImGuiInspectorWindow
{
public:
	SceneGuiInspectorWindow(const char* windowName, Scene* scene) : ImGuiInspectorWindow(windowName), m_scene(scene) {}

	void renderInspectables() override;
	void setEntities(const std::vector<std::shared_ptr<Entity>>& entities) { m_entities = entities; }
	void clear() override { m_entities.clear(); } // kills ownership of entities.

private:
	Scene* m_scene;
	std::vector<std::shared_ptr<Entity>> m_entities;
};

