#pragma once
#include <utility>

class IInputManager
{
public:
    virtual ~IInputManager() {}
    virtual bool isKeyPressed(int key) const = 0;
    virtual bool isMouseButtonPressed(int button) const = 0;
    virtual std::pair<double, double> getMousePosition() const = 0;
    virtual std::pair<double, double> getMouseScroll() const = 0;
    virtual void update(float deltaTime) = 0;
    virtual void lateUpdate(float deltaTime) = 0;
};