#include "Scene.h"
#include <string>
#include <imgui.h>
#include <Components/MeshComponent.h>

void Scene::RenderImGui()
{
	int totalVertexCount = 0;
	auto meshEntities = getEntitiesWith<MeshComponent>();

	for (auto meshEntity : meshEntities)
	{
		totalVertexCount += meshEntity->getComponent<MeshComponent>()->m_vertexCount;
	}

	ImGui::Text("Total vertex count: %d", totalVertexCount);
}
