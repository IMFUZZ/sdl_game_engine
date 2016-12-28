#include "ResourcesManager.h"

namespace Engine {

	TextureCache ResourcesManager::_textureCache;
	FontCache ResourcesManager::_fontCache;

	void ResourcesManager::init() { TTF_Init(); }
	void ResourcesManager::quit() { TTF_Quit(); }

	GLTexture ResourcesManager::getTexture(std::string a_filePath) {
		return _textureCache.getTexture(a_filePath);
	}

	Font ResourcesManager::getFont(std::string a_filePath) {
		return _fontCache.getFont(a_filePath);
	}

}