#include "Bird.h"
#include <Components/MeshComponent.h>
#include <Components/TextureComponent.h>
#include <ColorShader.h>
#include <TexturedShader.h>
#include <ObjLoader.h>
#include <PathManager.h>

#include <iostream>

#include "../Global/Globals.h"

Bird::Bird(std::shared_ptr<Loader> loader,
	const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : GameObject(position, rotation, scale), m_loader(loader)
{
	m_colorShader = new ColorShader();
	m_texturedShader = new TexturedShader();

	PathManager::setResourceRoot(_SOLUTIONDIR);
	auto [vao, vertexCount] = ObjLoader::loadMeshFromObjFile(DefaultBird, loader);
	auto mesh = addComponent<MeshComponent>(vao, vertexCount, m_colorShader);
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
	std::cout << "bird changed!\n";

	m_name = signal.data.name;

	m_loader->unloadMesh(getComponent<MeshComponent>()->m_vertexArrayObject);
	destroyComponent<MeshComponent>();
	if (hasComponent<TextureComponent>())
	{
		m_loader->unloadTexture(getComponent<TextureComponent>()->m_textureID);
		destroyComponent<TextureComponent>();
	}

	auto birdJson = signal.data.birdJson;

	std::string texture = birdJson["texture"];
	std::string objname = birdJson["obj_name"];

	bool hasTexture = texture != "none";


	auto [vao, vertexCount] = ObjLoader::loadMeshFromObjFile(objname, m_loader);
	auto mesh = addComponent<MeshComponent>(vao, vertexCount);

	if (hasTexture)
	{
		mesh->setShader(m_texturedShader);
		addComponent<TextureComponent>(m_loader, texture);
	}
	else
	{
		mesh->setShader(m_colorShader);
	}
}
