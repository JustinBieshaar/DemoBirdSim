#pragma once

#include "Component.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <IInspectable.h>
#include <cmath>

class Transform : public Component, public IInspectable
{
public:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale = glm::vec3(1.0f);

	Transform(const glm::vec3& position = {}, const glm::vec3& rotation = {}, const glm::vec3& scale = glm::vec3(1.0f), bool valuesChangableByDebug = true)
		: m_position(position), m_rotation(rotation), m_scale(scale)
	{
		m_valuesChangableByDebug = valuesChangableByDebug;
	}

	glm::mat4 getTransformationMatrix()
	{
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);

		glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0, 0, 1));

		glm::mat4 rotationMatrix = rotationZ * rotationY * rotationX; // ZYX order (common in many engines)

		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_position);

		glm::mat4 model = translationMatrix * rotationMatrix * scaleMatrix;
		return model;
	}

	glm::vec3 getForward() const
	{
		glm::vec3 forward;

		forward.x = std::cos(m_rotation.x) * std::sin(m_rotation.y);
		forward.y = -std::sin(m_rotation.x);
		forward.z = std::cos(m_rotation.x) * std::cos(m_rotation.y);

		return forward;
	}

	void RenderImGui() override;
	void update(float deltaTime) override;

	void setScale(float scale)
	{
		m_scale = glm::vec3(scale);
	}
};