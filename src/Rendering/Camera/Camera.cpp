#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, float pitch, float yaw)
    : m_position(position), m_pitch(pitch), m_yaw(yaw)
{
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
    viewMatrix = glm::translate(viewMatrix, negativeCameraPos);

    return viewMatrix;
}
