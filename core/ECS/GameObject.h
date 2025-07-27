#pragma once

#include <glm/vec3.hpp>
#include <Entity.h>
#include <Components/Transform.h>

namespace ECS
{
	/// <summary>
	/// Basically an Entity with always a transform component.
	/// </summary>
	class GameObject : public ECS::Entity
	{
	public:
		GameObject(const glm::vec3& position = {}, const glm::vec3& rotation = {}, const glm::vec3& scale = glm::vec3(1.0f)) 
			: m_transform(addComponent<Transform>(position, rotation, scale)) {}
		virtual ~GameObject() = default;

		void update(float deltaTime) override;

	protected:
		std::shared_ptr<Transform> m_transform;
	};
}

