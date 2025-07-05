#pragma once

#include <glad/glad.h>
#include "Component.h"
#include "../../Rendering/Loading/Loader.h"

struct TextureComponent : public Component
{
	GLuint m_textureID;

	TextureComponent(Loader* loader)
	{
		m_textureID = loader->loadTexture("test.png");
	}
};