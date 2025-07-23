#pragma once
#include <IBird.h>

class IPlayerManager
{
public:
	virtual const IBird* getBird() = 0;
};