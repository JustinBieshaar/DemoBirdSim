#include "Scene.h"
#include <imgui.h>

void Scene::RenderImGui()
{
	if (ImGui::Button("ToggleWireframes"))
	{
		m_toggleWireframes = !m_toggleWireframes;
	}
}
