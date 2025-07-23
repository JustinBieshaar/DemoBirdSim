#pragma once

#include "IPlayerManager.h"
#include <SignalHandler.h>

class PlayerManager : public IPlayerManager
{
public:
	PlayerManager(std::shared_ptr<SignalHandler> signalHandler);

	// Inherited via IPlayerManager
	std::shared_ptr<IBird> getBird() override;

private:
	std::shared_ptr<SignalHandler> m_signalHandler;
};