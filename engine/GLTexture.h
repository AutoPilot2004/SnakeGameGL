#pragma once
#include <GL/glew.h>

namespace engine
{
	struct GLTexture
	{
		GLuint id;

		unsigned long width, height;

		bool operator==(GLTexture other) {
			return (other.id == id && other.width == width && other.height == height);
		}
	};
}