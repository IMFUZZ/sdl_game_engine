/*

*/

#include <iostream>
#include <string>
#include "GameEngine.h"
#include "GameEngineV2.h"
#include "BaseEntity.h"

using namespace std;

int main(int argc, char* args[]) {
	//GameEngineV2 Game2342;
	//Game2342.Start();
	GameEngine game("SDL_GAME_ENGINE", 800, 600);
	game.Start();

	return 0;
}