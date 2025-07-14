#include "FollowTargetComponent.h"
#include <glm/gtc/quaternion.hpp>
#include <imgui.h>

void FollowTargetComponent::update(float deltaTime)
{
    if (m_target == nullptr || m_transform == nullptr)
    {
        return;
    }

	m_transform->m_position = m_target->m_position + m_offset;

    // Compute direction vector (target - self)
    glm::vec3 direction = glm::normalize(m_target->m_position - m_transform->m_position);

    // Calculate yaw and pitch
    float yaw = atan2(direction.x, direction.z);
    float pitch = -asin(direction.y);

    m_transform->m_rotation = glm::vec3(pitch, yaw, 0.0f); 
}

void FollowTargetComponent::RenderImGui()
{
    ImGui::DragFloat3("offset", &m_offset.x);
}
