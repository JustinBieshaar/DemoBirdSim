#pragma once

#include "../ECS/Entity.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"
#include "Camera/Camera.h"

class Renderer
{
public:
	Renderer(Camera* camera) : m_camera(camera) {}

	void render(const std::vector<Entity*>& entities);

private:
	Camera* m_camera;
};

