#pragma once

#include "Shader.h"

class ColorShader : public Shader
{
public:
	ColorShader();

protected:
	void bindAttributes() override;

	std::vector<int> getAttributeUsage() override { return { 0, 1, 3 }; }

private:
	int lightPositionLocation;
	int lightColorLocation;
};

