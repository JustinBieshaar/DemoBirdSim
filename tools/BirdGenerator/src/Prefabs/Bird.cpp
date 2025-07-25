#include "Bird.h"
#include <Components/MeshComponent.h>
#include <Components/TextureComponent.h>
#include <ColorShader.h>
#include <TexturedShader.h>
#include <ObjLoader.h>
#include <PathManager.h>

#include <iostream>

#include "../Global/Globals.h"
#include "../Debug/BirdGenLogChannels.h"
#include "../Debug/LoadingScreen.h"

Bird::Bird(std::shared_ptr<Loader> loader,
	const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : GameObject(position, rotation, scale), m_loader(loader)
{
	m_colorShader = new ColorShader();
	m_texturedShader = new TexturedShader();
}

void Bird::subscribeSignals(std::shared_ptr<Signals::SignalHandler> signalHandler)
{
	signalHandler->observeSignal<ChangeBirdSignal>(
		[this](Signals::Signal<ChangeBirdSignal>& event) { onBirdChanged(event); }
	);
}

void Bird::update(float deltaTime)
{
    // just a simple rotation.
    // todo add controls. (with a component ;))
	m_transform->m_rotation.y += m_rotationSpeed * deltaTime;
}

void Bird::onBirdChanged(Signals::Signal<ChangeBirdSignal>& signal)
{
    // I know I know... this is dry code from game MainMenuBirdPreview prefab as well..
    // But this must be refactored to a better use anyway. My apologies for this dry instance :'(

	m_name = signal.data.name;

	auto birdJson = signal.data.birdJson;

    // Parse properties from JSON
    std::string texture = birdJson["texture"]; // Texture file path (or "none")
    std::string objname = birdJson["obj_name"]; // .obj file path
    float scale = birdJson["scale"].get<float>(); // Scale factor for the bird's model
    bool invertUvs = birdJson["invert_uvs"].get<bool>(); // Flag to flip UVs if needed

    // Apply scale transformation to the bird model
    m_transform->setScale(scale);

    // Determine if a texture should be applied
    bool hasTexture = texture != "none";

    // Set the resource root directory for file loading (based on your solution root)
    PathManager::setResourceRoot(_SOLUTIONDIR);

    // Start the loading screen while the bird mesh is being loaded
    LoadingScreen::start("Loading bird (" + m_name + ")");

	// runs async and uses event to apply changes.
	ObjLoader::loadMeshFromObjFileAsync(objname, m_loader,
		[texture, hasTexture, this](std::tuple<GLuint, size_t> result)
		{
            ECS::MeshComponent* oldMesh = nullptr;
            ECS::TextureComponent* oldTexture = nullptr;

            // Try to get existing mesh and texture components from the entity
            tryGetComponent(oldMesh);
            tryGetComponent(oldTexture);

            // If there's an old mesh, unload and remove it
            if (oldMesh)
            {
                m_loader->unloadMesh(oldMesh->m_vertexArrayObject);
                destroyComponent<ECS::MeshComponent>();
            }

            // If there's an old texture, unload and remove it
            if (oldTexture)
            {
                m_loader->unloadTexture(oldTexture->m_textureID);
                destroyComponent<ECS::TextureComponent>();
            }

            // Extract mesh data from result
            auto [vao, vertexCount] = result;

            // Add new mesh component with the loaded VAO and vertex count
            auto newMesh = addComponent<ECS::MeshComponent>(vao, vertexCount);

            // If the bird uses a texture, add a texture component and assign textured shader
            if (hasTexture)
            {
                newMesh->setShader(m_texturedShader);
                addComponent<ECS::TextureComponent>(m_loader, texture);
            }
            else
            {
                // Otherwise, use the flat color shader
                newMesh->setShader(m_colorShader);
            }

            // End loading screen once all operations are complete
            LoadingScreen::stop();
		},
		/*withSuffix:*/ false, invertUvs
	);
}
