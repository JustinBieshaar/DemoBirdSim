#pragma once

#include "../ECS/Entity.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"

class Renderer
{
public:
	void render(const std::vector<Entity*>& entities);
};

