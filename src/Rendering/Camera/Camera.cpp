#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>

Camera::Camera(std::shared_ptr<IInputManager> inputManager, glm::vec3 position, float pitch, float yaw)
    : m_inputManager(inputManager), m_position(position), m_pitch(pitch), m_yaw(yaw)
{
}

void Camera::update()
{
    // quick implementation todo: add events to input manager
    if (m_inputManager->isKeyPressed(GLFW_KEY_A))
    {
        m_position.x -= 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_D))
    {
        m_position.x += 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_S))
    {
        m_position.z -= 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_W))
    {
        m_position.z += 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_R))
    {
        m_position.y -= 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_F))
    {
        m_position.y += 0.01f;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_Z))
    {
        m_pitch -= 1.0f;
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_X))
    {
        m_pitch += 1.0f;
    }


    if (m_inputManager->isKeyPressed(GLFW_KEY_C))
    {
        m_yaw -= 1.0f;
    }
    if (m_inputManager->isKeyPressed(GLFW_KEY_V))
    {
        m_yaw += 1.0f;
    }
}

glm::mat4 Camera::getViewMatrix()
{
    glm::mat4 viewMatrix(1.0f); // Identity matrix

    // Apply pitch (rotation around X-axis)
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f));

    // Apply yaw (rotation around Y-axis)
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_yaw), glm::vec3(0.0f, 1.0f, 0.0f));

    // Translate by the negative camera position
    glm::vec3 negativeCameraPos = -m_position;
    viewMatrix = glm::translate(viewMatrix, m_position);

    return viewMatrix;
}
