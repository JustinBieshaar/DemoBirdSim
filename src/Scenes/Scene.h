#pragma once

#include <memory>
#include <vector>
#include "../ECS/Entity.h"

class Scene
{
public:
	virtual ~Scene() = default;
	
	virtual void load() = 0;
	virtual void unload() = 0;

	virtual bool isLoaded() = 0;

	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

protected:
	std::vector<std::unique_ptr<Entity>> m_entities;
};