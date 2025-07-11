#include "ImGuiInspectorWindow.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <string>

ImGuiInspectorWindow::ImGuiInspectorWindow(const char* windowName) : m_windowName(windowName)
{
}

void ImGuiInspectorWindow::render()
{
	ImGui::Begin(m_windowName);
	renderInspectables();
	ImGui::End();
}
