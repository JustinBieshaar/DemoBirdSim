#pragma once

class Component
{
public:
	virtual ~Component() = default;

	virtual void update(float deltaTime) = 0;
};