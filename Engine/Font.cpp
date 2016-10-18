#include "font.h"
#include <string>
#include "EngineError.h"

Font::Font() : ttf(nullptr), size(20), textColor({ 255, 255, 255, 255 }), backgroundColor({ 0, 0, 0, 0 }) {}

Font::Font(std::string a_filePath) : ttf(nullptr), size(40), textColor({ 255, 255, 255, 255 }), backgroundColor({ 0, 0, 0, 0 }) {
	init(a_filePath);
}

Font::~Font() {}

void Font::init(std::string a_filePath) {
	ttf = TTF_OpenFont(a_filePath.c_str(), size);
	if (ttf == nullptr) {
		std::cout << TTF_GetError() << std::endl;
		fatalError("Font : '" + a_filePath + "' could not be loaded!");
	}
}
