#pragma once

#include "Shader.h"

class TexturedShader : public Shader
{
public:
	TexturedShader();

protected:
	void bindAttributes() override;

	std::vector<int> getAttributeUsage() override { return { 0, 1, 2, 3 }; }
};

