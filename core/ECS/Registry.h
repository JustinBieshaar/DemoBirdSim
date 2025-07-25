/* This file contains summaries for even the most obvious methods as it's acting as a library.
That way each method can be understood without diving into the code. I know some like and other dislike this.
So hence the heads up. ;) */

#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

namespace ECS
{
	/// <summary>
	/// Registry of entities.
	/// This is used to store entities and find entities with certain components.
	/// </summary>
	class Registry
	{
	public:

		/// <summary>
		/// Creates an entity of given type and stores it for future reference. (And inspector window for example)
		/// </summary>
		template<typename T, typename... Args>
		std::shared_ptr<T> createEntity(Args... args)
		{
			static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity");

			auto entity = std::make_shared<T>(std::forward<Args>(args)...);
			m_entities.push_back(entity);
			return entity;
		}

		/// <summary>
		/// Returns all entities with given components. You can pass multiple components.
		/// getEntitiesWith<Transform, MeshComponent> will return all entities with both components.
		/// NOTE; entities are only included who own ALL given components.
		/// </summary>
		template<typename... Components>
		std::vector<ECS::Entity*> getEntitiesWith()
		{
			std::vector<ECS::Entity*> result;
			for (auto& entity : m_entities)
			{
				// Learned about this cool fold expression that's been introduced in C++ 17
				// https://en.cppreference.com/w/cpp/language/fold.html?ref=blog.yuo.be
				if ((entity->hasComponent<Components>() && ...))
				{
					result.push_back(entity.get());
				}
			}
			return result;
		}
		
	protected:
		std::vector<std::shared_ptr<ECS::Entity>> m_entities;
	};
}