#pragma once
#include <memory>
#include <glm/vec3.hpp>
#include <Loader.h>
#include "../GameObject.h"

class Terrain : public GameObject
{
public:
	Terrain(std::shared_ptr<Loader> loader, const glm::vec3& position);

private:
	void generate(std::shared_ptr<Loader> loader);
};

