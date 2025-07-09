#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include "../../Managers/IInputManager.h"
#include "../../ECS/Components/CameraComponent.h"
#include "../GameObject.h"

class Camera : public GameObject
{
public:
	Camera(std::shared_ptr<IInputManager> inputManager, glm::vec3 position = {}, float pitch = 0.0f, float yaw = 0.0f);

	void update();

	glm::mat4 getViewMatrix() { return m_camera->getViewMatrix(); }

private:
	std::shared_ptr<IInputManager> m_inputManager;
	std::shared_ptr<CameraComponent> m_camera;
};

