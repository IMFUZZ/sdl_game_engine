#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace Engine {

	TextureCache::TextureCache() {}
	TextureCache::~TextureCache() {}

	GLTexture TextureCache::getTexture(std::string a_filePath) {
		auto texturePair = _textureMap.find(a_filePath);
		
	#if _DEBUG
		std::string outputMessage = (texturePair == _textureMap.end()) ? "Loaded NOT cached texture!" : "Loaded cached texture!";
		std::cout << outputMessage << std::endl;
	#endif // _DEBUG
		
		if (texturePair != _textureMap.end()) {
			// texturePair is a pointer to a pair
			return texturePair->second;
		} else {
			GLTexture newTexture = ImageLoader::loadPNG(a_filePath);
			_textureMap.insert(make_pair(a_filePath, newTexture));
			return newTexture;
		}	
	}

}