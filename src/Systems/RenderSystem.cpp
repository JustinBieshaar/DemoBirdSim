#include "RenderSystem.h"

#include <iostream>
#include "../Global/Globals.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "../ECS/Components/TextureComponent.h"

#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"

void RenderSystem::update(float deltaTime)
{
}

void RenderSystem::render()
{
    // todo: update this list only when entities update.
    auto renderableEntities = m_registry.getEntitiesWith<Transform, MeshComponent>();

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)Window_Width / Window_Height,
        0.1f, 100.0f);

    for (auto entity : renderableEntities)
    {
        Transform* transform = nullptr;
        if (!entity->tryGetComponent(transform))
            continue;

        MeshComponent* mesh = nullptr;
        if (!entity->tryGetComponent(mesh))
            continue;

        mesh->render();

        auto cameraPosition = m_camera->getComponent<Transform>();

        // Build projection
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Window_Width / Window_Height, 0.1f, 100.0f);

        // Use shader
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        mesh->useShader();
        mesh->setModelViewProjection(transform->getTransformationMatrix(), m_camera->getViewMatrix(), projection);
        mesh->setLightLocation(m_light);

        // Render mesh
        glBindVertexArray(mesh->m_vertexArrayObject);
        mesh->enableShaderAttributes();

        if (entity->hasComponent<TextureComponent>())
        {
            auto texture = entity->getComponent<TextureComponent>();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
        }

        glDrawElements(GL_TRIANGLES, mesh->m_vertexCount, GL_UNSIGNED_INT, 0);

        mesh->disableShaderAttributes();
        mesh->stopShader();
        glBindVertexArray(0);
    }
}
