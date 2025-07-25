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

	}
};