#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include "Font.h"
#include "Sprite.h"
#include "GLTexture.h"

namespace Engine {

	class SpriteFont : virtual public Sprite
	{
	public:
		SpriteFont();
		SpriteFont(float a_x, float a_y, std::string a_text, std::string a_fontPath, float a_scale = 1.0f, int a_wrapWidth = 800);
		SpriteFont(float a_x, float a_y, std::string a_text, Font a_font, float a_scale = 1.0f, int a_wrapWidth = 800);
		~SpriteFont();
		
		std::string text;
		int wrapWidth;
		Font font;
		float scale;

		void setText(std::string a_text);

	private:
		static int power_of_two(int input);
		GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord);
		GLfloat _textureCoord[4];
	};
	
}