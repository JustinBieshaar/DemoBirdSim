#pragma once

#include "Component.h"

#include <IInspectable.h>
#include <Shader.h>

#include <glm/glm.hpp>
#include <memory>
#include <iostream>

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
    {}

    MeshComponent(const GLuint& vao, const unsigned int& vertexCount, Shader* shader)
        : m_vertexArrayObject(vao), m_vertexCount(vertexCount), m_shader(shader)
    {}

    void setShader(Shader* shader)
    {
        m_shader = shader;
        setRepeat(1); // Default repeat
    }

    void render()
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        // bind VAO + draw here
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

    void setModelViewProjection(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
    {
        if (m_shader)
        {
            m_shader->setMat4("u_model", model);
            m_shader->setMat4("u_view", view);
            m_shader->setMat4("u_projection", projection);
        }
    }

    void setLightLocation(glm::vec3 lightPosition, glm::vec3 lightColor)
    {
        if (m_shader)
        {
            m_shader->setVec3("u_lightPosition", lightPosition);
            m_shader->setVec3("u_lightColor", lightColor);
        }
    }

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
    void RenderImGui() override;
};