#include "MainMenuBirdPreview.h"
#include <Event.h>

#include "../../Debug/GameLogChannels.h"
#include "../../Signals/PlayerChangedEvent.h"

#include <PathManager.h>
#include <ObjLoader.h>
#include <Components/MeshComponent.h>
#include <Components/TextureComponent.h>

MainMenuBirdPreview::MainMenuBirdPreview(std::shared_ptr<Loader> loader, std::shared_ptr<Signals::SignalHandler> signalHandler, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
	GameObject(position, rotation, scale), m_loader(loader), m_signalHandler(signalHandler)
{
    m_colorShader = std::make_unique<ColorShader>();
    m_texturedShader = std::make_unique<TexturedShader>();

    m_onBirdChangedHandler = m_signalHandler->observeEvent<PlayerChangedEvent>([this](Signals::Event<PlayerChangedEvent>& event)
		{
			BirdLogChannel.log("Bird changed from: " + (event.data.previousBird != nullptr ? event.data.previousBird->getName() : "undefined") +
				" to: " + event.data.currentBird->getName());
			onBirdChange(event.data.currentBird);
		});
}

MainMenuBirdPreview::~MainMenuBirdPreview()
{
    m_signalHandler->removeObserver(*m_onBirdChangedHandler);
}

void MainMenuBirdPreview::update(float deltaTime)
{
	m_transform->m_rotation.y += m_rotationSpeed * deltaTime;
}

void MainMenuBirdPreview::onBirdChange(const IBird* bird)
{
    std::string texture = bird->getTexture();
    std::string objname = bird->getObj_name();

    float scale = bird->getScale();
    m_transform->setScale(scale);

    bool invertUvs = bird->getInvert_uvs();

    bool hasTexture = texture != "none";

    ObjLoader::loadMeshFromObjFileAsync(objname, m_loader,
        [texture, hasTexture, this, objname](std::tuple<GLuint, size_t> result)
        {
            ECS::MeshComponent* oldMesh = nullptr;
            ECS::TextureComponent* oldTexture = nullptr;

            tryGetComponent(oldMesh);
            tryGetComponent(oldTexture);

            if (oldMesh)
            {
                m_loader->unloadMesh(oldMesh->m_vertexArrayObject);
                destroyComponent<ECS::MeshComponent>();
            }

            if (oldTexture)
            {
                m_loader->unloadTexture(oldTexture->m_textureID);
                destroyComponent<ECS::TextureComponent>();
            }

            auto [vao, vertexCount] = result;
            auto newMesh = addComponent<ECS::MeshComponent>(vao, vertexCount);

            if (hasTexture)
            {
                newMesh->setShader(m_texturedShader.get());
                addComponent<ECS::TextureComponent>(m_loader, texture);
            }
            else
            {
                newMesh->setShader(m_colorShader.get());
            }
            BirdLogChannel.log("(" + objname + ") loaded succesfully!\nProcessed " + std::to_string(vertexCount) + " vertices ;-).");
            //LoadingScreen::stop();
        },
        false, invertUvs
    );
}
