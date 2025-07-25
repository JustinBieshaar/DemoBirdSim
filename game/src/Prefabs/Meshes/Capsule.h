#pragma once
#include <Loader.h>
#include <Entity.h>
#include <GameObject.h>

#include <memory>

/// <summary>
/// This was a test prefab for initial model loading.
/// Just keeping it in for now as it's an ancient artifact of this project ;P
/// </summary>
class Capsule : public ECS::GameObject
{
public:
	Capsule(std::shared_ptr<Loader> loader, const glm::vec3& position = {}, const glm::vec3& rotation = {}, const glm::vec3& scale = glm::vec3(1.0f));
};