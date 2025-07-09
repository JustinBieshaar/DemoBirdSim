#pragma once
#include "../../Rendering/Loading/Loader.h"
#include "../../ECS/Entity.h"

#include <memory>

class Capsule : public Entity
{
public:
	Capsule(std::shared_ptr<Loader> loader);
};