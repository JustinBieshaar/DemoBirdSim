#pragma once
#include "../Rendering/Loading/Loader.h"
#include "../ECS/Entity.h"

class Capsule : public Entity
{
public:
	Capsule(Loader* loader);
};