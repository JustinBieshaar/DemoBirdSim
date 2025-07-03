#pragma once

#include "Component.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct SpriteComponent : Component
{
	unsigned int m_textureID;
	glm::vec2 m_size;
	glm::vec4 color = glm::vec4(1.0f);
};