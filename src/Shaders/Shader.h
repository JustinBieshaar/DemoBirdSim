#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/fwd.hpp>

class Shader
{
public:
    Shader(const std::string& name);

    /// <summary>
    /// init must be called after constructor to use bind attributes abstract method.
    /// </summary>
    void init();

    void use() const;
    void stop() const;

    GLuint getID() const { return m_shaderId; }
    void setMat4(const std::string& name, const glm::mat4& matrix) const;

protected:

    virtual void bindAttributes() = 0; // abstract

    void bindAttribute(int attribute, const GLchar* variableName);

private:
    GLuint m_shaderId;
    GLuint m_vertex;
    GLuint m_fragment;

    std::string loadShaderSource(const std::string& filePath);
    GLuint compileShader(GLenum type, const std::string& source);
};