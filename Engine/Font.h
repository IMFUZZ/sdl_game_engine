#pragma once
#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>


namespace Engine {

	class Font
	{
	public:
		Font();
		Font(std::string a_filePath);
		~Font();
		void init(std::string a_filePath, int a_fontSize);
		int size;
		TTF_Font* ttf;
		SDL_Color textColor;
		SDL_Color backgroundColor;
	};

}