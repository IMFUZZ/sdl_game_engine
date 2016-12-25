#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

enum WindowFlags {INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4, DEFAULT = 0x0};

class Window
{
public:
	Window();
	~Window();
	int create(std::string a_title, int a_width, int a_height, unsigned int a_flags);
	void swapBuffer();
	int getWidth() { return _width; }
	int getHeight() { return _height; }
private:
	int _height, _width;
	SDL_Window* _sdlWindow;
};

