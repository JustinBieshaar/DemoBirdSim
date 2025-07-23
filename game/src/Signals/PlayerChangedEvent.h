#pragma once

#include <memory>
#include <IBird.h>

struct PlayerChangedEvent
{
	std::shared_ptr<IBird> previousBird;
	std::shared_ptr<IBird> currentBird;
};