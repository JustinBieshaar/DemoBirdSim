#pragma once

#include <BaseBootstrapper.h>
#include "../Managers/InputManager.h"
#include "../Scenes/ISceneManager.h"
#include "../Scenes/SceneManager.h"

// Add game specific services here.
class GameBootstrapper : public SimpleDI::BaseBootstrapper
{
	void configureBindings() override
	{
		// empty binding for now. In here game specific services could be bound like;
		// a world-service or a resources-service or anything else that's game specific.
	}
};