#pragma once

#include "Shader.h"

class ColorShader : public Shader
{
public:
	ColorShader();

protected:
	void bindAttributes() override;
};

