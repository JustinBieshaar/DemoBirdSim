#include "ColorShader.h"


ColorShader::ColorShader(const glm::vec3& color) : Shader("BasicColor")
{
	Shader::init();

	use();
	setVec3("u_color", color);
	stop();
}

void ColorShader::bindAttributes()
{
	bindAttribute(0, "in_position");
	bindAttribute(1, "in_normal");
}
