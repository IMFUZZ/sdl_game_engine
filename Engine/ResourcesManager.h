#pragma once
#include <string>
#include "TextureCache.h"
#include "FontCache.h"

class ResourcesManager {
public:
	static void init();
	static void quit();
	static GLTexture getTexture(std::string a_filePath);
	static Font getFont(std::string a_filePath);

private:
	static TextureCache _textureCache;
	static FontCache _fontCache;
};

