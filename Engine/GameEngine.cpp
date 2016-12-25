
#include "GameEngine.h"
#include "ResourcesManager.h"

GameEngine::GameEngine(std::string a_configFilePath) : _fps(60), _configFilePath(a_configFilePath) {
	ResourcesManager::init();
	initSystem();
	initDisplay();
	initShaders();
	// ----------- TMP -----------
	_sprite = Sprite(0.0f, 0.0f, 1.0f, 1.0f, "../resources/textures/default.png", 1.0f, { 255, 255, 255, 255 });
	_spriteFont = SpriteFont(0.0f, 0.0f, 1.0f, 1.0f, "FPS : " + std::to_string(_currentFps), 200, ResourcesManager::getFont("../resources/fonts/orangekid.ttf"));
	// ----------- TMP -----------
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
}

void GameEngine::initDisplay() {
	_window.create("Game engine", 800, 600, DEFAULT);
	_camera.init(_window.getWidth(), _window.getHeight());
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
		_spriteFont.setText(std::to_string(_currentFps));
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
	deltaTime = (currentTick-previousTick)/1000.0f;
	return deltaTime;
}

double GameEngine::regulateFPS() {
	long double elapsedTime = this->tick();
	long double fpsGap = (1000.0f/_fps)-(elapsedTime*1000.0f);
	if (fpsGap > 0.0)
		SDL_Delay(fpsGap);

	// Update the elapsedTime to the regulated elapsed time
	elapsedTime = (elapsedTime)+fpsGap/1000.0f;

	// 1 second / fraction of second passed
	_currentFps = 1/elapsedTime;
	return elapsedTime;
}

void GameEngine::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
	
	// set the camera matrix
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();
	_spriteBatch.draw(glm::vec4(0.0f, 0.0f, 500.0f, 500.0f), _sprite);
	_spriteBatch.draw(glm::vec4(0.0f, 0.0f, _spriteFont.getTexture().width, _spriteFont.getTexture().height), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _spriteFont.getTexture().id, 0.0f, {255, 255, 255, 255});
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	_window.swapBuffer();
}