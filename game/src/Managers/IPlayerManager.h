#pragma once
#include <memory>
#include <IBird.h>

class IPlayerManager
{
public:
	virtual std::shared_ptr<IBird> getBird() = 0;
};