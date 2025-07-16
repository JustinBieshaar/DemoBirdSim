#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

// I like to use ECS for this as System is quite a generic name.
// so something like ECS::System shows it's related to ECS
namespace ECS
{
	/// <summary>
	/// Registry of entities.
	/// This is used to store entities and find entities with certain components.
	/// </summary>
	class Registry
	{
	public:
		template<typename T, typename... Args>
		std::shared_ptr<T> createEntity(Args... args)
		{
			static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity");

			auto entity = std::make_shared<T>(std::forward<Args>(args)...);
			m_entities.push_back(entity);
			return entity;
		}

		template<typename... Components>
		std::vector<Entity*> getEntitiesWith()
		{
			std::vector<Entity*> result;
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
		std::vector<std::shared_ptr<Entity>> m_entities;
	};
}