#pragma once

#include <BaseBootstrapper.h>
#include <ISceneManager.h>
#include <SceneManager.h>
#include <SignalHandler.h>

#include "../Managers/InputManager.h"

class MainBootstrapper : public BaseBootstrapper
{
public:
    explicit MainBootstrapper(GLFWwindow* window) : BaseBootstrapper(), m_window(window) {}

    void configureBindings() override
    {
        m_container->bind<ISceneManager, SceneManager>(DI::Lifetime::Singleton);
        m_container->bind<IInputManager, InputManager>(DI::Lifetime::Singleton, m_window);
        
        m_container->bind<SignalHandler, SignalHandler>(DI::Lifetime::Singleton);
    }

    void initialize() override
    {
        m_sceneManager = m_container->resolve<ISceneManager>();
        m_inputManager = m_container->resolve<IInputManager>();
        m_signalHandler = m_container->resolve<SignalHandler>();
    }

    std::shared_ptr<ISceneManager> getSceneManager() const { return m_sceneManager; }
    std::shared_ptr<IInputManager> getInputManager() const { return m_inputManager; }

    std::shared_ptr<SignalHandler> getSignalHandler() const { return m_signalHandler; }

private:
    std::shared_ptr<ISceneManager> m_sceneManager;
    std::shared_ptr<IInputManager> m_inputManager;
    std::shared_ptr<SignalHandler> m_signalHandler;

    GLFWwindow* m_window;
};