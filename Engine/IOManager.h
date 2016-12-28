#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace Engine {

	class IOManager {
	public:
		static int readFileToBuffer(const std::string a_filePath, std::vector<unsigned char>& a_buffer);
	};

}