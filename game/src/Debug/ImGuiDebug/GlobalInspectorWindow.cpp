#include "GlobalInspectorWindow.h"
#include <string>
#include <imgui.h>
#include "../../Global/Globals.h"
#include <Components/MeshComponent.h>

GlobalInspectorWindow::GlobalInspectorWindow(std::shared_ptr<Scenes::ISceneManager> sceneManager) : ImGuiInspectorWindow("Globals"), m_sceneManager(sceneManager)
{
}

void GlobalInspectorWindow::renderInspectables()
{
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Set Wireframe mode: ");
    ImGui::SameLine();
    ImGui::PushItemWidth(100); // fixed size

    // ## for invisible as text is set above so it's on the left.
	ImGui::Checkbox("##wireframeMode", &EnableWireframeMode);
}
