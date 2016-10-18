/*

*/

#include <iostream>
#include <string>
#include "Engine/GameEngine.h"
#include "Engine/GameEngineV2.h"
#include "Engine/BaseEntity.h"

using namespace std;

int main(int argc, char* args[]) {
	GameEngine game = GameEngine();
	game.start();

	return 0;
}