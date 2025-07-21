#include "TexturedShader.h"

TexturedShader::TexturedShader() : Shader("BasicTexture")
{
	Shader::init();
}

void TexturedShader::bindAttributes()
{
	bindAttribute(0, "in_position");
	bindAttribute(1, "in_normal");
	bindAttribute(2, "in_textureCoords");
}
