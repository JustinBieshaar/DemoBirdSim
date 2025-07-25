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
    // TODO optimization: Cache this list when entities/components change instead of every frame.
    // should add a "entities updated" event in registry
    auto renderableEntities = m_registry.getEntitiesWith<ECS::Transform, ECS::MeshComponent>();

#ifdef _DEBUG
    // Enable wireframe rendering in debug builds (useful for visualizing geometry).
    if (EnableWireframeMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
#endif

    // Iterate over each entity with a Transform and MeshComponent
    for (auto entity : renderableEntities)
    {
        // Retrieve Transform component (contains model matrix)
        ECS::Transform* transform = nullptr;
        if (!entity->tryGetComponent(transform))
            continue;  // Skip if no transform

        // Retrieve Mesh component (contains VAO, shader info, etc.)
        ECS::MeshComponent* mesh = nullptr;
        if (!entity->tryGetComponent(mesh))
            continue;  // Skip if no mesh

        // Render any mesh-specific logic (like bounding boxes or custom behavior)
        mesh->render();

        // Retrieve camera's position for view matrix
        auto cameraPosition = m_camera->getComponent<ECS::Transform>();

        // --- Begin shader setup and draw ---
        mesh->useShader();  // Activate mesh shader

        // Set Model-View-Projection matrices to the shader
        mesh->setModelViewProjection(
            transform->getTransformationMatrix(), // Model
            m_camera->getViewMatrix(), // View
            m_camera->getProjectionMatrix() // Projection
        );

        // Pass light info to shader
        mesh->setLightLocation(m_light->m_position, m_light->m_color);

        // Bind VAO for the mesh
        glBindVertexArray(mesh->m_vertexArrayObject);

        // Enable shader attribute arrays (e.g., position, normals, uvs)
        mesh->enableShaderAttributes();

        // If textured, bind texture to GL_TEXTURE0
        if (entity->hasComponent<ECS::TextureComponent>())
        {
            auto texture = entity->getComponent<ECS::TextureComponent>();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
        }

        // Issue the draw call using indices (GL_TRIANGLES)
        glDrawElements(GL_TRIANGLES, mesh->m_vertexCount, GL_UNSIGNED_INT, 0);

        // Disable attribute arrays after drawing
        mesh->disableShaderAttributes();
        mesh->stopShader(); // Unbind shader
        glBindVertexArray(0); // Unbind VAO
    }

#ifdef _DEBUG
    // Reset polygon mode to fill mode (default)
    if (EnableWireframeMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
#endif
}
