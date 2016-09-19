/*

*/

#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine(const char* a_name, int a_width, int a_height) {
	InitRequirement(a_name, a_width, a_height);
	InitShaders();
}

GameEngine::~GameEngine() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameEngine::InitShaders() {
	_colorProgram.CompileShaders("./Debug/colorShading.vert", "./Debug/colorShading.frag");
	_colorProgram.AddAttribute("vertexPosition");
	_colorProgram.AddAttribute("vertexColor");
	_colorProgram.LinkShaders();
}

void GameEngine::InitRequirement(const char* a_name, int a_width, int a_height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fatalError("SDL initialization failed!");
	}
	window = SDL_CreateWindow(
		a_name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		a_width,
		a_height,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) {
		fatalError("Could not initialize the window!");
	}
	name = a_name;
	glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		fatalError("Could not create OpenGL context!");
	}
	if (glewInit() != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GameEngine::Start() {
	isRunning = true;
	_sprite.Init(-1.0f, -1.0f, 1.0f, 1.0f);
	_playerTexture = ImageLoader::LoadPNG("./Debug/test.png");
	Update();
}

void GameEngine::Update() {
	SDL_Event event;
	double elapsed;
	while (isRunning) {
		elapsed = Tick();
		RegulateFPS(60, elapsed);
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT: // Closing the SDL_Window
				Stop();
				break;
			}
		}
		Draw();
	}
}

void GameEngine::Stop() {
	isRunning = false;
}

double GameEngine::Tick() {
	double deltaTime = 0.0f;
	previousTick = currentTick;
	currentTick = SDL_GetTicks();
	deltaTime = (currentTick - previousTick) / 1000.0f;
	return deltaTime;
}

void GameEngine::RegulateFPS(int a_fps, double a_elapsedTime) {
	int deltaInNano = (a_elapsedTime*1000.0f);
	int fpsGap = ((1000.0f / a_fps) - deltaInNano);
	if (fpsGap > 0) {
		SDL_Delay(fpsGap);
	}
}

void GameEngine::Draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.Use();
	GLuint timeLocation = _colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, currentTick / 50);
	
	_sprite.Draw();
	_colorProgram.Unuse();

	SDL_GL_SwapWindow(window);
}