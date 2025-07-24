#include "Player.h"
#include <ObjLoader.h>
#include <Components/MeshComponent.h>
#include <ColorShader.h>
#include <TexturedShader.h>
#include <Components/TextureComponent.h>


Player::Player(std::shared_ptr<Loader> loader, std::shared_ptr<IInputManager> inputManager, const IBird* birdData, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) 
    : GameObject(position, rotation, scale), m_loader(loader), m_inputManager(inputManager)
{
    m_colorShader = std::make_unique<ColorShader>();
    m_texturedShader = std::make_unique<TexturedShader>();

    construct(birdData);
}

void Player::update(float deltaTime)
{
    // quick implementation todo: add events to input manager
    if (m_inputManager->isKeyPressed(GLFW_KEY_A))
    {
        m_transform->m_rotation.y += m_rotationSpeed * deltaTime;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_D))
    {
        m_transform->m_rotation.y -= m_rotationSpeed * deltaTime;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_S))
    {
        m_transform->m_position += m_transform->getForward() * m_speed * deltaTime;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_W))
    {
        m_transform->m_position -= m_transform->getForward() * m_speed * deltaTime;
    }
}

void Player::construct(const IBird* birdData)
{
    std::string texture = birdData->getTexture();
    std::string objname = birdData->getObj_name();

    float scale = birdData->getScale();
    m_transform->setScale(scale);

    bool invertUvs = birdData->getInvert_uvs();
    m_speed = birdData->getAcceleration();

    bool hasTexture = texture != "none";

    // runs async and uses event to apply changes.
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
        },
        false, invertUvs
    );
}
