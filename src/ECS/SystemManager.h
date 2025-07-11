#pragma once

#include <memory>
#include <vector>

#include "System.h"

// I like to use ECS for this as System is quite a generic name.
// so something like ECS::System shows it's related to ECS
namespace ECS
{
	class SystemManager
	{
	public:
		void update(float deltaTime)
		{
			for (auto& system : m_systems)
			{
				system->update(deltaTime);
			}
		}

		template<typename T, typename... Args>
		T& addSystem(Args&&... args)
		{
			auto system = std::make_unique<T>(std::forward<Args>(args)...);
			T& reference = *system;
			m_systems.push_back(std::move(system));
			return reference;
		}

	private:
		std::vector<std::unique_ptr<System>> m_systems;
	};

}