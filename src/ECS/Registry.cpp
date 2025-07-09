#include "Registry.h"

namespace ECS
{
	template<typename ...Components>
	std::vector<Entity*> Registry::getEntitiesWith()
	{
		std::vector<Entity*> result;
		for (auto& entity : m_entities)
		{
			if ((entity->hasComponent<Components>() && ...))
			{
				result.push_back(entity.get());
			}
		}
		return result;
	}
}