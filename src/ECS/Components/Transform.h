#pragma once

#include "Component.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "glm/gtc/matrix_transform.hpp"

struct Transform : public Component
{
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale = glm::vec3(1.0f);

	Transform(const glm::vec3& position = {}, const glm::vec3& rotation = {}, const glm::vec3& scale = glm::vec3(1.0f))
		: m_position(position), m_rotation(rotation), m_scale(scale){ }

	glm::mat4 getTransformationMatrix()
	{
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_position);

		glm::mat4 model = translationMatrix * rotationMatrix * scaleMatrix;
		return model;
	}
};