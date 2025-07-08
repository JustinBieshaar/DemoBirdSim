#include "Renderer.h"

#include <iostream>
#include "../Global/Globals.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "../ECS/Components/TextureComponent.h"

#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"

void Renderer::render(const std::vector<Entity*>& entities)
{
    for (const auto& entity : entities)
    {
        Transform* transform = nullptr;
        if (!entity->tryGetComponent(transform))
            continue;

        MeshComponent* mesh = nullptr;
        if (!entity->tryGetComponent(mesh))
            continue;

        // Build projection
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Window_Width / Window_Height, 0.1f, 100.0f);

        // Use shader
        if (mesh->m_shader)
        {
            mesh->m_shader->use();
            mesh->setModelViewProjection(transform->getTransformationMatrix(), m_camera->getViewMatrix(), projection);
            mesh->setLightLocation(m_light);
        }

        // Render mesh
        glBindVertexArray(mesh->m_vertexArrayObject);
        mesh->m_shader->enableAttribs();

        if (entity->hasComponent<TextureComponent>())
        {
            auto texture = entity->getComponent<TextureComponent>();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
        }

        glDrawElements(GL_TRIANGLES, mesh->m_vertexCount, GL_UNSIGNED_INT, 0);

        mesh->m_shader->disableAttribs();
        glBindVertexArray(0);
    }
}
