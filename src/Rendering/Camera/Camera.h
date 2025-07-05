#pragma once
#include <glm/ext/matrix_float4x4.hpp>
class Camera
{
public:
	Camera(glm::vec3 position, float pitch, float yaw);

	void update();
	
	glm::mat4 getViewMatrix();

private:
	glm::vec3 m_position;

	float m_pitch;
	float m_yaw;
};

