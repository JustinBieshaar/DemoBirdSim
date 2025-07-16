#include "Player.h"
#include <ObjLoader.h>
#include <Components/MeshComponent.h>
#include "../../Shaders/ColorShader.h"
#include "../../Shaders/TexturedShader.h"
#include <Components/TextureComponent.h>


Player::Player(std::shared_ptr<Loader> loader, std::shared_ptr<IInputManager> inputManager, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) 
    : GameObject(position, rotation, scale), m_inputManager(inputManager)
{
	//todo: factory code here to generate the correct player.
	auto [vao, vertexCount] = ObjLoader::loadMeshFromObjFile("Robin-bird", loader);

	TexturedShader* shader = new TexturedShader(); // todo, no new instance here.. something like materials may be better
    auto meshComponent = addComponent<MeshComponent>(vao, vertexCount);
	meshComponent->setShader(shader);

    addComponent<TextureComponent>(loader, "robin-texture.png");
}

void Player::update(float deltaTime)
{
    // quick implementation todo: add events to input manager
    if (m_inputManager->isKeyPressed(GLFW_KEY_A))
    {
        m_transform->m_rotation.y -= m_rotationSpeed * deltaTime;
    }

    if (m_inputManager->isKeyPressed(GLFW_KEY_D))
    {
        m_transform->m_rotation.y += m_rotationSpeed * deltaTime;
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
