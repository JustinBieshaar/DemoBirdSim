#include "Loader.h"
#include <stb_image.h>
#include <iostream>
#include <filesystem>

std::tuple<GLuint, size_t> Loader::loadToMeshComponent(const std::vector<float>& vertices, const std::vector<float>& textureCoordinates, const std::vector<float>& normals, const std::vector<GLuint>& indices)
{
	GLuint vao = createVertexArrayObject();
	bindIndices(indices);
	storeDataInAttributeList(0, vertices, 3);
	storeDataInAttributeList(1, normals, 3);
	storeDataInAttributeList(2, textureCoordinates, 2);
	glBindVertexArray(0); // Unbind VAO after setup

	return { vao, indices.size() };
}

GLuint Loader::loadTexture(const std::string& path)
{
	std::string fullPath = std::filesystem::current_path().string() + "../../../resources/" + path;

	int width, height, nrChannels;
	unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cerr << "Failed to load texture: " << fullPath << std::endl;
		return 0;
	}

	GLenum format = {};
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Upload texture to GPU
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Set texture parameters (wrapping and filtering)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data); // Free CPU image memory

	m_textures.push_back(textureID);
	return textureID;
}

void Loader::cleanup()
{
	std::cout << "clean up loader, cleaning up vao size: " << m_vertexArrayObjects.size() << " vbo size: " << m_vertexBufferObjects.size() << "\n";
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

	std::cout << "creating new vao: " << m_vertexArrayObjects.size() << "\n";
	return vao;
}

GLuint Loader::createVertexBufferObject(GLenum target, const void* data, size_t size)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(target, vbo);
	glBufferData(target, size, data, GL_STATIC_DRAW);
	m_vertexBufferObjects.push_back(vbo);

	std::cout << "creating new vbo: " << m_vertexBufferObjects.size() << "\n";
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

