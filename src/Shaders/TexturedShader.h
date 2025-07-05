#pragma once

#include "Shader.h"

class TexturedShader : public Shader
{
public:
	TexturedShader();

protected:
	void bindAttributes() override;
};

