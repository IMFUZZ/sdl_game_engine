/*

*/
#pragma once

#define GLEW_STATIC

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>

#include "Sprite.h"
#include "EngineError.h"
#include "GLSLProgram.h"
#include "Window.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"

class GameEngine {
public:
	GameEngine();
	~GameEngine();
	void initSystem();
	void initShaders();
	void start();
	void stop();
	void update();
	double tick();
	double regulateFPS();
	void draw();

private:
	int _screenWidth, _screenHeight, _fps, _currentFps;
	bool isRunning = false;
	int currentTick = 0;
	int previousTick = 0;
	Window _window;
	SpriteBatch _spriteBatch;
	GLSLProgram _colorProgram;
	Camera2D _camera;
	SpriteFont _spriteFont;
	Sprite _sprite;
};