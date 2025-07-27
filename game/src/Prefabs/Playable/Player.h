#pragma once
#include <ILoader.h>
#include <Entity.h>
#include <GameObject.h>

#include <IBird.h>

#include <memory>

#include "IPlayer.h"
#include "../../Managers/IInputManager.h"
#include "../../Managers/IPlayerManager.h"
#include "../../Services/IPlayerProgressService.h"

#include <TexturedShader.h>
#include <ColorShader.h>

#include <ConstructorTraits.h>

/// <summary>
/// Player prefab which controls the player via input.
/// For now it only moves around. It should fly at some point as this evolves.
/// </summary>
class Player : public IPlayer, public ECS::GameObject
{
public:
	Player(std::shared_ptr<ILoader> loader, std::shared_ptr<IInputManager> inputManager, std::shared_ptr<IPlayerManager> playerManager, std::shared_ptr<IPlayerProgressService> playerProgressService);

	void update(float deltaTime) override;
private:
	void construct(const IBird* birdData);

	std::shared_ptr<ILoader> m_loader;
	std::shared_ptr<IInputManager> m_inputManager;
	std::shared_ptr<IPlayerProgressService> m_playerProgressService;

	std::unique_ptr<TexturedShader> m_texturedShader;
	std::unique_ptr<ColorShader> m_colorShader;

	float m_speed = 10.0f;
	float m_rotationSpeed = 5.0f;
};

template<> 
struct SimpleDI::ConstructorTraits<Player>
{
	using Args = std::tuple<
		std::shared_ptr<ILoader>, 
		std::shared_ptr<IInputManager>, 
		std::shared_ptr<IPlayerManager>, 
		std::shared_ptr<IPlayerProgressService>
	>;
};