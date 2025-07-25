/* This file contains summaries for even the most obvious methods as it's acting as a library.
That way each method can be understood without diving into the code. I know some like and other dislike this.
So hence the heads up. ;) */

#pragma once

#include "Component.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <IInspectable.h>
#include <cmath>

namespace ECS
{
	class Transform : public Component, public IInspectable
	{
	public:
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale = glm::vec3(1.0f);

		Transform(const glm::vec3& position = {}, const glm::vec3& rotation = {}, const glm::vec3& scale = glm::vec3(1.0f), bool valuesChangableByDebug = true)
			: IInspectable(valuesChangableByDebug), m_position(position), m_rotation(rotation), m_scale(scale)
		{
		}

		/// <summary>
		/// Get transformation matrix of this transform. This is used to render the model location and orientation.
		/// </summary>
		/// <returns></returns>
		glm::mat4 getTransformationMatrix()
		{
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);

			glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1, 0, 0));
			glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0, 1, 0));
			glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0, 0, 1));

			glm::mat4 rotationMatrix = rotationZ * rotationY * rotationX; // ZYX order (common in many engines)

			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_position);

			glm::mat4 model = translationMatrix * rotationMatrix * scaleMatrix;
			return model;
		}

		/// <summary>
		/// Find forward value of current transform.
		/// Typically useful for moving object, or find their orientation what they are looking at.
		/// </summary>
		/// <returns></returns>
		glm::vec3 getForward() const
		{
			glm::vec3 forward;

			forward.x = std::cos(m_rotation.x) * std::sin(m_rotation.y);
			forward.y = -std::sin(m_rotation.x);
			forward.z = std::cos(m_rotation.x) * std::cos(m_rotation.y);

			return forward;
		}

		void renderInspectorImGui() override;
		void update(float deltaTime) override;

		/// <summary>
		/// Update scale with a factor. This will set the scale on all axis (x,y,z)
		/// </summary>
		void setScale(float scale)
		{
			m_scale = glm::vec3(scale);
		}
	};
}