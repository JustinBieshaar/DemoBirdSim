#pragma once
#include "ImGuiInspectorWindow.h"

#include <vector>
#include <memory>
#include "../../ECS/Entity.h"

class SceneGuiInspectorWindow : public ImGuiInspectorWindow
{
public:
	SceneGuiInspectorWindow(const char* windowName) : ImGuiInspectorWindow(windowName){}

	void renderInspectables() override;
	void setEntities(const std::vector<std::shared_ptr<Entity>>& entities) { m_entities = entities; }

private:
	std::vector<std::shared_ptr<Entity>> m_entities;
};

