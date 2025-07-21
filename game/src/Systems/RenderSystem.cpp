#include "RenderSystem.h"

#include <iostream>
#include "../Global/Globals.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "../ECS/Components/TextureComponent.h"

#include <Components/Transform.h>
#include <Components/MeshComponent.h>

void RenderSystem::update(float deltaTime)
{
}

void RenderSystem::render()
{
    // todo: update this list only when entities update.
    auto renderableEntities = m_registry.getEntitiesWith<Transform, MeshComponent>();

#ifdef _DEBUG
    if (EnableWireframeMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
#endif

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

        // Use shader
        mesh->useShader();
        mesh->setModelViewProjection(transform->getTransformationMatrix(), m_camera->getViewMatrix(), m_camera->getProjectionMatrix());
        mesh->setLightLocation(m_light->m_position, m_light->m_color);

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

#ifdef _DEBUG
    if (EnableWireframeMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
#endif
}
