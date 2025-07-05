#include "ColorShader.h"

ColorShader::ColorShader() : Shader("BasicColor")
{
	Shader::init();
}

void ColorShader::bindAttributes()
{
	bindAttribute(0, "in_position");
}
