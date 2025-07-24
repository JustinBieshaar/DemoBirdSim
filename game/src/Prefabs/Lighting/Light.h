#pragma once

#include <glm/vec3.hpp>
#include <Entity.h>

class Light : public ECS::Entity
{
public:
	Light(glm::vec3 position, glm::vec3 color = {1,1,1}) : m_position(position), m_color(color) {}

	glm::vec3 m_position;
	glm::vec3 m_color;

	// Inherited via Entity
	void update(float deltaTime) override;
};