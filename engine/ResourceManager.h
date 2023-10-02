#pragma once
#include "TextureCache.h"

namespace engine
{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(const std::string& filePath);

	private:
		static TextureCache m_textureCache;
	};
}