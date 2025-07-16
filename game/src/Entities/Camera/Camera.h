#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include "../../Managers/IInputManager.h"
#include "../../Components/CameraComponent.h"
#include "../GameObject.h"

class Camera : public GameObject
{
public:
	Camera(std::shared_ptr<IInputManager> inputManager, const glm::vec3& position = {}, const float& pitch = 0.0f, const float& yaw = 0.0f);

	void update(float deltaTime) override;

	glm::mat4 getViewMatrix() { return m_camera->getViewMatrix(); }
	glm::mat4 getProjectionMatrix() { return m_camera->getProjectionMatrix(); }

private:
	std::shared_ptr<IInputManager> m_inputManager;
	std::shared_ptr<CameraComponent> m_camera;

	float m_scrollSpeed = 0.6f;
};

