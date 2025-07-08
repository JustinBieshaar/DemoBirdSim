#pragma once

#include "../../ECS/Components/MeshComponent.h"

#include <memory>
#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

class Loader
{
public: 
	std::shared_ptr<MeshComponent> loadToMeshComponent(const std::vector<float>& vertices, const std::vector<float>& textureCoordinates, const std::vector<float>& normals, const std::vector<GLuint>& indices);
	GLuint loadTexture(const std::string& path);
	void cleanup();

private:
	std::vector<GLuint> m_vertexArrayObjects;
	std::vector<GLuint> m_vertexBufferObjects;
	std::vector<GLuint> m_textures;

	GLuint createVertexArrayObject();
	GLuint createVertexBufferObject(GLenum target, const void* data, size_t size);

	void storeDataInAttributeList(int attributeNumber, const std::vector<float>& data, int sizePerVertex = 3);
	void bindIndices(const std::vector<unsigned int>& indices);
};