#pragma once
#include <string>
#include <vector>

namespace engine
{
	class IOManager
	{
	public:
		IOManager() = delete;

		static bool readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);
	};
}