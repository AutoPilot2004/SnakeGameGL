#include "IOManager.h"

#include <fstream>

namespace engine
{
	bool IOManager::readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath.c_str(), std::ios::binary);

		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//seek to the end
		file.seekg(0, std::ios::end);

		//Get file size
		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		//Remove the header bytes
		fileSize -= file.tellg();

		buffer.resize(fileSize);

		file.read((char *)&buffer[0], fileSize);

		file.close();

		return true;
	}
}