#pragma once

#include "../ECS/Components/MeshComponent.h"

#include <memory>
#include <vector>
#include <GLFW/glfw3.h>

class Loader
{
public: 
	std::shared_ptr<MeshComponent> loadToMeshComponent(const std::vector<float>& vertices, const std::vector<GLuint>& indices);
	void cleanup();

private:
	std::vector<GLuint> m_vertexArrayObjects;
	std::vector<GLuint> m_vertexBufferObjects;

	GLuint createVertexArrayObject();
	GLuint createVertexBufferObject(GLenum target, const void* data, size_t size);

	void storeDataInAttributeList(int attributeNumber, const std::vector<float>& data, int sizePerVertex = 3);
	void bindIndices(const std::vector<unsigned int>& indices);
};