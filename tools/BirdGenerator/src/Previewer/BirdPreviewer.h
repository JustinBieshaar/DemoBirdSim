#pragma once
#include <Loader.h>
#include <memory>
#include <Entity.h>
#include <SignalHandler.h>

#include "../Prefabs/Bird.h"

class BirdPreviewer
{
public:
	BirdPreviewer(std::shared_ptr<Loader> loader);

	void subscribeSignals(std::shared_ptr<Signals::SignalHandler> signalHandler);

	void update(float deltaTime);
	void render();

private:

	std::shared_ptr<Loader> m_loader;

	Bird* m_bird;
};

