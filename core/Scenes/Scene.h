#pragma once

#include <memory>
#include <vector>
#include <IInspectable.h>
#include <Registry.h>
#include <Loader.h>
#include <SystemManager.h>

namespace Scenes
{
	/// <summary>
	/// Base class representing a scene in the application or game.
	/// Inherits from ECS::Registry for managing entities in systems.
	/// Using ECS::Registry allows us to do operations like getEntitiesWith<A,B,C...> etc
	/// </summary>
	class Scene : public ECS::Registry, public IInspectable, public std::enable_shared_from_this<Scene>
	{
	public:
		Scene() { }

		virtual ~Scene() = default;

		/// <summary>
		/// Loads the scene. Initializes the loader.
		/// Can be overridden for scene-specific loading logic.
		/// </summary>
		virtual void load()
		{
			m_loader = std::make_shared<Loader>();
			m_systemManager = std::make_unique<ECS::SystemManager>();
		}

		/// <summary>
		/// Unloads the scene. Cleans up the loader and resets resources.
		/// Can be overridden for scene-specific unload logic.
		/// </summary>
		virtual void unload()
		{
			m_loader->cleanup();
			m_loader.reset();

			m_systemManager->cleanup();
			m_systemManager.reset();
		}

		virtual bool isLoaded() = 0;

		virtual void update(float deltaTime)
		{
			for (auto& entity : m_entities)
			{
				if (entity == nullptr) continue;
				// update entity first
				entity->update(deltaTime);
				entity->updateAllComponents(deltaTime);
			}

			m_systemManager->update(deltaTime);
		}

		virtual void render() = 0;
		virtual void renderImGui() = 0;

		void renderInspectorImGui() override;

	protected:
		std::shared_ptr<ILoader> m_loader;
		std::unique_ptr<ECS::SystemManager> m_systemManager;
	};
}