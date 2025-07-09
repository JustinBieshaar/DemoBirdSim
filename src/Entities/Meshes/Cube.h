#pragma once
#include "../../Rendering/Loading/Loader.h"
#include "../../ECS/Entity.h"

#include <memory>

class Cube : public Entity
{
public:
	Cube(std::shared_ptr<Loader> loader);
};

