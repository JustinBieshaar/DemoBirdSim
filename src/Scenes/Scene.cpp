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
}
