#include "ResourceManager.h"

namespace engine
{
	TextureCache ResourceManager::m_textureCache;

	GLTexture ResourceManager::getTexture(const std::string& filePath)
	{
		return m_textureCache.getTexture(filePath);
	}
}