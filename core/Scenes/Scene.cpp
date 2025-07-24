#include "Scene.h"
#include <string>
#include <imgui.h>
#include <Components/MeshComponent.h>

void Scene::renderInspectorImGui()
{
	int totalVertexCount = 0;
	auto meshEntities = getEntitiesWith<ECS::MeshComponent>();

	for (auto meshEntity : meshEntities)
	{
		totalVertexCount += meshEntity->getComponent<ECS::MeshComponent>()->m_vertexCount;
	}

	ImGui::Text("Total vertex count: %d", totalVertexCount);
}
