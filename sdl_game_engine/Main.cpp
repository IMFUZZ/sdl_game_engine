/*

*/

#include <iostream>
#include <string>
#include "GameEngine.h"

using namespace std;

int main(int argc, char* args[]) {
	GameEngine game = GameEngine("SDL_GAME_ENGINE", 800, 600);
	game.Start();
	return 0;
}