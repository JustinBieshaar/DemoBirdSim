#pragma once
#include <Loader.h>
#include <Entity.h>
#include <GameObject.h>

#include <memory>
#include "../../Managers/IInputManager.h"

class Player : public GameObject
{
public:
	Player(std::shared_ptr<Loader> loader, std::shared_ptr<IInputManager> inputManager, const glm::vec3& position = {}, const glm::vec3& rotation = {}, const glm::vec3& scale = glm::vec3(1.0f));

	void update(float deltaTime) override;
private:
	std::shared_ptr<IInputManager> m_inputManager;
	float m_speed = 10.0f;
	float m_rotationSpeed = 5.0f;
};