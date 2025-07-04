#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/fwd.hpp>

class Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;
    void stop() const;

    GLuint getID() const { return m_ID; }
    void setMat4(const std::string& name, const glm::mat4& matrix) const;

private:
    GLuint m_ID;
    std::string loadShaderSource(const std::string& filePath);
    GLuint compileShader(GLenum type, const std::string& source);
};