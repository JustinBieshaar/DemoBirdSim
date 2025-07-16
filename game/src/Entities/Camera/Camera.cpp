#include "Camera.h"
#include <iostream>

Camera::Camera(std::shared_ptr<IInputManager> inputManager, const glm::vec3& position, const float& pitch, const float& yaw)
    : GameObject(position), m_inputManager(inputManager), m_camera(addComponent<CameraComponent>(m_transform, pitch, yaw))
{
}

void Camera::update(float deltaTime)
{
    // not ideal in an update.. maybe better to make it link to an event as well
    m_camera->Zoom(m_inputManager->getMouseScroll().second * m_scrollSpeed);

}
