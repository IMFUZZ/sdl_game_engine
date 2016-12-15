#include "Window.h"

#include "EngineError.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>

Window::Window() {}

Window::~Window() {
	SDL_DestroyWindow(_sdlWindow);
}

int Window::create(std::string a_title, int a_width, int a_height, unsigned int a_flags) {
	Uint32 flags = SDL_WINDOW_OPENGL;
	if (a_flags & INVISIBLE)
		flags |= SDL_WINDOW_HIDDEN;
	if (a_flags & FULLSCREEN)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (a_flags & BORDERLESS)
		flags |= SDL_WINDOW_BORDERLESS;

	_sdlWindow = SDL_CreateWindow(
		a_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		a_width,
		a_height,
		flags
	);
	if (_sdlWindow == nullptr)
		fatalError("Could not initialize the Window!");
	if (SDL_GL_CreateContext(_sdlWindow) == nullptr)
		fatalError("Could not create OpenGL context!");
	if (glewInit() != GLEW_OK)
		fatalError("Could not initialize glew!");
	
	glClearColor(0.52f, 0.80f, 0.98f, 1.0f);
	SDL_GL_SetSwapInterval(1); // Activate the vSync

	//Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#if _DEBUG
	std::printf("*** OpenGL Version : %s ***", glGetString(GL_VERSION));
#endif // _DEBUG

	return 0;
}

void Window::swapBuffer() {
	SDL_GL_SwapWindow(_sdlWindow);
}
