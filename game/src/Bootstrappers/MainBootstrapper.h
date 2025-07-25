#pragma once
#include "../Managers/IPlayerManager.h"
#include "../Managers/PlayerManager.h"

#include "../Managers/InputManager.h"

#include <BaseBootstrapper.h>
#include <ISceneManager.h>
#include <SceneManager.h>
#include <SignalHandler.h>

class MainBootstrapper : public SimpleDI::BaseBootstrapper
{
public:
    explicit MainBootstrapper(GLFWwindow* window) : SimpleDI::BaseBootstrapper(), m_window(window) {}

    void configureBindings() override
    {
        m_container->bind<Scenes::ISceneManager, Scenes::SceneManager>(SimpleDI::Lifetime::Singleton);
        m_container->bind<IInputManager, InputManager>(SimpleDI::Lifetime::Singleton, m_window);
        
        m_container->bind<Signals::SignalHandler, Signals::SignalHandler>(SimpleDI::Lifetime::Singleton);

        //todo: make auto inject
        m_signalHandler = m_container->resolve<Signals::SignalHandler>();
        m_container->bind<IPlayerManager, PlayerManager>(SimpleDI::Lifetime::Singleton, m_signalHandler);
    }

    void initialize() override
    {
        m_sceneManager = m_container->resolve<Scenes::ISceneManager>();
        m_inputManager = m_container->resolve<IInputManager>();
        m_signalHandler = m_container->resolve<Signals::SignalHandler>();
        m_playerManager = m_container->resolve<IPlayerManager>();
    }

    std::shared_ptr<Scenes::ISceneManager> getSceneManager() const { return m_sceneManager; }
    std::shared_ptr<IInputManager> getInputManager() const { return m_inputManager; }
    std::shared_ptr<IPlayerManager> getPlayerManager() const { return m_playerManager; }

    std::shared_ptr<Signals::SignalHandler> getSignalHandler() const { return m_signalHandler; }

private:
    std::shared_ptr<Scenes::ISceneManager> m_sceneManager;
    std::shared_ptr<IInputManager> m_inputManager;
    std::shared_ptr<Signals::SignalHandler> m_signalHandler;
    std::shared_ptr<IPlayerManager> m_playerManager;

    GLFWwindow* m_window;
};