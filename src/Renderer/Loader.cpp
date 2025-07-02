#include "Loader.h"
#include <backends/imgui_impl_opengl3_loader.h>
#include <glad/glad.h>

MeshComponent Loader::loadToMeshComponent(const std::vector<float>& vertices, const std::vector<int>& indices)
{
	GLuint vaoID = createVertexArrayObject();
	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, vertices);
	unbindVertexArrayObject();
	return MeshComponent();
}

void Loader::cleanup()
{
	for (auto vao : m_vertexArrayObjects)
	{
		glDeleteVertexArrays(1, &vao);
	}
	m_vertexArrayObjects.clear();

	for (auto vbo : m_vertexBufferObjects)
	{
		glDeleteBuffers(1, &vbo);
	}
	m_vertexBufferObjects.clear();
}

GLuint Loader::createVertexArrayObject()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	m_vertexArrayObjects.push_back(vao);
	return vao;
}

GLuint Loader::createVertexBufferObject(GLenum target, const void* data, size_t size)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(target, vbo);
	glBufferData(target, size, data, GL_STATIC_DRAW);
	m_vertexBufferObjects.push_back(vbo);
	return vbo;
}

void Loader::bindIndicesBuffer(const std::vector<int>& indices)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	m_vertexBufferObjects.push_back(vboID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Loader::storeDataInAttributeList(int attributeNumber, const std::vector<float>& data, int sizePerVertex = 3)
{
	// Create VBO for attribute data
	createVertexBufferObject(GL_ARRAY_BUFFER, data.data(), data.size() * sizeof(float));

	// Set vertex attribute pointer and enable it
	glVertexAttribPointer(attributeNumber, sizePerVertex, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(attributeNumber);
}

GLuint Loader::storeDataInIntBuffer(const std::vector<int>& indices)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
	return bufferID;
}

