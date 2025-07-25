#pragma once

#include "IPlayerManager.h"
#include <SignalHandler.h>

/// <summary>
/// Just holds IBird data which is chosen by charactar selection
/// </summary>
class PlayerManager : public IPlayerManager
{
public:
	PlayerManager(std::shared_ptr<Signals::SignalHandler> signalHandler);

	// Inherited via IPlayerManager
	const IBird* getBird() override;

private:
	std::shared_ptr<Signals::SignalHandler> m_signalHandler;

	const IBird* m_bird;
};