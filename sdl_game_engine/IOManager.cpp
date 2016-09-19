
#include "IOManager.h"

bool IOManager::ReadFileToBuffer(const std::string a_filePath, std::vector<unsigned char>& a_buffer) {
	std::ifstream file(a_filePath, std::ios::binary);
	if (file.fail()) {
		perror(a_filePath.c_str());
		return false;
	}
	// seek to the end
	file.seekg(0, std::ios::end);

	// Get the file size
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	// reduce the file size by any header byte that might be present
	fileSize -= file.tellg();

	a_buffer.resize(fileSize);
	file.read((char *)&(a_buffer[0]), fileSize);
	file.close();
	return true;
}