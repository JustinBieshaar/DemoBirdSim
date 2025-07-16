#pragma once

#include <glm/vec3.hpp>
#include <Entity.h>
#include <Components/Transform.h>

/// <summary>
/// Basically an Entity with always a transform component.
/// </summary>
class GameObject : public Entity
{
public:
	GameObject(const glm::vec3& position = {}, const glm::vec3& rotation = {}, const glm::vec3& scale = glm::vec3(1.0f)) : m_transform(addComponent<Transform>(position, rotation, scale)) {}

	void update(float deltaTime) override;

protected:
	std::shared_ptr<Transform> m_transform;
};

