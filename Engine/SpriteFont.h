#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Font.h"
#include "Sprite.h"
#include "GLTexture.h"

class SpriteFont : virtual public Sprite
{
public:
	SpriteFont();
	SpriteFont(float a_x, float a_y, float a_width, float a_height, std::string a_message, int a_wrapWidth, Font a_font);
	~SpriteFont();
	Font font;
private:
	static int power_of_two(int input);
	GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord);
	GLfloat _textureCoord[4];
};

