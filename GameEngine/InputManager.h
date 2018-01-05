#pragma once
#include <unordered_map>

class InputManager
{
public:
	InputManager();
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);
	~InputManager();

private:
	std::unordered_map<unsigned int, bool> _keyMap;
};

