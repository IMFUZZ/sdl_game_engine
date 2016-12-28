#include "InputManager.h"

namespace Engine {

	InputManager::InputManager() {}
	InputManager::~InputManager() {}

	void InputManager::pressKey(unsigned int keyID) {
		_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID) {
		_keyMap[keyID] = false;
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {
		return (_keyMap.count(keyID) == 1) ? _keyMap[keyID] : false;
	}

	void InputManager::setMouseCoords(float x, float y) {
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

}