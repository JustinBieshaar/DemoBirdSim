#pragma once

#include <glad/glad.h>
#include "Component.h"
#include "../../Renderer/Loader.h"

struct TextureComponent : Component
{
	GLuint m_textureID;

	TextureComponent(Loader* loader)
	{
		m_textureID = loader->loadTexture("test.png");
	}
};