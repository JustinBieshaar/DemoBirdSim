#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include "../../Managers/IInputManager.h"

class Camera
{
public:
	Camera(std::shared_ptr<IInputManager> inputManager, glm::vec3 position, float pitch, float yaw);

	void update();
	
	glm::mat4 getViewMatrix();

private:
	std::shared_ptr<IInputManager> m_inputManager;
	glm::vec3 m_position;

	float m_pitch;
	float m_yaw;
};

