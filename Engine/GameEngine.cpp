#include "GameEngine.h"
#include "ResourcesManager.h"

namespace Engine {

	GameEngine::GameEngine(std::string a_configFilePath) : _fps(60), _configFilePath(a_configFilePath) {
		ResourcesManager::init();
		initSystem();
		initDisplay();
		initShaders();
		// ----------- TMP -----------
		_sprite = Sprite(0.0f, 0.0f, 32.0f, 64.0f, "../resources/textures/0001.png");
		_spriteFont = SpriteFont(100.0f, 100.0f, "--", "../resources/fonts/retganon.ttf");
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
		glm::vec2 mouseCoords;
		while (isRunning) {
			elapsed = regulateFPS();
			while (SDL_PollEvent(&event) != 0) {
				switch (event.type) {
					case SDL_QUIT:
						stop();
						break;
					case SDL_MOUSEMOTION:
						_inputManager.setMouseCoords(event.motion.x, event.motion.y);
						mouseCoords = _inputManager.getMouseCoords();
						mouseCoords = _camera.convertScreenToWorld(mouseCoords);
						_spriteFont.setText(std::to_string(mouseCoords.x) + " | " + std::to_string(mouseCoords.y));
						break;
					case SDL_KEYDOWN:
						_inputManager.pressKey(event.key.keysym.sym);
						break;
					case SDL_KEYUP:
						_inputManager.releaseKey(event.key.keysym.sym);
						break;
					case SDL_MOUSEBUTTONDOWN:
						_inputManager.pressKey(event.key.keysym.sym);
						break;
					case SDL_MOUSEBUTTONUP:
						_inputManager.releaseKey(event.key.keysym.sym);
						break;
				}
			}
			if (_inputManager.isKeyPressed(SDLK_w)){
				_sprite.setTexture("../resources/textures/0005.png");
				_sprite.move(0.0f, 5.0f);
				//_camera.translate(glm::vec2(0.0f, -5.0f));
			}
			if (_inputManager.isKeyPressed(SDLK_s)) {
				_sprite.setTexture("../resources/textures/0001.png");
				_sprite.move(0.0f, -5.0f);
			}
				//_camera.translate(glm::vec2(0.0f, 5.0f));
			if (_inputManager.isKeyPressed(SDLK_d)){
				_sprite.setTexture("../resources/textures/0003.png");
				_sprite.move(5.0f, 0.0f);
				//_camera.translate(glm::vec2(-5.0f, 0.0f));
			}
			if (_inputManager.isKeyPressed(SDLK_a)){
				_sprite.setTexture("../resources/textures/0007.png");
				_sprite.move(-5.0f, 0.0f);
				//_camera.translate(glm::vec2(5.0f, 0.0f));
			}
			if (_inputManager.isKeyPressed(SDLK_r))
				_camera.zoom(0.05f);
			
			if (_inputManager.isKeyPressed(SDLK_f))
				_camera.zoom(-0.05f);
			
			if (_inputManager.isKeyPressed(SDLK_q))
				_sprite.setColor({0, 0, 255, 255});
			
			if (_inputManager.isKeyPressed(SDLK_ESCAPE))
				stop();

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
		long double elapsedTime = tick();
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
		_spriteBatch.draw(_sprite);
		_spriteBatch.draw(_spriteFont);
		_spriteBatch.end();
		_spriteBatch.renderBatch();

		glBindTexture(GL_TEXTURE_2D, 0);
		_colorProgram.unuse();

		_window.swapBuffer();
	}

}