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
	GameEngine game = GameEngine();
	game.start();

	return 0;
}