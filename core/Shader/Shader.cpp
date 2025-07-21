#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
#include <PathManager.h>

Shader::Shader(const std::string& name)
{
    std::string shaderBasePath = std::filesystem::current_path().string() + "/" + PathManager::getShaderPath(); //     std::string shaderBasePath = std::filesystem::current_path().string() + "/Shaders/frag-vert/";
    std::string vertexCode = loadShaderSource(shaderBasePath + name + ".vert");
    std::string fragmentCode = loadShaderSource(shaderBasePath + name + ".frag");

    m_vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
    m_fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    m_shaderId = glCreateProgram();
    glAttachShader(m_shaderId, m_vertex);
    glAttachShader(m_shaderId, m_fragment);
}

void Shader::init()
{
    bindAttributes();

    glLinkProgram(m_shaderId);

    GLint success;
    glGetProgramiv(m_shaderId, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_shaderId, 512, nullptr, infoLog);
        std::cerr << "Shader Linking Error:\n" << infoLog << std::endl;
    }

    glDeleteShader(m_vertex);
    glDeleteShader(m_fragment);
}

void Shader::use() const
{
    glUseProgram(m_shaderId);
}

void Shader::stop() const
{
    glUseProgram(0);
}

void Shader::enableAttribs()
{
    for (int attributeIndex : getAttributeUsage())
    {
        glEnableVertexAttribArray(attributeIndex);
    }
}

void Shader::disableAttribs()
{
    for (int attributeIndex : getAttributeUsage())
    {
        glDisableVertexAttribArray(attributeIndex);
    }
}

void Shader::bindAttribute(int attribute, const GLchar* variableName)
{
    glBindAttribLocation(m_shaderId, attribute, variableName);
}

std::string Shader::loadShaderSource(const std::string& filePath)
{
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compileShader(GLenum type, const std::string& source)
{
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader Compilation Error ("
            << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
            << "):\n" << infoLog << std::endl;
    }

    return shader;
}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVec3(const std::string& name, const glm::vec3& vec) const
{
    glUniform3f(glGetUniformLocation(m_shaderId, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::setInt(const std::string& name, const int& integer) const
{
    glUniform1i(glGetUniformLocation(m_shaderId, name.c_str()), integer);
}
