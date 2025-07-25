#pragma once

#include <memory>
#include <IBird.h>

struct PlayerChangedSignal
{
	const IBird* previousBird;
	const IBird* currentBird;
};