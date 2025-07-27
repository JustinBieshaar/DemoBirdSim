#pragma once

#include "ILoader.h"

class Loader : public ILoader
{
public: 
	/// <summary>
	/// Binds mesh to open gl renderign pipeline.
	/// Returns the vertex array object (vao) id and the vertex count. These can then be stored in e.g. MeshComponent
	/// to render the mesh with it's vao id and amount of vertices.
	/// </summary>
	std::tuple<GLuint, size_t> loadToMeshComponent(const std::vector<float>& vertices, const std::vector<float>& textureCoordinates, const std::vector<float>& normals, const std::vector<GLuint>& indices) override;

	/// <summary>
	/// Loads a texture using stbi and binds it to opengl render pipeline.
	/// Returns the index the texture is stored at.
	/// </summary>
	GLuint loadTexture(const std::string& path) override;
	void unloadTexture(const GLuint& textureId) override;

	void unloadMesh(const GLuint& vao) override;
	void cleanup() override;

private:
	std::vector<GLuint> m_vertexArrayObjects;
	std::vector<GLuint> m_vertexBufferObjects;

	std::unordered_map<GLuint, std::vector<GLuint>> m_vaoToVbos; // for individual deletion

	std::vector<GLuint> m_textures;

	GLuint createVertexArrayObject();
	GLuint createVertexBufferObject(GLenum target, const void* data, size_t size);

	void storeDataInAttributeList(int attributeNumber, const std::vector<float>& data, int sizePerVertex = 3);
	void bindIndices(const std::vector<unsigned int>& indices);
};