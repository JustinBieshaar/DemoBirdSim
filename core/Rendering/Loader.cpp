#include "Loader.h"
#include <stb_image.h>
#include <iostream>
#include <filesystem>
#include <PathManager.h>

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
	std::string fullPath = std::filesystem::current_path().string() + "/" + PathManager::getTexturePath(path);//std::filesystem::current_path().string() + "../../../resources/textures/" + path;

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

void Loader::unloadTexture(const GLuint& textureId)
{
	if (m_textures.empty())
	{
		return;
	}

	// Delete the texture from GPU
	glDeleteTextures(1, &textureId);

	// Remove it from internal tracking list
	auto it = std::find(m_textures.begin(), m_textures.end(), textureId);
	if (it != m_textures.end())
	{
		m_textures.erase(it);
		std::cout << "Unloaded texture ID: " << textureId << std::endl;
	}
	else
	{
		std::cerr << "Attempted to unload unknown texture ID: " << textureId << std::endl;
	}
}

void Loader::unloadMesh(const GLuint& vao)
{
	if (m_vaoToVbos.empty())
	{
		return;
	}

	// Delete VBOs associated with this VAO
	if (m_vaoToVbos.count(vao))
	{
		for (GLuint vbo : m_vaoToVbos[vao])
		{
			glDeleteBuffers(1, &vbo);
			// Remove from global list
			m_vertexBufferObjects.erase(std::remove(m_vertexBufferObjects.begin(), m_vertexBufferObjects.end(), vbo), m_vertexBufferObjects.end());
		}
		m_vaoToVbos.erase(vao);
	}

	// Delete the VAO itself
	glDeleteVertexArrays(1, &vao);
	m_vertexArrayObjects.erase(std::remove(m_vertexArrayObjects.begin(), m_vertexArrayObjects.end(), vao), m_vertexArrayObjects.end());

	std::cout << "Unloaded VAO: " << vao << " and its associated VBOs.\n";
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

	for (GLuint texId : m_textures)
	{
		glDeleteTextures(1, &texId);
	}
	m_textures.clear();
	std::cout << "All textures unloaded.\n";
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

	// Track which VAO this VBO is bound to
	GLint boundVao = 0;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVao);
	if (boundVao != 0)
		m_vaoToVbos[boundVao].push_back(vbo);

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

