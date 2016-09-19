/*

*/

#define GLEW_STATIC

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "Sprite.h"
#include "EngineError.h"
#include "GLSLProgram.h"
#include "ImageLoader.h"

class GameEngine {
	const char* name = "";
	bool isRunning = false;
	int currentTick = 0;
	int previousTick = 0;
	SDL_Window* window = NULL;
	SDL_GLContext glContext = NULL;

public:
	GameEngine(const char* a_name, int a_width, int a_height);
	~GameEngine();
	void InitRequirement(const char* a_name, int a_width, int a_height);
	void InitShaders();
	void Start();
	void Stop();
	void Update();
	double Tick();
	void RegulateFPS(int a_fps, double a_elapsedTime);
	void Draw();

private:
	Sprite _sprite;
	GLSLProgram _colorProgram;
	GLTexture _playerTexture;
};