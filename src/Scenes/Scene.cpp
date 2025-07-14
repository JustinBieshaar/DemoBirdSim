#include "Scene.h"
#include <string>
#include <imgui.h>
#include "../Global/Globals.h"

void Scene::RenderImGui()
{
	std::string wireframesEnabled = EnableWireframeMode ? "true" : "false";
	ImGui::Text("Wireframes Enabled");
	if (ImGui::RadioButton("Wireframes Enabled", EnableWireframeMode))
	{
		EnableWireframeMode = !EnableWireframeMode;
	}

	int totalVertexCount = 0;
	auto meshEntities = getEntitiesWith<MeshComponent>();

	for (auto meshEntity : meshEntities)
	{
		totalVertexCount += meshEntity->getComponent<MeshComponent>()->m_vertexCount;
	}

	ImGui::Text("Total vertex count: %d", totalVertexCount);
}
