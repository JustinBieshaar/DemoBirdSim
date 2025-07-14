#include "CameraComponent.h"
#include <imgui.h>

glm::mat4 CameraComponent::getViewMatrix() const
{
	glm::mat4 viewMatrix(1.0f); // Identity matrix

	// Apply pitch (rotation around X-axis)
	viewMatrix = glm::rotate(viewMatrix, glm::radians(m_pitch + m_transform->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

	// Apply yaw (rotation around Y-axis)
	viewMatrix = glm::rotate(viewMatrix, glm::radians(m_yaw + m_transform->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

	// Apply roll (rotation around Z-axis)
	viewMatrix = glm::rotate(viewMatrix, glm::radians(m_roll + m_transform->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// Translate by the negative camera position
	viewMatrix = glm::translate(viewMatrix, -m_transform->m_position);

	return viewMatrix;
}

glm::mat4 CameraComponent::getProjectionMatrix() const
{
	return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
}

void CameraComponent::SetAspectRatio(float width, float height)
{
	m_aspectRatio = width / height;
}

void CameraComponent::SetFOV(float fov)
{
	m_fov = glm::clamp(fov, 1.0f, 90.0f);
}

void CameraComponent::Zoom(float delta)
{
	SetFOV(m_fov - delta);
}

void CameraComponent::RenderImGui()
{
	ImGui::Text("View setting:");
	ImGui::SliderFloat("Pitch", &m_pitch, -89.0f, 89.0f);
	ImGui::SliderFloat("Yaw", &m_yaw, -180.0f, 180.0f);
	ImGui::SliderFloat("Roll", &m_roll, -180.0f, 180.0f);

	ImGui::Text("Projection setting:");
	ImGui::SliderFloat("FOV (Zoom)", &m_fov, 1.0f, 90.0f);
	ImGui::InputFloat("Near", &m_near);
	ImGui::InputFloat("Far", &m_far);
}

void CameraComponent::update(float deltaTime)
{
}
