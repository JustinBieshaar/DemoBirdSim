#include "Transform.h"
#include <imgui.h>
#include <string>

void Transform::RenderImGui()
{
	// todo: implement changeable values toggle option
	std::string baseID = std::to_string(reinterpret_cast<uintptr_t>(this));

	ImGui::InputFloat3(("Position##" + baseID).c_str(), &m_position.x);
	ImGui::InputFloat3(("Rotation##" + baseID).c_str(), &m_rotation.x);
	ImGui::InputFloat3(("Scale##" + baseID).c_str(), &m_scale.x);
}
