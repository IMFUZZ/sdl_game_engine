/*

*/

#include <SDL.h>
#include <iostream>
#include "game.h"

using namespace std;

Game::Game() {

}

Game::~Game() {

}

void Game::Start() {
	this->isRunning = true;
	this->Update();
}

void Game::Update() {
	SDL_Event event;
	float elapsed;
	while (this->isRunning) {
		elapsed = this->UpdateTime();
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
				case SDL_QUIT:
					this->Stop();
					break;
			}
		}
	}
}

void Game::Stop() {
	this->isRunning = false;
}

float Game::UpdateTime() {
	// WORK IN PROGRESS
	float deltaTime = 0.0f;
	this->previousTime = this->currentTime;
	this->currentTime = SDL_GetTicks();
	// Preventing the fps to flipout if the SDL_tick counter resets
	// if (this->currentTime < this->previousTime) {
	// 	this->previousTime = this->currentTime;
	// }
	deltaTime = (this->currentTime - this->previousTime) / 1000.0f;
	this->UpdateFPS(deltaTime);
	return deltaTime;
}

void Game::UpdateFPS(float elapsedTime) {
	// WORK IN PROGRESS
	cout << "ElapsedTime (sec) : " << elapsedTime << endl;
	cout << "FPS : " << 1 / elapsedTime << endl;
	int fpsGap = (0.06 - elapsedTime) * 500;
	cout << "FPS gap : " << fpsGap << endl;
	if (fpsGap > 0) {
		SDL_Delay(fpsGap);
	}
}