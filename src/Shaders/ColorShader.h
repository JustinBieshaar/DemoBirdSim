#pragma once

#include <glm/vec3.hpp>
#include "Shader.h"

class ColorShader : public Shader
{
public:
	ColorShader(const glm::vec3& color = {1,1,1});

protected:
	void bindAttributes() override;

	std::vector<int> getAttributeUsage() override { return { 0, 1, 3 }; }

private:
	int lightPositionLocation;
	int lightColorLocation;
};

