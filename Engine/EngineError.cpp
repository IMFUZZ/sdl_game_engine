#include "EngineError.h"

namespace Engine {

	void fatalError(std::string errorMessage) {
		std::cout << "FATAL ERROR : " << errorMessage << std::endl;
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(69);
	}

}