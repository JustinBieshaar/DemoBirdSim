#include "Transform.h"
#include <imgui.h>
#include <string>

void Transform::renderInspectorImGui()
{
	// todo: implement changeable values toggle option
	std::string baseID = std::to_string(reinterpret_cast<uintptr_t>(this));

	ImGui::DragFloat3(("Position##" + baseID).c_str(), &m_position.x);
	ImGui::DragFloat3(("Rotation##" + baseID).c_str(), &m_rotation.x);
	ImGui::DragFloat3(("Scale##" + baseID).c_str(), &m_scale.x);
}

void Transform::update(float deltaTime)
{
}
