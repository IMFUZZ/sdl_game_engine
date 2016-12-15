#include "SpriteFont.h"
#include "EngineError.h"
#include "Font.h"

SpriteFont::SpriteFont() {}

SpriteFont::SpriteFont(
	float a_x, 
	float a_y, 
	float a_width, 
	float a_height, 
	std::string a_text, 
	int a_wrapWidth, 
	Font a_font) : 
		x(a_x),
		y(a_y), 
		width(a_width),
		height(a_height),
		text(a_text),
		wrapWidth(a_wrapWidth),
		font(a_font) {}

SpriteFont::~SpriteFont() {}

void SpriteFont::setText(std::string a_text) {
	text = a_text;
	GLenum glError;
	surface = TTF_RenderText_Blended_Wrapped(font.ttf, text.c_str(), font.textColor, wrapWidth);
	if (surface == NULL) {
		fatalError("SpriteFont for message : '" + text + "' could not be loaded!");
	}
	_texture.id = SDL_GL_LoadTexture(surface, _textureCoord);
	if ((glError = glGetError()) != GL_NO_ERROR) {
		printf("Warning: Couldn't create texture: 0x%x\n", glError);
	}
	SDL_FreeSurface(surface);
}

int SpriteFont::power_of_two(int input) {
	int value = 1;
	while (value < input) { value <<= 1; }
	return value;
}

GLuint SpriteFont::SDL_GL_LoadTexture(SDL_Surface * surface, GLfloat * texcoord) {
	GLuint texture;
	SDL_Surface *image;
	SDL_Rect area;
	Uint8  saved_alpha;
	SDL_BlendMode saved_mode;

	/* Use the surface width and height expanded to powers of 2 */
	_texture.width = power_of_two(surface->w);
	_texture.height = power_of_two(surface->h);
	texcoord[0] = 0.0f;			/* Min X */
	texcoord[1] = 0.0f;			/* Min Y */
	texcoord[2] = (GLfloat)surface->w / _texture.width;	/* Max X */
	texcoord[3] = (GLfloat)surface->h / _texture.height;	/* Max Y */

	image = SDL_CreateRGBSurface(
		SDL_SWSURFACE,
		_texture.width, _texture.height,
		32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
		0x000000FF,
		0x0000FF00,
		0x00FF0000,
		0xFF000000
#else
		0xFF000000,
		0x00FF0000,
		0x0000FF00,
		0x000000FF
#endif
	);
	
	if (image == NULL) { return 0; }

	/* Save the alpha blending attributes */
	SDL_GetSurfaceAlphaMod(surface, &saved_alpha);
	SDL_SetSurfaceAlphaMod(surface, 0xFF);
	SDL_GetSurfaceBlendMode(surface, &saved_mode);
	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);

	/* Copy the surface into the GL texture image */
	area.x = 0;
	area.y = 0;
	area.w = surface->w;
	area.h = surface->h;
	SDL_BlitSurface(surface, &area, image, &area);

	/* Restore the alpha blending attributes */
	SDL_SetSurfaceAlphaMod(surface, saved_alpha);
	SDL_SetSurfaceBlendMode(surface, saved_mode);

	/* Create an OpenGL texture for the image */
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		_texture.width, _texture.height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image->pixels);
	SDL_FreeSurface(image); /* No longer needed */
	return texture;
}