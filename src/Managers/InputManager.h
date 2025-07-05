#pragma once
#include <GLFW/glfw3.h>
#include "IInputManager.h"
#include <unordered_map>

class InputManager : public IInputManager
{
public:
    InputManager(GLFWwindow* win);

    void Update();

    bool IsKeyPressed(int key) const override;
    bool IsMouseButtonPressed(int button) const override;
    std::pair<double, double> GetMousePosition() const override;

private:
    GLFWwindow* window;
    std::unordered_map<int, bool> keys;
    std::unordered_map<int, bool> mouseButtons;
    double mouseX = 0.0, mouseY = 0.0;
};