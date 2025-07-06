#pragma once

#include "../BaseBootstrapper.h"
#include "../../Managers/InputManager.h"

class MainBootstrapper : public BaseBootstrapper
{
public:
    explicit MainBootstrapper(GLFWwindow* window) : BaseBootstrapper(), m_window(window) {}

    void configureBindings() override
    {
        m_container->bind<IInputManager, InputManager>(DI::Lifetime::Singleton, m_window);
    }

    void initialize() override
    {
        m_inputManager = m_container->resolve<IInputManager>();
    }

    std::shared_ptr<IInputManager> getInputManager() const { return m_inputManager; }

private:
    std::shared_ptr<IInputManager> m_inputManager;

    GLFWwindow* m_window;
};