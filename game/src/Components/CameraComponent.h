#pragma once

#include "Loader.h"
#include "IInspectable.h"
#include "../Global/Globals.h"
#include "Component.h"

#include <glm/ext/matrix_transform.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <Components/Transform.h>

class CameraComponent : public ECS::Component, public IInspectable
{
public:
	CameraComponent(std::shared_ptr<ECS::Transform> transform = {}, float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f) : m_transform(transform), m_pitch(pitch), m_yaw(yaw), m_roll(roll)
	{ 
		m_aspectRatio = Window_Width / Window_Height;
	}

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;

	void SetAspectRatio(float width, float height);
	void SetFOV(float fov);
	void Zoom(float delta);

	void renderInspectorImGui() override;
	void update(float deltaTime) override;

private:
	std::shared_ptr<ECS::Transform> m_transform;

	// view properties
	float m_pitch;
	float m_yaw;
	float m_roll;

	// projection properties
	float m_fov = 45.0f;
	float m_aspectRatio;
	float m_near = 0.1f;
	float m_far = 100.0f;
};