#include "PlayerManager.h"
#include "../Signals/PlayerChangedEvent.h"

PlayerManager::PlayerManager(std::shared_ptr<SignalHandler> signalHandler) : m_bird(nullptr)
{
	signalHandler->observeEvent<PlayerChangedEvent>([this](Event<PlayerChangedEvent>& event)
		{
			m_bird = event.data.currentBird;
		});
}

const IBird* PlayerManager::getBird()
{
    return m_bird;
}
