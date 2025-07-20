#pragma once
#include <glm/vec3.hpp>

#include <System.h>
#include <Registry.h>
#include "../Prefabs/Camera/Camera.h"
#include "../Prefabs/Lighting/Light.h"

class RenderSystem : ECS::System
{
public:
	RenderSystem(ECS::Registry& registry, Light* light)
		: m_registry(registry), m_light(light) { }

	void update(float deltaTime) override;
	void render();

	void setCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

private:
	ECS::Registry& m_registry;
	std::shared_ptr<Camera> m_camera;

	Light* m_light;
};

