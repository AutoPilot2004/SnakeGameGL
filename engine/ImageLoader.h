#pragma once
#include "GLTexture.h"
#include <string>

namespace engine
{
	class ImageLoader
	{
	public:
		ImageLoader() = delete;

		static GLTexture loadPNG(const std::string& filePath);
	};
}