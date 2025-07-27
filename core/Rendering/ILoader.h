#pragma once

#include <glad/glad.h>

#include <memory>
#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>

// for dependency injection purpose.

class ILoader
{
public:
	/// <summary>
	/// Binds mesh to open gl renderign pipeline.
	/// Returns the vertex array object (vao) id and the vertex count. These can then be stored in e.g. MeshComponent
	/// to render the mesh with it's vao id and amount of vertices.
	/// </summary>
	virtual std::tuple<GLuint, size_t> loadToMeshComponent(const std::vector<float>& vertices, const std::vector<float>& textureCoordinates, const std::vector<float>& normals, const std::vector<GLuint>& indices) = 0;

	/// <summary>
	/// Loads a texture using stbi and binds it to opengl render pipeline.
	/// Returns the index the texture is stored at.
	/// </summary>
	virtual GLuint loadTexture(const std::string& path) = 0;
	virtual void unloadTexture(const GLuint& textureId) = 0;

	virtual void unloadMesh(const GLuint& vao) = 0;
	virtual void cleanup() = 0;
};