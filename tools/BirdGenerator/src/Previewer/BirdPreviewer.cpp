#include "BirdPreviewer.h"
#include "BirdPreviewer.h"

#include <ObjLoader.h>
#include "../Global/Globals.h"
#include <Components/Transform.h>
#include <Components/MeshComponent.h>
#include <Components/TextureComponent.h>

BirdPreviewer::BirdPreviewer(std::shared_ptr<Loader> loader) : m_loader(loader), m_bird(new Bird(loader))
{
}

void BirdPreviewer::subscribeSignals(std::shared_ptr<Signals::SignalHandler> signalHandler)
{
    m_bird->subscribeSignals(signalHandler);
}

void BirdPreviewer::update(float deltaTime)
{
    if (!m_bird)
        return;

    m_bird->update(deltaTime);
}

void BirdPreviewer::render()
{
    if (!m_bird)
        return;

    ECS::Transform* transform = nullptr;
    if (!m_bird->tryGetComponent(transform))
        return;

    ECS::MeshComponent* mesh = nullptr;
    if (!m_bird->tryGetComponent(mesh))
        return;

    mesh->render();

    // camera settings
    auto cameraPosition = glm::vec3{ 3,0,-15 };
    glm::mat4 view = glm::translate(glm::mat4(1.0f), cameraPosition);
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)Window_Width / Window_Height,
        0.1f, 100.0f);

    // Use shader
    mesh->useShader();
    mesh->setModelViewProjection(transform->getTransformationMatrix(), view, projection);
    mesh->setLightLocation({ 0, 2, 15 }, { 1, 1, 1 }); // just using a static light

    // Render mesh
    glBindVertexArray(mesh->m_vertexArrayObject);
    mesh->enableShaderAttributes();

    if (m_bird->hasComponent<ECS::TextureComponent>())
    {
        auto texture = m_bird->getComponent<ECS::TextureComponent>();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
    }

    glDrawElements(GL_TRIANGLES, mesh->m_vertexCount, GL_UNSIGNED_INT, 0);

    mesh->disableShaderAttributes();
    mesh->stopShader();
    glBindVertexArray(0);
}
