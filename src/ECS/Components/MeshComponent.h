#pragma once

#include "Component.h"
#include "../../Shaders/Shader.h"

struct MeshComponent : Component
{
	GLuint m_vertexArrayObject; // vertex array object
	unsigned int m_vertexCount;

	Shader* m_shader;

	MeshComponent() {}

	MeshComponent(const GLuint& vao, const unsigned int& vertexCount)
		: m_vertexArrayObject(vao), m_vertexCount(vertexCount)
	{ }

	MeshComponent(const GLuint& vao, const unsigned int& vertexCount, Shader* shader)
		: m_vertexArrayObject(vao), m_vertexCount(vertexCount), m_shader(shader)
	{ }
};