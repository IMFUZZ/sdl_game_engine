#include "SpriteFont.h"
#include "EngineError.h"
#include "Font.h"
#include "ResourcesManager.h"

namespace Engine {

	SpriteFont::SpriteFont() {}

	SpriteFont::SpriteFont(float a_x, float a_y, std::string a_text, std::string a_fontPath, float a_scale/* = 1.0f*/, int a_wrapWidth/* = 800*/)
		: text(a_text), wrapWidth(a_wrapWidth), scale(a_scale), Sprite(a_x, a_y, 32, 32, 1.0f, {255, 255, 255, 255}) {

		font = ResourcesManager::getFont(a_fontPath);
		setText(a_text);
	}

	SpriteFont::SpriteFont(float a_x, float a_y, std::string a_text, Font a_font, float a_scale/* = 1.0f*/, int a_wrapWidth/* = 800*/)
		: text(a_text), wrapWidth(a_wrapWidth), scale(a_scale), font(a_font), Sprite(a_x, a_y, 32, 32, 1.0f, {255, 255, 255, 255}) {

		setText(a_text);
	}

	SpriteFont::~SpriteFont() {}

	void SpriteFont::setText(std::string a_text) {
		text = a_text;
		GLenum glError;
		SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font.ttf, text.c_str(), font.textColor, wrapWidth);
		if (surface == NULL)
			fatalError("SpriteFont for message : '" + text + "' could not be loaded!");
		_texture.id = SDL_GL_LoadTexture(surface, _textureCoord);
		if ((glError = glGetError()) != GL_NO_ERROR)
			printf("Warning: Couldn't create texture: 0x%x\n", glError);
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

		width = surface->w*scale;	/* Max X */
		height = surface->h*scale;	/* Max Y */

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
		
		if (image == NULL) return 0;

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

}