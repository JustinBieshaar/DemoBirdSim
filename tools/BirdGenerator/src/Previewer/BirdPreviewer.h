#pragma once
#include <Loader.h>
#include <memory>
#include <Entity.h>
#include <SignalHandler.h>

#include "../Prefabs/Bird.h"

/// <summary>
/// This is the rendering heart of OpenGL 3D for this tool.
/// This is ensuring the birds are being rendered and displayed. Similar to using RenderSystem in game code.
/// But simplified for this tool usage.
/// 
/// As by design we are not using any scene management here, I decided to also not use
/// a ECS system for this rendering as it could be kept simple.
/// </summary>
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

