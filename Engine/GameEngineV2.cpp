#include "GameEngineV2.h"


// The game process is as follow : 
// Initialize()
// Load()
// While(notExit) {
//   Update()
//   Draw()
// }
// Unload()

GameEngineV2::GameEngineV2()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fatalError("SDL initialization failed!");
	}
}


GameEngineV2::~GameEngineV2()
{
}
/*
// Function called when it is time to start the game, usually the only thing done in the main
// You should use it like this : 
//
// int main(int argc, char* args[]) {
// GameEngineV2 myEngine();
// myEngine.Start();
// }
// If you have any code to do before or after the game is done, do it before or after the start function
*/
void GameEngineV2::Start()
{
	
}

// Function called before the loop of the game is started. It is recommended to initialize the variables
// and to setup the environment here (Screen size, FPS, etc...)
void GameEngineV2::Initialize()
{

}

// Function called before the loop of the game starts, this funciton is used mainly to load textures and
// anything you'll use in your game that requires some time. You are not required to load your textures
// here but it is recommended
void GameEngineV2::Load()
{

}

// Function called in a loop while the game is running, this is where you'll do your computing and any update you need
void GameEngineV2::Update()
{

}

// Function called in a loop aswell. It is called right after Update has been called
void GameEngineV2::Draw()
{

}

// You've guessed it, this function is called after the game loop and is there to unload anything you've loaded
// It's like the destructor of your class, so make sure to unload anything that was loaded before!
void GameEngineV2::Unload()
{

}


double GameEngineV2::Tick() {
	double deltaTime = 0.0f;
	previousTick = currentTick;
	currentTick = SDL_GetTicks();
	deltaTime = (currentTick - previousTick) / 1000.0f;
	return deltaTime;
}

void GameEngineV2::RegulateFPS(int a_fps, double a_elapsedTime) {
	int deltaInNano = (a_elapsedTime*1000.0f);
	int fpsGap = ((1000.0f / a_fps) - deltaInNano);
	if (fpsGap > 0) {
		SDL_Delay(fpsGap);
	}
}