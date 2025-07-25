/* This file contains summaries for even the most obvious methods as it's acting as a library.
That way each method can be understood without diving into the code. I know some like and other dislike this.
So hence the heads up. ;) */

#pragma once

#include <memory>
#include <vector>

#include "System.h"

namespace ECS
{
	class SystemManager
	{
	public:
		SystemManager() = default;
		~SystemManager() { cleanup(); }

		void update(float deltaTime)
		{
			for (auto& system : m_systems)
			{
				system->update(deltaTime);
			}
		}

		/// <summary>
		/// Add system of type.
		/// This system will be stored and updated by this manager.
		/// </summary>
		template<typename T, typename... Args>
		T* addSystem(Args&&... args)
		{
			static_assert(std::is_base_of<System, T>::value, "T must derive from System");

			auto system = std::make_unique<T>(std::forward<Args>(args)...);
			T* systemPtr = system.get(); // get pointer before move
			m_systems.push_back(std::move(system)); // safe: unique_ptr<T> to unique_ptr<System>
			return systemPtr;
		}

		/// <summary>
		/// Clears all systems
		/// </summary>
		void cleanup()
		{
			m_systems.clear();
		}

	private:
		std::vector<std::unique_ptr<System>> m_systems;
	};
}