#pragma once

#include <glad/glad.h>
#include "Loader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <filesystem>
#include <PathManager.h>

namespace ObjLoader
{
	/// <summary>
	/// Parsing face lines. This happens as soon as we enter the 'f' lines in the obj file.
	/// Each face line defines a triangle using vertex indices that reference positions,
	/// texture coordinates (UVs), and normals.
	/// This method extracts and stores those attributes for each vertex of the triangle.
	/// It handles shared vertex data properly by referencing the indexed temporary arrays.
	/// </summary>
	inline void parseFaceLine(
		const std::string& line,
		const std::vector<glm::vec3>& tempPositions,
		const std::vector<glm::vec2>& tempUVs,
		const std::vector<glm::vec3>& tempNormals,
		std::vector<float>& positions,
		std::vector<float>& uvs,
		std::vector<float>& normals,
		std::vector<GLuint>& indices
	)
	{
		std::istringstream ss(line);
		std::string prefix;
		ss >> prefix; // Skip "f"

		std::string vertexData;
		for (int i = 0; i < 3; ++i) // Only triangles
		{
			ss >> vertexData;

			std::istringstream vss(vertexData);
			std::string vStr, vtStr, vnStr;

			std::getline(vss, vStr, '/');
			std::getline(vss, vtStr, '/');
			std::getline(vss, vnStr, '/');

			int vIndex = std::stoi(vStr) - 1;
			int vtIndex = std::stoi(vtStr) - 1;
			int vnIndex = std::stoi(vnStr) - 1;

			const glm::vec3& pos = tempPositions[vIndex];
			const glm::vec2& uv = tempUVs[vtIndex];
			const glm::vec3& normal = tempNormals[vnIndex];

			positions.push_back(pos.x);
			positions.push_back(pos.y);
			positions.push_back(pos.z);

			uvs.push_back(uv.x);
			uvs.push_back(uv.y);

			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);

			GLuint index = static_cast<GLuint>(positions.size() / 3 - 1);
			indices.push_back(index);
		}
	}

	/// <summary>
	/// Reads an obj file and parses it into a MeshComponent object.
	/// This can then be used to render this mesh.
	/// </summary>
	inline std::tuple<GLuint, size_t> loadMeshFromObjFile(std::string fileName, std::shared_ptr<Loader> loader)
	{
		std::string fullPath = std::filesystem::current_path().string() + "/" + PathManager::getObjPath(fileName + ".obj");// std::filesystem::current_path().string() + "../../../resources/3d-obj/" + fileName + ".obj";
		std::ifstream file(fullPath);
		if (!file.is_open())
		{
			std::cerr << "Failed to open OBJ file: " << fullPath << std::endl;
			return {0, 0};
		}

		// storing temporary data to link them later when reaching f lines
		std::vector<glm::vec3> tempPositions;
		std::vector<glm::vec3> tempNormals;
		std::vector<glm::vec2> tempUVs;
		std::vector<int> tempIndices;

		// storing all the face datas
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> uvs;
		std::vector<GLuint> indices;

		std::string line;
		while (std::getline(file, line))
		{
			std::istringstream ss(line);
			std::string prefix;
			ss >> prefix;

			if (prefix == "v")
			{
				glm::vec3 pos;
				ss >> pos.x >> pos.y >> pos.z;

				tempPositions.push_back(pos);
			}
			else if (prefix == "vt")
			{
				glm::vec2 uv;
				ss >> uv.x >> uv.y;
				tempUVs.push_back(uv);
			}
			else if (prefix == "vn")
			{
				glm::vec3 normal;
				ss >> normal.x >> normal.y >> normal.z;
				tempNormals.push_back(normal);
			}
			else if (prefix == "f")
			{
				parseFaceLine(line, tempPositions, tempUVs, tempNormals, positions, uvs, normals, indices);
			}
		}

		auto mesh = loader->loadToMeshComponent(positions, uvs, normals, indices);

		return mesh;
	}
}

