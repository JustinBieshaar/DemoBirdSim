#pragma once

// I like to use ECS for this as System is quite a generic name.
// so something like ECS::System shows it's related to ECS
namespace ECS
{
	class System
	{
	public:
		virtual ~System() = default;

		virtual void update(float deltaTime) = 0;
		virtual void clear() {} // can be overriden
	};
}