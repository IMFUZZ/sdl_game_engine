#include "ImageLoader.h"

namespace Engine {

	GLTexture ImageLoader::loadPNG(std::string a_filePath) {
		GLTexture texture = {};
		std::vector<unsigned char> 
			in, out;
		unsigned long 
			width, height;

		if (IOManager::readFileToBuffer(a_filePath, in) == 1) {
			std::cout << "Could not open file : " << a_filePath << std::endl;
			if (IOManager::readFileToBuffer("../resources/textures/default.png", in) == 1) {
				fatalError("Could not open default texture!");
			}
		}
		if (decodePNG(out, width, height, &(in[0]), in.size()) == 0) {
			glGenTextures(1, &(texture.id));
			glBindTexture(GL_TEXTURE_2D, texture.id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			texture.width = width;
			texture.height = height;
		} else {
			fatalError("decodePNG failed with error!");
		}
		return texture;
	}

}