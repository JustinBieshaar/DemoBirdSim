#include "Bird.h"
#include <Components/MeshComponent.h>
#include <Components/TextureComponent.h>
#include <ColorShader.h>
#include <TexturedShader.h>
#include <ObjLoader.h>
#include <PathManager.h>

#include <iostream>

#include "../Global/Globals.h"
#include "../Debug/LogChannels.h"
#include "../Debug/LoadingScreen.h"

Bird::Bird(std::shared_ptr<Loader> loader,
	const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : GameObject(position, rotation, scale), m_loader(loader)
{
	m_colorShader = new ColorShader();
	m_texturedShader = new TexturedShader();
}

void Bird::subscribeSignals(std::shared_ptr<SignalHandler> signalHandler)
{
	signalHandler->observeEvent<ChangeBirdSignal>(
		[this](Event<ChangeBirdSignal>& event) { onBirdChanged(event); }
	);
}

void Bird::update(float deltaTime)
{
	m_transform->m_rotation.y += m_rotationSpeed * deltaTime;

	m_test += deltaTime;
}

void Bird::onBirdChanged(Event<ChangeBirdSignal>& signal)
{
	m_name = signal.data.name;

	auto birdJson = signal.data.birdJson;

	std::string texture = birdJson["texture"];
	std::string objname = birdJson["obj_name"];

	float scale = birdJson["scale"].get<float>();
	m_transform->setScale(scale);

	bool invertUvs = birdJson["invert_uvs"].get<bool>();

	bool hasTexture = texture != "none";

	PathManager::setResourceRoot(_SOLUTIONDIR);

    BirdLogChannel.log("Loading bird (" + m_name + ")");

    LoadingScreen::start("Loading bird (" + m_name + ")");

	// runs async and uses event to apply changes.
	ObjLoader::loadMeshFromObjFileAsync(objname, m_loader,
		[texture, hasTexture, this](std::tuple<GLuint, size_t> result)
		{
            MeshComponent* oldMesh = nullptr;
            TextureComponent* oldTexture = nullptr;

            tryGetComponent(oldMesh);
            tryGetComponent(oldTexture);

            if (oldMesh)
            {
                m_loader->unloadMesh(oldMesh->m_vertexArrayObject);
                destroyComponent<MeshComponent>();
            }

            if (oldTexture)
            {
                m_loader->unloadTexture(oldTexture->m_textureID);
                destroyComponent<TextureComponent>();
            }

            auto [vao, vertexCount] = result;
            auto newMesh = addComponent<MeshComponent>(vao, vertexCount);

            if (hasTexture)
            {
                newMesh->setShader(m_texturedShader);
                addComponent<TextureComponent>(m_loader, texture);
            }
            else
            {
                newMesh->setShader(m_colorShader);
            }
            BirdLogChannel.log("(" + m_name + ") loaded succesfully!\nProcessed " + std::to_string(vertexCount) + " vertices ;-).");
            LoadingScreen::stop();
		},
		false, invertUvs
	);
}
