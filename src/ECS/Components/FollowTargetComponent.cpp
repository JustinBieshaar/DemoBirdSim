#include "FollowTargetComponent.h"
#include <glm/gtc/quaternion.hpp>
#include <imgui.h>

void FollowTargetComponent::update(float deltaTime)
{
    if (m_target == nullptr || m_transform == nullptr)
    {
        return;
    }

    // --- SMOOTH POSITION ---
    float positionLerpSpeed = 5.0f; // higher = faster follow
    m_transform->m_position = glm::mix(
        m_transform->m_position,
        m_target->m_position + m_offset,
        deltaTime * positionLerpSpeed
    );

    // --- COMPUTE DIRECTION TO TARGET ---
    glm::vec3 direction = glm::normalize(m_target->m_position - m_transform->m_position);

    // --- CALCULATE DESIRED ROTATION (YAW + PITCH) ---
    float yaw = atan2(direction.x, direction.z);
    float pitch = -asin(direction.y);

    // Convert to quaternion for smooth interpolation
    glm::quat currentRotation = glm::quat(m_transform->m_rotation);
    glm::quat targetRotation = glm::quat(glm::vec3(pitch, yaw, 0.0f));

    // --- SMOOTH ROTATION ---
    float rotationLerpSpeed = 5.0f;
    glm::quat smoothedRotation = glm::slerp(currentRotation, targetRotation, deltaTime * rotationLerpSpeed);

    // Convert back to Euler angles
    m_transform->m_rotation = glm::eulerAngles(smoothedRotation);
    m_transform->m_rotation.z = 0; // force roll to 0
}

void FollowTargetComponent::RenderImGui()
{
    ImGui::DragFloat3("offset", &m_offset.x);
}
