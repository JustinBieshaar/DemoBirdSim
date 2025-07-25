/* This file contains summaries for even the most obvious methods as it's acting as a library.
That way each method can be understood without diving into the code. I know some like and other dislike this.
So hence the heads up. ;) 

Unless some because they are dead obvious xD
*/

#pragma once

#include "Component.h"

#include <IInspectable.h>
#include <Shader.h>

#include <glm/glm.hpp>
#include <memory>
#include <iostream>

namespace ECS
{
    class MeshComponent : public Component, public IInspectable
    {
    private:
        Shader* m_shader = nullptr;

    public:
        GLuint m_vertexArrayObject = 0;
        unsigned int m_vertexCount = 0;

        MeshComponent() {}

        MeshComponent(const GLuint& vao, const unsigned int& vertexCount)
            : m_vertexArrayObject(vao), m_vertexCount(vertexCount)
        {
        }

        MeshComponent(const GLuint& vao, const unsigned int& vertexCount, Shader* shader)
            : m_vertexArrayObject(vao), m_vertexCount(vertexCount), m_shader(shader)
        {
        }

        /// <summary>
        /// Update shader for this mesh.
        /// </summary>
        /// <param name="shader"></param>
        void setShader(Shader* shader)
        {
            m_shader = shader;
            setRepeat(1); // Default repeat
        }

        /// <summary>
        /// Sets cullface
        /// </summary>
        void render()
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }

        void useShader()
        {
            if (m_shader)
            {
                m_shader->use();
            }
        }

        void stopShader()
        {
            if (m_shader)
            {
                m_shader->stop();
            }
        }

        /// <summary>
        /// Update model view projection matrices to make the model appear on the renderer
        /// </summary>
        void setModelViewProjection(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
        {
            if (m_shader)
            {
                m_shader->setMat4("u_model", model);
                m_shader->setMat4("u_view", view);
                m_shader->setMat4("u_projection", projection);
            }
        }

        void setLightLocation(const glm::vec3& lightPosition, const glm::vec3& lightColor)
        {
            if (m_shader)
            {
                m_shader->setVec3("u_lightPosition", lightPosition);
                m_shader->setVec3("u_lightColor", lightColor);
            }
        }

        /// <summary>
        /// Repeats the texture
        /// </summary>
        void setRepeat(int repeat)
        {
            if (m_shader)
            {
                m_shader->use();
                m_shader->setInt("u_repeat", repeat);
            }
        }

        void enableShaderAttributes()
        {
            if (m_shader)
            {
                m_shader->enableAttribs();
            }
        }

        void disableShaderAttributes()
        {
            if (m_shader)
            {
                m_shader->disableAttribs();
            }
        }

        void update(float deltaTime) override;


        // Inherited via IInspectable
        void renderInspectorImGui() override;
    };
}