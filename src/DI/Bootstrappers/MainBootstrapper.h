#pragma once

#include "../BaseBootstrapper.h"
#include "../../Managers/InputManager.h"
#include "../../Scenes/ISceneManager.h"
#include "../../Scenes/SceneManager.h"

class MainBootstrapper : public BaseBootstrapper
{
public:
    explicit MainBootstrapper(GLFWwindow* window) : BaseBootstrapper(), m_window(window) {}

    void configureBindings() override
    {
        m_container->bind<ISceneManager, SceneManager>(DI::Lifetime::Singleton);
        m_container->bind<IInputManager, InputManager>(DI::Lifetime::Singleton, m_window);
    }

    void initialize() override
    {
        m_sceneManager = m_container->resolve<ISceneManager>();
        m_inputManager = m_container->resolve<IInputManager>();
    }

    std::shared_ptr<ISceneManager> getSceneManager() const { return m_sceneManager; }
    std::shared_ptr<IInputManager> getInputManager() const { return m_inputManager; }

private:
    std::shared_ptr<ISceneManager> m_sceneManager;
    std::shared_ptr<IInputManager> m_inputManager;

    GLFWwindow* m_window;
};