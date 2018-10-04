/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::initialize() {
	Player1 = new Gamepad(1);
	if (Player1->IsConnected()) {
		enableGamepad();
		disableMouseMovement();
		disableMouseProccessing();
	}
	else {
		disableGamepad();
	}
}

void InputManager::deleteGamepad() {
	if (Player1 != NULL) {
		delete Player1;
	}
}

void InputManager::pressKey(unsigned int keyID) {
	_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
	_keyMap[keyID] = false;
}

bool InputManager::isKeyPressed(unsigned int keyID) {
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end()) {
		return it->second;
	}
	else {
		return false;
	}
}
