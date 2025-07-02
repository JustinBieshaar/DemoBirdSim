#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <backends/imgui_impl_opengl3_loader.h>

#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"

void Renderer::render(const std::vector<Entity*>& entities)
{
    for (const auto& entity : entities)
    {
        Transform transform;
        MeshComponent mesh;
        if (!entity->HasComponent<Transform>(transform))
            continue;

        if (!entity->HasComponent<MeshComponent>(mesh))
            continue;

        auto model = glm::mat4(1.0f);
        model = glm::translate(model, transform.m_position);
        model = glm::scale(model, transform.m_scale);
        // Rotation omitted for simplicity

        // Render Mesh
            // Set shader uniforms, bind VAO, etc.
        glBindVertexArray(mesh.m_vertexArrayObject);
        // e.g., shader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, mesh.m_vertexCount, GL_UNSIGNED_INT, 0);
    }
}
