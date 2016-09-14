/*

*/

#include <SDL2/SDL.h>
#include <iostream>
#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine() {

}

GameEngine::~GameEngine() {

}

void GameEngine::Start() {
	this->isRunning = true;
	this->Update();
}

void GameEngine::Update() {
	SDL_Event event;
	double elapsed;
	while (this->isRunning) {
		elapsed = this->Tick();
		this->RegulateFPS(60, elapsed);
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
				case SDL_QUIT: // Closing the SDL_Window
					this->Stop();
					break;
			}
		}
	}
}

void GameEngine::Stop() {
	this->isRunning = false;
}

double GameEngine::Tick() {
	// WORK IN PROGRESS
	double deltaTime = 0.0f;
	this->previousTick = this->currentTick;
	this->currentTick = SDL_GetTicks();
	// Preventing the fps to flipout if the SDL_tick counter resets
	// if (this->currentTick < this->previousTick) {
	// 	this->previousTick = this->currentTick;
	// }
	deltaTime = (this->currentTick - this->previousTick) / 1000.0f;
	return deltaTime;
}

void GameEngine::RegulateFPS(int fps, double elapsedTime) {
	// WORK IN PROGRESS
	int deltaInMs = (elapsedTime*1000.0f);
	int fpsGap = ((1000.0f/fps) - deltaInMs);
	cout << "ElapsedTime (sec) : " << elapsedTime << endl;
	cout << "1000/fps : " << (1000.0f/fps) << " Elapsed * 1000 : " << deltaInMs << endl;
	cout << "FPS gap : " << fpsGap << endl;
	cout << "FPS : " << 1000/(deltaInMs + fpsGap)  << endl;
	if (fpsGap > 0) {
		SDL_Delay(fpsGap);
	}
}