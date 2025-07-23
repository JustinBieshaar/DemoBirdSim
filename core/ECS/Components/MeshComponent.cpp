#include "MeshComponent.h"
#include <imgui.h>
#include <StringUtils.h>

void MeshComponent::update(float deltaTime)
{
}

void MeshComponent::renderInspectorImGui()
{
	ImGui::Text("vao: %u", m_vertexArrayObject);
	ImGui::Text("vertex count: %d", m_vertexCount);

	std::string shaderInfo = "Using shader: " + StringUtils::runtime_type_name(m_shader);
	ImGui::Text(shaderInfo.c_str());
} 
