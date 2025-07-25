#pragma once

#include <memory>
#include <IBird.h>

/// <summary>
/// Notifies project a new player has been selected.
/// </summary>
struct PlayerChangedSignal
{
	const IBird* previousBird;
	const IBird* currentBird;
};