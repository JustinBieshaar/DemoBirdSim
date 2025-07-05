#include "InputManager.h"

InputManager::InputManager(GLFWwindow* win)
    : window(win)
{
}

void InputManager::Update()
{
    keys.clear();
    mouseButtons.clear();

    // Update key states
    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
    {
        keys[key] = glfwGetKey(window, key) == GLFW_PRESS;
    }

    // Update mouse button states
    for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; ++button)
    {
        mouseButtons[button] = glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    // Update mouse position
    glfwGetCursorPos(window, &mouseX, &mouseY);
}

bool InputManager::IsKeyPressed(int key) const
{
    auto it = keys.find(key);
    return it != keys.end() && it->second;
}

bool InputManager::IsMouseButtonPressed(int button) const
{
    auto it = mouseButtons.find(button);
    return it != mouseButtons.end() && it->second;
}

std::pair<double, double> InputManager::GetMousePosition() const
{
    return { mouseX, mouseY };
}