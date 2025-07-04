#include "Renderer.h"

#include <glm/glm.hpp>
#include <backends/imgui_impl_opengl3_loader.h>

#include "../ECS/Components/Transform.h"
#include "../ECS/Components/MeshComponent.h"
#include <glm/ext/matrix_transform.hpp>

#include <iostream>
#include "../Global/Globals.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <GLFW/glfw3.h>

void Renderer::render(const std::vector<Entity*>& entities)
{
    for (const auto& entity : entities)
    {
        Transform transform;
        MeshComponent mesh;
        if (!entity->tryGetComponent<Transform>(transform))
            continue;

        if (!entity->tryGetComponent<MeshComponent>(mesh))
            continue;

        // Build model matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform.m_position);
        model = glm::scale(model, transform.m_scale);
        model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Window_Width / Window_Height, 0.1f, 100.0f);

        // Use shader
        if (mesh.m_shader)
        {
            mesh.m_shader->use();
            mesh.m_shader->setMat4("u_Model", model);
            mesh.m_shader->setMat4("u_View", view);
            mesh.m_shader->setMat4("u_Projection", projection);
        }

        // Render mesh
        glBindVertexArray(mesh.m_vertexArrayObject);
        glEnableVertexAttribArray(0); // Position
        glEnableVertexAttribArray(1); // TexCoords / Normals etc.

        //glActiveTexture(GL_TEXTURE0); // Optional: bind texture here

        glDrawElements(GL_TRIANGLES, mesh.m_vertexCount, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);

       // std::cout << "tried to render: " << typeid(*entity).name() << " | vao is: " << mesh.m_vertexArrayObject << "\n";

    }
}
