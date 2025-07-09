#pragma once

#include "../../Rendering/Loading/Loader.h"
#include "Component.h"

#include <glm/ext/matrix_transform.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Transform.h"

struct CameraComponent : public Component
{
	std::shared_ptr<Transform> m_transform;

	float m_pitch;
	float m_yaw;

	CameraComponent(std::shared_ptr<Transform> transform = {}, float pitch = 0.0f, float yaw = 0.0f) : m_transform(transform), m_pitch(pitch), m_yaw(yaw)
	{ }


	glm::mat4 getViewMatrix()
	{
		glm::mat4 viewMatrix(1.0f); // Identity matrix

		// Apply pitch (rotation around X-axis)
		viewMatrix = glm::rotate(viewMatrix, glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f));

		// Apply yaw (rotation around Y-axis)
		viewMatrix = glm::rotate(viewMatrix, glm::radians(m_yaw), glm::vec3(0.0f, 1.0f, 0.0f));

		// Translate by the negative camera position
		viewMatrix = glm::translate(viewMatrix, m_transform->m_position);

		return viewMatrix;
	}
};