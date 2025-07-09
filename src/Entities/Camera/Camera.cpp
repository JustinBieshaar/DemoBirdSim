#include "Camera.h"
#include <iostream>

Camera::Camera(std::shared_ptr<IInputManager> inputManager, const glm::vec3& position, const float& pitch, const float& yaw)
    : GameObject(position), m_inputManager(inputManager), m_camera(addComponent<CameraComponent>(m_transform, pitch, yaw))
{
}

void Camera::update(float deltaTime)
{
    GameObject::update(deltaTime);

    // quick implementation todo: add events to input manager
    if (m_inputManager->isKeyPressed(GLFW_KEY_A))
    {
        std::cout << "move camera! \n \n";
        m_transform->m_position.x -= 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_D))
    {
        m_transform->m_position.x += 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_S))
    {
        m_transform->m_position.z -= 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_W))
    {
        m_transform->m_position.z += 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_R))
    {
        m_transform->m_position.y -= 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_F))
    {
        m_transform->m_position.y += 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_Z))
    {
        m_camera->m_pitch -= .1f;
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_X))
    {
        m_camera->m_pitch += .1f;
    }


    if (m_inputManager->isKeyPressed(GLFW_KEY_C))
    {
        m_camera->m_yaw -= .1f;
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_V))
    {
        m_camera->m_yaw += .1f;
    }

}
