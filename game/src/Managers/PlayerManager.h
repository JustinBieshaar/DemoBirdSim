#pragma once

#include "IPlayerManager.h"
#include <SignalHandler.h>

#include <ConstructorTraits.h>

/// <summary>
/// Just holds IBird data which is chosen by charactar selection managing what bird is used
/// for the player.
/// </summary>
class PlayerManager : public IPlayerManager
{
public:
	PlayerManager() {} // default constructor for DI to operate.
	PlayerManager(std::shared_ptr<Signals::SignalHandler> signalHandler);

	// Inherited via IPlayerManager
	const IBird* getBird() override;

private:
	std::shared_ptr<Signals::SignalHandler> m_signalHandler;

	const IBird* m_bird;
};

template<>
struct SimpleDI::ConstructorTraits<PlayerManager>
{
	using Args = std::tuple<std::shared_ptr<Signals::SignalHandler>>;
};