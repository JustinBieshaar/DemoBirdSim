#pragma once

#include <memory>
#include "Loader.h"
#include "Component.h"

namespace ECS
{
	class TextureComponent : public Component
	{
	public:
		GLuint m_textureID;

		TextureComponent(std::shared_ptr<Loader> loader, const std::string& fileName = "default.png")
		{
			m_textureID = loader->loadTexture(fileName);
		}

		void update(float deltaTime) override;
	};
}