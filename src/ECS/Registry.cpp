#include "Registry.h"

namespace ECS
{
	template<typename... Components>
	std::vector<Entity*> Registry::getEntitiesWith()
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
}