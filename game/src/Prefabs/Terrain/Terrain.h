#pragma once
#include <memory>
#include <glm/vec3.hpp>
#include <Loader.h>
#include <GameObject.h>

class Terrain : public ECS::GameObject
{
public:
	Terrain(std::shared_ptr<Loader> loader, const glm::vec3& position);

private:
	/// <summary>
	/// Generates a flat terrain mesh grid using a fixed vertex count and size.
	/// Sets up vertices, normals, texture coordinates, and indices for rendering,
	/// and uploads them via the Loader.
	/// </summary>
	void generate(std::shared_ptr<Loader> loader);
};

