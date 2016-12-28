#include <iostream>
#include <string>
#include "GameEngine.h"

int main(int argc, char* args[]) {
	Engine::GameEngine game = Engine::GameEngine("configFile");
	game.start();
	return 0;
}