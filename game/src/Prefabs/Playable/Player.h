#pragma once
#include <Loader.h>
#include <Entity.h>
#include <GameObject.h>

#include <IBird.h>

#include <memory>
#include "../../Managers/IInputManager.h"

#include <TexturedShader.h>
#include <ColorShader.h>

class Player : public ECS::GameObject
{
public:
	Player(std::shared_ptr<Loader> loader, std::shared_ptr<IInputManager> inputManager, const IBird* birdData, const glm::vec3& position = {}, const glm::vec3& rotation = {}, const glm::vec3& scale = glm::vec3(1.0f));

	void update(float deltaTime) override;
private:
	void construct(const IBird* birdData);

	std::shared_ptr<Loader> m_loader;
	std::shared_ptr<IInputManager> m_inputManager;

	std::unique_ptr<TexturedShader> m_texturedShader;
	std::unique_ptr<ColorShader> m_colorShader;

	float m_speed = 10.0f;
	float m_rotationSpeed = 5.0f;
};