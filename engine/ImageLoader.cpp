#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include <iostream>
#include <GLFW/glfw3.h>

namespace engine
{
	GLTexture ImageLoader::loadPNG(const std::string& filePath)
	{
		GLTexture texture = {};

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;

		if (!(IOManager::readFileToBuffer(filePath, in))) {
			glfwTerminate();
			std::cout << "Couldn't read file to buffer!\n";
			std::cin.get();
			std::exit(1);
		}

		int errorCode = decodePNG(out, texture.width, texture.height, &in[0], in.size());

		if (errorCode != 0) {
			glfwTerminate();
			std::cout << "DecodePNG failed to decode the PNG! (Error Code: " << errorCode << ")\n";
			std::cin.get();
			std::exit(1);
		}

		glGenTextures(1, &texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.width, texture.height, GL_FALSE, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}
}