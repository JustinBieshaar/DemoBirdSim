#pragma once
#include "../../Rendering/Loading/Loader.h"
#include "../../ECS/Entity.h"
#include "../GameObject.h"

#include <memory>

class Capsule : public GameObject
{
public:
	Capsule(std::shared_ptr<Loader> loader, const glm::vec3& position = {}, const glm::vec3& rotation = {}, const glm::vec3& scale = glm::vec3(1.0f));
};