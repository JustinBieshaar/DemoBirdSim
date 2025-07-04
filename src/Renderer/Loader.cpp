#include <glad/glad.h>
#include "Loader.h"

std::shared_ptr<MeshComponent> Loader::loadToMeshComponent(const std::vector<float>& vertices, const std::vector<GLuint>& indices)
{
	GLuint vao = createVertexArrayObject();
	bindIndices(indices);
	storeDataInAttributeList(0, vertices);
	glBindVertexArray(0); // Unbind VAO after setup

	return std::make_shared<MeshComponent>(vao, indices.size());
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

void Loader::storeDataInAttributeList(int attributeNumber, const std::vector<float>& data, int sizePerVertex)
{
	// Create VBO for attribute data
	createVertexBufferObject(GL_ARRAY_BUFFER, data.data(), data.size() * sizeof(float));

	// Set vertex attribute pointer and enable it
	glVertexAttribPointer(attributeNumber, sizePerVertex, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(attributeNumber);
}

void Loader::bindIndices(const std::vector<unsigned int>& indices)
{
	createVertexBufferObject(GL_ELEMENT_ARRAY_BUFFER, indices.data(), indices.size() * sizeof(unsigned int));
}

