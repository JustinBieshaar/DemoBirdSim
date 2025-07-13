#pragma once

#include <memory>
#include <vector>
#include "../ECS/Entity.h"
#include "../ECS/Registry.h"
#include "../Rendering/Loading/Loader.h"


/// <summary>
/// Base class representing a scene in the application or game.
/// Inherits from ECS::Registry for managing entities in systems.
/// Using ECS::Registry allows us to do operations like getEntitiesWith<A,B,C...> etc
/// </summary>
class Scene : public ECS::Registry, public IInspectable
{
public:
	virtual ~Scene() = default;

	/// <summary>
	/// Loads the scene. Initializes the loader.
	/// Can be overridden for scene-specific loading logic.
	/// </summary>
	virtual void load()
	{
		m_loader = std::make_shared<Loader>();
	}

	/// <summary>
	/// Unloads the scene. Cleans up the loader and resets resources.
	/// Can be overridden for scene-specific unload logic.
	/// </summary>
	virtual void unload()
	{
		m_loader->cleanup();
		m_loader.reset();
	}

	virtual bool isLoaded() = 0;

	virtual void update(float deltaTime)
	{
		for (auto entity : m_entities)
		{
			// update entity first
			entity->update(deltaTime);
			entity->updateAllComponents(deltaTime);
		}
	}

	virtual void render() = 0;

	void RenderImGui() override;

protected:
	std::shared_ptr<Loader> m_loader;

private:
	bool m_toggleWireframes = false;
};