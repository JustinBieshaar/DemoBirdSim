#pragma once

namespace ECS
{
	class System
	{
	public:
		virtual ~System() = default;

		virtual void update(float deltaTime) = 0;
		virtual void clear() {}
	};
}