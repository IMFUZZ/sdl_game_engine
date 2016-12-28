#include "Font.h"
#include <string>
#include "EngineError.h"

namespace Engine {

	Font::Font() 
		: size(50), textColor({ 255, 255, 255, 255 }), backgroundColor({ 0, 0, 0, 0 }) {}

	Font::Font(std::string a_filePath) 
		: size(50), textColor({ 255, 255, 255, 255 }), backgroundColor({ 0, 0, 0, 0 }) {
		
		init(a_filePath, size);
	}

	Font::~Font() {}

	void Font::init(std::string a_filePath, int a_fontSize) {
		ttf = TTF_OpenFont(a_filePath.c_str(), a_fontSize);
		if (ttf == nullptr) {
			std::cout << TTF_GetError() << std::endl;
			fatalError("Font : '" + a_filePath + "' could not be loaded!");
		}
	}

}