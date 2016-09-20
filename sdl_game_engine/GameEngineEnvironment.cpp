#include "GameEngineEnvironment.h"
#include <SDL2/SDL.h>

GameEngineEnvironment::GameEngineEnvironment() :GameEngineEnvironment(false) {};
GameEngineEnvironment::GameEngineEnvironment(bool fullscreen) : GameEngineEnvironment(fullscreen, DEFAULT_FPS) {};
GameEngineEnvironment::GameEngineEnvironment(bool fullscreen, uint8_t fps)
{
	uint16_t w, h;
	if (!fullscreen)
	{
		SDL_DisplayMode current;
		if (SDL_GetCurrentDisplayMode(0, &current) != 0)
		{
			SDL_Log("Could not get display mode for video display #%d: %s", 0, SDL_GetError());
		}
		else
		{
			w = current.w;
			h = current.h;
		}
	}
	init(w, h, fps, fullscreen);
}


GameEngineEnvironment::GameEngineEnvironment(uint16_t width, uint16_t height) : GameEngineEnvironment(width, height, DEFAULT_FPS) {};
GameEngineEnvironment::GameEngineEnvironment(uint16_t width, uint16_t height, uint8_t fps)
{
	init(width, height, fps, false);
}

void GameEngineEnvironment::init(uint16_t width, uint16_t height, uint8_t fps, bool fullscreen) {
	ScreenWidth = width;
	ScreenHeight = height;
	FPS = fps;
	FullScreen = fullscreen;
}

GameEngineEnvironment::~GameEngineEnvironment()
{

}

