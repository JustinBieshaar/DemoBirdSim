#pragma once

#include "Component.h"

class FollowTargetComponent : public Component
{
public:
	// Inherited via Component
	void update(float deltaTime) override;
};