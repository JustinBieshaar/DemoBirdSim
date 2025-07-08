#pragma once

#include "Component.h"

#include "../../Shaders/Shader.h"
#include "../../Rendering/Lighting/Light.h"

#include <glm/glm.hpp>
#include <memory>
#include <iostream>

struct MeshComponent : public Component
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

	void setModelViewProjection(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
	{
		m_shader->setMat4("u_model", model);
		m_shader->setMat4("u_view", view);
		m_shader->setMat4("u_projection", projection);
	}

	void setLightLocation(Light* light)
	{
		std::cout << "set light pos" << light->m_position.x << ", " << light->m_position.y << ", " << light->m_position.z << "\n";
		m_shader->setVec3("u_lightPosition", light->m_position);
		m_shader->setVec3("u_lightColor", light->m_color);
	}
};