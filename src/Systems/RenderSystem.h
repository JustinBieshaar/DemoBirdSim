#pragma once
#include <glm/vec3.hpp>

#include "../ECS/System.h"
#include "../ECS/Registry.h"
#include "../Entities/Camera/Camera.h"

class RenderSystem : ECS::System
{
public:
	RenderSystem(ECS::Registry& registry, Camera* camera, glm::vec3 lightPosition)
		: m_registry(registry), m_camera(camera), m_light(lightPosition) { }

	void update(float deltaTime) override;

private:
	ECS::Registry& m_registry;
	Camera* m_camera;
	glm::vec3 m_light;
};

