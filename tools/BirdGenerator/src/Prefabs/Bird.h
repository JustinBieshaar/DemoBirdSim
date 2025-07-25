#pragma once

#include <string>

#include <GameObject.h>
#include <Loader.h>
#include <SignalHandler.h>

#include <ColorShader.h>
#include <TexturedShader.h>

#include "../Signals/ChangeBirdSignal.h"

/// <summary>
/// Bird that's rendering the current selected bird data.
/// Using ChangeBirdSignal to change it's appearance.
/// 
/// Always unloads the previous bird when loading a new one. This could lead in recurring hic-ups when looping through large models
/// as they will not be cached. (design flaw by now)
/// </summary>
class Bird : public ECS::GameObject
{
public:
	Bird(std::shared_ptr<Loader> loader, 
		const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f));

	void subscribeSignals(std::shared_ptr<Signals::SignalHandler> signalHandler);
	void update(float deltaTime) override;

private:
	void onBirdChanged(Signals::Signal<ChangeBirdSignal>& signal);
	std::shared_ptr<Loader> m_loader;

	TexturedShader* m_texturedShader;
	ColorShader* m_colorShader;

	float m_rotationSpeed = .5f;

	std::string m_name;
};