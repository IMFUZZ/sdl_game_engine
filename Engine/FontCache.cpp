#include "FontCache.h"
#include <string>
#include <iostream>

FontCache::FontCache() {}
FontCache::~FontCache() {
	for (auto i = _fontMap.begin(); i != _fontMap.end(); i++) {
		// WIP - DJDUBE
		/*TTF_CloseFont(i->second.ttf);*/
	}
}

Font FontCache::getFont(std::string a_filePath) {
	auto fontPair = _fontMap.find(a_filePath);

#if _DEBUG
	std::string outputMessage = (fontPair == _fontMap.end()) ? "Loaded NOT cached font!" : "Loaded cached font!";
	std::cout << outputMessage << std::endl;
#endif // _DEBUG

	if (fontPair != _fontMap.end()) {
		// fontPair is a pointer to a pair
		return fontPair->second;
	}
	else {
		Font newFont = Font(a_filePath);
		_fontMap.insert(make_pair(a_filePath, newFont));
		return newFont;
	}
}
