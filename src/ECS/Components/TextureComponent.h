#pragma once

#include "../../Rendering/Loading/Loader.h"
#include "Component.h"

struct TextureComponent : public Component
{
	GLuint m_textureID;

	TextureComponent(Loader* loader)
	{
		m_textureID = loader->loadTexture("test.png");
	}
};