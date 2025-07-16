#include "Camera.h"
#include <iostream>

Camera::Camera(std::shared_ptr<IInputManager> inputManager, const glm::vec3& position, const float& pitch, const float& yaw)
    : GameObject(position), m_inputManager(inputManager), m_camera(addComponent<CameraComponent>(m_transform, pitch, yaw))
{
}

void Camera::update(float deltaTime)
{

}
