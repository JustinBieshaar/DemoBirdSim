#pragma once
#include <glm/vec3.hpp>

#include <memory>
#include <System.h>
#include <Registry.h>
#include "../Prefabs/Camera/Camera.h"
#include "../Prefabs/Lighting/Light.h"

class RenderSystem : public ECS::System
{
public:
	RenderSystem(ECS::Registry& registry, glm::vec3 lightPosition)
		: m_registry(registry), m_light(std::make_unique<Light>(lightPosition)) { }
	~RenderSystem() { clear(); }

	void update(float deltaTime) override;
	void render();

	void setCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }
	void clear() override { m_camera = nullptr; }

private:
	ECS::Registry& m_registry;
	std::shared_ptr<Camera> m_camera;

	std::unique_ptr<Light> m_light;
};

