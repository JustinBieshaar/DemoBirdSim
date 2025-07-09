#pragma once

#include <glm/vec3.hpp>
#include "../ECS/Entity.h"
#include "../ECS/Components/Transform.h"

/// <summary>
/// Basically an Entity with always a transform component.
/// </summary>
class GameObject : public Entity
{
public:
	GameObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = {}) : m_transform(addComponent<Transform>(position, rotation, scale)) {}

protected:
	std::shared_ptr<Transform> m_transform;
};

