#pragma once

#include <memory>
#include "../../Rendering/Loading/Loader.h"
#include "Component.h"

struct TextureComponent : public Component
{
	GLuint m_textureID;

	TextureComponent(std::shared_ptr<Loader> loader, const std::string& fileName = "default.png")
	{
		m_textureID = loader->loadTexture(fileName);
	}
};