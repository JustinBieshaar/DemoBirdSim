#include "InputManager.h"
#include <iostream>

InputManager::InputManager(GLFWwindow* win)
    : m_window(win)
{
    // required to cast back to us on static on scroll method
    glfwSetWindowUserPointer(win, this);
    glfwSetScrollCallback(win, s_onScroll);
}

void InputManager::update(float deltaTime)
{
    m_keys.clear();
    m_mouseButtons.clear();

    // Update key states
    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
    {
        m_keys[key] = glfwGetKey(m_window, key) == GLFW_PRESS;
    }

    // Update mouse button states
    for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; ++button)
    {
        m_mouseButtons[button] = glfwGetMouseButton(m_window, button) == GLFW_PRESS;
    }

    // Update mouse position
    glfwGetCursorPos(m_window, &m_mouseX, &m_mouseY);
}

bool InputManager::isKeyPressed(int key) const
{
    auto it = m_keys.find(key);
    return it != m_keys.end() && it->second;
}

bool InputManager::isMouseButtonPressed(int button) const
{
    auto it = m_mouseButtons.find(button);
    return it != m_mouseButtons.end() && it->second;
}

std::pair<double, double> InputManager::getMousePosition() const
{
    return { m_mouseX, m_mouseY };
}

std::pair<double, double> InputManager::getMouseScroll() const
{
    return { m_mouseScrollX, m_mouseScrollY };
}

void InputManager::s_onScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    InputManager* self = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (self)
    {
        self->m_mouseScrollX = xoffset;
        self->m_mouseScrollY = yoffset;
    }
}

void InputManager::lateUpdate(float deltaTime)
{
    // reset mouse scroll at the end of the frame
    if (m_mouseScrollY != 0)
    {
        m_mouseScrollY = 0.0;
    }
    if (m_mouseScrollX != 0)
    {
        m_mouseScrollX = 0.0;
    }
}
