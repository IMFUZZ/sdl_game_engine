#pragma once

#include <vector>
#include <string>
#include <fstream>

class IOManager {
public:
	static bool ReadFileToBuffer(const std::string a_filePath, std::vector<unsigned char>& a_buffer);
};