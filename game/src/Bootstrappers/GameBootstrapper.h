#pragma once

#include <BaseBootstrapper.h>
#include <Loader.h>

#include "MainBootstrapper.h"

#include "../Managers/InputManager.h"
#include "../Scenes/SceneManager.h" // also includes interface
#include "../Services/PlayerProgressService.h" // also includes interface
#include "../Prefabs/Playable/Player.h" // also includes interface

// Add game specific services here.
class GameBootstrapper : public SimpleDI::BaseBootstrapper
{
public:
	GameBootstrapper(std::shared_ptr<MainBootstrapper> mainBootstrapper, std::shared_ptr<ILoader> loader) :
		SimpleDI::BaseBootstrapper(), m_mainBootstrapper(mainBootstrapper), m_loader(loader)
	{}

	void configureBindings() override
	{
		m_container->bindInstance(m_loader);

		// For now player progress service could also be singleton
		// but just wanted to show a basic example of a transient instance.
		// This as, lets say we have multiple players, each one owns their own progress service.
		// So, in case multiple players will be resolved, each instance has it's own progression service.
		m_container->bind<IPlayerProgressService, PlayerProgressService>(SimpleDI::Lifetime::Transient);

		// TODO: auto bind
		m_container->bind<IPlayer, Player>(SimpleDI::Lifetime::Transient);
	}

private:
	std::shared_ptr<MainBootstrapper> m_mainBootstrapper;
	std::shared_ptr<ILoader> m_loader;
};