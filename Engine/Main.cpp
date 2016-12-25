#include <iostream>
#include <string>
#include "GameEngine.h"

using namespace std;

int main(int argc, char* args[]) {
	GameEngine game = GameEngine("configFile");
	game.start();
	return 0;
}