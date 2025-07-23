#pragma once

#include <memory>
#include <IBird.h>

struct PlayerChangedEvent
{
	const IBird* previousBird;
	const IBird* currentBird;
};