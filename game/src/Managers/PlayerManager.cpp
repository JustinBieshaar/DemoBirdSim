#include "PlayerManager.h"
#include "../Signals/PlayerChangedSignal.h"

PlayerManager::PlayerManager(std::shared_ptr<Signals::SignalHandler> signalHandler) : m_bird(nullptr)
{
	signalHandler->observeSignal<PlayerChangedSignal>([this](Signals::Signal<PlayerChangedSignal>& event)
		{
			m_bird = event.data.currentBird;
		});
}

const IBird* PlayerManager::getBird()
{
    return m_bird;
}
