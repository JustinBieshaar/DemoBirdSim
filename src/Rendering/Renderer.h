#pragma once

#include "../ECS/Entity.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"
#include "../Entities/Camera/Camera.h"
#include "../Entities/Lighting/Light.h"

class Renderer
{
public:
	Renderer(Camera* camera, Light* light) : m_camera(camera), m_light(light){}

	void render(const std::vector<Entity*>& entities);

private:
	Camera* m_camera;
	Light* m_light;
};

