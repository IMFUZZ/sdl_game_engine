#pragma once

#define GLEW_STATIC

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "EngineError.h"

class GameEngineV2 {
public:
	GameEngineV2();
	~GameEngineV2();
	void Initialize();
	void Start();
	void Load();
	void Update();
	void Draw();
	void Unload();

private:
	uint32_t currentTick = 0;
	uint32_t previousTick = 0;
	SDL_Window* window = nullptr;
	double Tick(); 
	void RegulateFPS(int a_fps, double a_elapsed_time);
};

