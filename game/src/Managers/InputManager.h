#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "IInputManager.h"
#include <unordered_map>


/// <summary>
/// Input manager handling GLFW input.
/// 
/// TODO: add event listeners for specific input like:
/// "OnHorizontal" for a,d and left-arrow, right-arrow and controller input.
/// "OnVertical" for w,s and up-arrow, down-arrow and controller input.
/// And more!
/// 
/// But also to have option for remapping of input.
/// </summary>
class InputManager : public IInputManager
{
public:
    InputManager(GLFWwindow* win);

    void update(float deltaTime) override;

    bool isKeyPressed(int key) const override;
    bool isMouseButtonPressed(int button) const override;
    std::pair<double, double> getMousePosition() const override;
    std::pair<double, double> getMouseScroll() const override;

private:
    static void s_onScroll(GLFWwindow* window, double xoffset, double yoffset);
    void lateUpdate(float deltaTime) override;

private:
    GLFWwindow* m_window;
    std::unordered_map<int, bool> m_keys;
    std::unordered_map<int, bool> m_mouseButtons;
    double m_mouseX = 0.0;
    double m_mouseY = 0.0;
    double m_mouseScrollX = 0.0;
    double m_mouseScrollY = 0.0;

};