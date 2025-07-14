#pragma once

#include <memory>
#include "Component.h"
#include "Transform.h"
#include "../Entity.h"

class FollowTargetComponent : public Component, public IInspectable
{
public:
	FollowTargetComponent(std::shared_ptr<Transform> target, glm::vec3 offset) : m_target(target), m_offset(offset) {	}

	void start() override { m_transform = m_owner->getComponent<Transform>(); }

	// Inherited via Component
	void update(float deltaTime) override;

private:
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<Transform> m_target;
	glm::vec3 m_offset;

	// Inherited via IInspectable
	void RenderImGui() override;
};