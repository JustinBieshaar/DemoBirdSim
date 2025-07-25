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
        m_container->bind<IPlayerManager, PlayerManager>(SimpleDI::Lifetime::Singleton, m_container->resolve<Signals::SignalHandler>());
        m_container->resolve<IPlayerManager>(); // resolving immediately because it needs to listen to a signal.
    }

private:

    GLFWwindow* m_window;
};