#pragma once

#include <memory>
#include <vector>
#include "../ECS/Entity.h"
#include "../ECS/Registry.h"
#include "../Rendering/Loading/Loader.h"

class Scene : public ECS::Registry
{
public:
	virtual ~Scene() = default;
	
	virtual void load()
	{
		m_loader = std::make_shared<Loader>();
	}

	virtual void unload()
	{
		m_loader->cleanup();
		m_loader.reset();
	}

	virtual bool isLoaded() = 0;

	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

protected:
	std::vector<std::unique_ptr<Entity>> m_entities;
	std::shared_ptr<Loader> m_loader;
};