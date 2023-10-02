#pragma once
#include <map>
#include <string>

#include "GLTexture.h"

namespace engine
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(const std::string& filePath);

	private:
		std::map<std::string, GLTexture> m_textureMap;
	};
}