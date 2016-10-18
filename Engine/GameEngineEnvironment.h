#include <iostream>

class GameEngineEnvironment {
public:
	GameEngineEnvironment(uint16_t width, uint16_t height);
	GameEngineEnvironment(uint16_t width, uint16_t height ,uint8_t fps);
	GameEngineEnvironment(bool fullscreen);
	GameEngineEnvironment(bool fullscreen, uint8_t fps);
	GameEngineEnvironment();
	~GameEngineEnvironment();
	uint16_t ScreenWidth;
	uint16_t ScreenHeight;
	uint8_t FPS;
	bool FullScreen;
private:
	void init(uint16_t width, uint16_t height, uint8_t fps, bool fullscreen);
	static const uint16_t DEFAULT_WIDTH = 800;
	static const uint16_t DEFAULT_HEIGHT = 600;
	static const uint8_t DEFAULT_FPS = 60;
};