#pragma once

#include <memory>
#include <Component.h>
#include <Components/Transform.h>
#include <Entity.h>
#include <IInspectable.h>

/// <summary>
/// Follow a target transform component.
/// </summary>
class FollowTargetComponent : public ECS::Component, public IInspectable
{
public:
	FollowTargetComponent(std::shared_ptr<ECS::Transform> target, glm::vec3 offset) : m_target(target), m_offset(offset) {	}

	void start() override { m_transform = m_owner->getComponent<ECS::Transform>(); }

	// Inherited via Component
	void update(float deltaTime) override;

private:
	std::shared_ptr<ECS::Transform> m_transform;
	std::shared_ptr<ECS::Transform> m_target;
	glm::vec3 m_offset;
	float m_distanceClamp = 0.5f;

	// Inherited via IInspectable
	void renderInspectorImGui() override;
};