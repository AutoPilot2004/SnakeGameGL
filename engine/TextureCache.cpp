#include "TextureCache.h"

#include "ImageLoader.h"

namespace engine
{
	TextureCache::TextureCache()
	{

	}

	TextureCache::~TextureCache()
	{

	}

	GLTexture TextureCache::getTexture(const std::string& filePath)
	{
		if (m_textureMap.find(filePath) == m_textureMap.end()) {
			GLTexture newTexture = ImageLoader::loadPNG(filePath);
			m_textureMap[filePath] = newTexture;
		}

		return m_textureMap[filePath];
	}
}