#pragma once

#include "Component.h"
#include <glm/vec3.hpp>

struct Transform : Component
{
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale = glm::vec3(1.0f);

	Transform(const glm::vec3& position = {}, const glm::vec3& rotation = {}, const glm::vec3& scale = glm::vec3(1.0f))
		: m_position(position), m_rotation(rotation), m_scale(scale){ }
};