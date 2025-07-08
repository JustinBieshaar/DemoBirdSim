#pragma once

#include <glm/vec3.hpp>

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color = {1,1,1}) : m_position(position), m_color(color) {}

	glm::vec3 m_position;
	glm::vec3 m_color;
};