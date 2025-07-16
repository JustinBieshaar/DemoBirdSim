#include "FollowTargetComponent.h"
#include <glm/gtc/quaternion.hpp>
#include <imgui.h>
#include <string>
#include <iostream>

void FollowTargetComponent::update(float deltaTime)
{
    if (m_target == nullptr || m_transform == nullptr)
    {
        return;
    }

    auto targetPosition = m_target->m_position + m_offset;
    auto distance = glm::distance(m_transform->m_position, targetPosition);

    if (distance < m_distanceClamp)
    {
        // too close to move
        return;
    }

    // --- SMOOTH POSITION ---
    float positionLerpSpeed = 5.0f; // higher = faster follow
    m_transform->m_position = glm::mix(
        m_transform->m_position,
        targetPosition,
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
    auto targetPosition = m_target->m_position + m_offset;
    auto distance = glm::distance(m_transform->m_position, targetPosition);

    std::string distanceLabel = "distance: " + std::to_string(distance);
    ImGui::Text(distanceLabel.c_str());
    if (distance < m_distanceClamp)
    {
        ImGui::Text("DISABLED, distance is too low");
    }
}
