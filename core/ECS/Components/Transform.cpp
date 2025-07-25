#include "Transform.h"
#include <imgui.h>
#include <string>

void ECS::Transform::renderInspectorImGui()
{
	std::string baseID = std::to_string(reinterpret_cast<uintptr_t>(this));

	if (m_valuesChangableByDebug)
	{
		ImGui::DragFloat3(("Position##" + baseID).c_str(), &m_position.x);
		ImGui::DragFloat3(("Rotation##" + baseID).c_str(), &m_rotation.x);
		ImGui::DragFloat3(("Scale##" + baseID).c_str(), &m_scale.x);
	}
	else
	{
		// not best solution with this if/else state. But does it for now.

		ImGui::Text("Position: (%.2f, %.2f, %.2f)", m_position.x, m_position.y, m_position.z);
		ImGui::Text("Rotation: (%.2f, %.2f, %.2f)", m_rotation.x, m_rotation.y, m_rotation.z);
		ImGui::Text("Scale: (%.2f, %.2f, %.2f)", m_scale.x, m_scale.y, m_scale.z);
	}
}

void ECS::Transform::update(float deltaTime)
{
}
