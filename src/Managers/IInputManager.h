#pragma once
#include <utility>

class IInputManager
{
public:
    virtual ~IInputManager() {}
    virtual bool IsKeyPressed(int key) const = 0;
    virtual bool IsMouseButtonPressed(int button) const = 0;
    virtual std::pair<double, double> GetMousePosition() const = 0;
};