
#include "GameEngine.h"
#include "ResourcesManager.h"

GameEngine::GameEngine() : _screenWidth(800), _screenHeight(600), _fps(60) {
	ResourcesManager::init();
	initSystem();
	initShaders();
	_spriteBatch.init();
}

GameEngine::~GameEngine() {
	ResourcesManager::quit();
	SDL_Quit();
}

void GameEngine::initShaders() {
	_colorProgram.compileShaders("../resources/shaders/colorShading.vert", "../resources/shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void GameEngine::initSystem() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fatalError("SDL initialization failed!");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// ----------- TMP -----------
	_window.create("Game engine", _screenWidth, _screenHeight, DEFAULT);
	_camera.init(_screenWidth, _screenHeight);
	_sprite = Sprite(0.0f, 0.0f, 1.0f, 1.0f, "../resources/textures/default.png", 1.0f, { 255, 255, 255, 255 });
	
	// ----------- TMP -----------
}

void GameEngine::start() {
	isRunning = true;
	update();
}

void GameEngine::update() {
	SDL_Event event;
	double elapsed;
	while (isRunning) {
		elapsed = regulateFPS();
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
				case SDL_QUIT:
					stop();
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_w:
							_camera.translate(glm::vec2(0.0f, -20.0f));
							break;
						case SDLK_s:
							_camera.translate(glm::vec2(0.0f, 20.0f));
							break;
						case SDLK_d:
							_camera.translate(glm::vec2(-20.0f, 0.0f));
							break;
						case SDLK_a:
							_camera.translate(glm::vec2(20.0f, 0.0f));
							break;
						case SDLK_r:
							_camera.zoom(0.1f);
							break;
						case SDLK_f:
							_camera.zoom(-0.1f);
							break;
						case SDLK_ESCAPE:
							stop();
							break;
					}
					break;
			}
		}
		_camera.update();
		draw();
	}
}

void GameEngine::stop() {
	isRunning = false;
}

double GameEngine::tick() {
	long double deltaTime = 0.0f;
	previousTick = currentTick;
	currentTick = SDL_GetTicks();
	deltaTime = (currentTick - previousTick) / 1000.0f;
	return deltaTime;
}

double GameEngine::regulateFPS() {
	long double elapsedTime = this->tick();
	int fpsGap = (int)((1000.0f / _fps) - (elapsedTime*1000.0f));
	if (fpsGap > 0.0f) { SDL_Delay(fpsGap); }
	_currentFps = ((elapsedTime*1000.0f) + (1000.0f / _fps));
	return elapsedTime;
}

void GameEngine::draw() {
	_spriteFont = SpriteFont(0.0f, 0.0f, 1.0f, 1.0f, "FPS : " + std::to_string(_currentFps), 200, ResourcesManager::getFont("../resources/fonts/orangekid.ttf"));
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
	//GLuint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, currentTick / 50);
	
	// set the camera matrix
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();
	//_spriteBatch.draw(glm::vec4(0.0f, 0.0f, 500.0f, 500.0f), _sprite);
	_spriteBatch.draw(glm::vec4(0.0f, 0.0f, _spriteFont.getTexture().width, _spriteFont.getTexture().height), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _spriteFont.getTexture().id, 0.0f, {255, 255, 255, 255});
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	_window.swapBuffer();
}