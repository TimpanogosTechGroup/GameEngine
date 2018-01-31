#pragma once
#include <unordered_map>

class InputManager
{
public:
	InputManager();
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);

	// Set properties
	void enableMouseMovement() { proccessMouseMovement = true; };
	void disableMouseMovement() { proccessMouseMovement = false; };
	void enableMouseProccessing() { proccessMouse = true; };
	void disableMouseProccessing() { proccessMouse = false; };
	void enableKeyboard() { proccessKeyboard = true; };
	void disableKeyboard() { proccessKeyboard = false; };

	bool isMouseMovementEnabled() { return proccessMouseMovement; };
	bool isMouseEnabled() { return proccessMouse; };
	bool isKeyboardEnabled() { return proccessKeyboard; };

	~InputManager();

private:
	std::unordered_map<unsigned int, bool> _keyMap;
	bool proccessMouseMovement = true;
	bool proccessKeyboard = true;
	bool proccessMouse = true;
};

