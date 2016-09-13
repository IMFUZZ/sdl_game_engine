/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "game/game.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	Game game = Game();
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		cout << "Video initialization failed! : " << SDL_GetError() << endl;
	}
	else {
		//Create window
		window = SDL_CreateWindow(
			"SDL Tutorial", 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			SCREEN_WIDTH, 
			SCREEN_HEIGHT, 
			SDL_WINDOW_SHOWN
		);
		if (window == NULL) {
			cout << "Could not create window! : " << SDL_GetError() << endl;
		}
		else {
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x44, 0xFF, 0xFF));
			
			//Update the surface
			SDL_UpdateWindowSurface(window);

			game.Start();
			//Wait two seconds
			//SDL_Delay(2000);
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}