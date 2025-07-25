#pragma once
#include <Loader.h>
#include <Entity.h>
#include <GameObject.h>
#include <SignalHandler.h>
#include <IBird.h>
#include <TexturedShader.h>
#include <ColorShader.h>
#include <ObserverHandler.h>
#include <optional>

/// <summary>
/// Previewing bird in main menu.
/// </summary>
class MainMenuBirdPreview : public ECS::GameObject
{
public:
	MainMenuBirdPreview(std::shared_ptr<Loader> loader, std::shared_ptr<Signals::SignalHandler> signalHandler,
		const glm::vec3& position = {}, const glm::vec3& rotation = {}, const glm::vec3& scale = glm::vec3(1.0f));

	~MainMenuBirdPreview();

	void update(float deltaTime) override;
private:
	void onBirdChange(const IBird* bird);

	std::shared_ptr<Loader> m_loader;
	std::shared_ptr<Signals::SignalHandler> m_signalHandler;

	std::unique_ptr<TexturedShader> m_texturedShader;
	std::unique_ptr<ColorShader> m_colorShader;

	float m_rotationSpeed = 0.5f;
	std::optional<Signals::ObserverHandle> m_onBirdChangedHandler;
};