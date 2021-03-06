/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>
#include "RegistryEntry.h"

class InputManager : public RegistryEntry
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

	void dipatchInputEvent() {

	}

	~InputManager();

	enum AbstractControlIndex
	{
		// Start and back buttons
		AINDEX_START, // Xbox 360 Start, PS3 Start
		AINDEX_BACK_PAUSE, 
		// Xbox 360 Back, PS3 Pause
		// Left D-pad
		AINDEX_LPAD_DOWN,
		AINDEX_LPAD_UP,
		AINDEX_LPAD_LEFT,
		AINDEX_LPAD_RIGHT,
		// Right "pad" of four buttons
		AINDEX_RPAD_DOWN, // Xbox 360 A, PS3 X
		AINDEX_RPAD_UP, // Xbox 360 Y, PS3 Triangle
		AINDEX_RPAD_LEFT, // Xbox 360 X, PS3 Square
		AINDEX_RPAD_RIGHT, // Xbox 360 B, PS3 Circle
		// Left and right thumb stick buttons
		AINDEX_LSTICK_BUTTON, // Xbox 360 LThumb, PS3 L3,
		// Xbox white
		AINDEX_RSTICK_BUTTON, // Xbox 360 RThumb, PS3 R3,
		// Xbox black
		// Left and right shoulder buttons
		AINDEX_LSHOULDER, // Xbox 360 L shoulder, PS3 L1
		AINDEX_RSHOULDER, // Xbox 360 R shoulder, PS3 R1
		// Left thumb stick axes
		AINDEX_LSTICK_X,
		AINDEX_LSTICK_Y,
		// Right thumb stick axes
		AINDEX_RSTICK_X,
		AINDEX_RSTICK_Y,
		// Left and right trigger axes
		AINDEX_LTRIGGER, // Xbox 360 �Z, PS3 L2
		AINDEX_RTRIGGER, // Xbox 360 +Z, PS3 R2
	};

	enum AbstractMouseIndex
	{
		MOUSE_MOVEMENT_X,
		MOUSE_MOVEMENT_Y,
		MOUSE_BTN_RIGTH,
		MOUSE_BTN_LEFT,
		MOUSE_BTN_0,
		MOUSE_BTN_1,
		MOUSE_BTN_2,
		MOUSE_BTN_3,
		MOUSE_BTN_4,
		MOUSE_BTN_5,
		MOUSE_BTN_6,
		MOUSE_BTN_7,
		MOUSE_BTN_8,
		MOUSE_BTN_9,
		MOUSE_BTN_10,
		MOUSE_BTN_11,
		MOUSE_BTN_12,
	};

	enum GameInputControl {
		INPUT_FORWARD,
		INPUT_BACKWARD,
		INPUT_LEFT,
		INPUT_RIGHT,
		INPUT_UP,
		INPUT_DOWN,
		KEY_UP,
		KEY_DOWN,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_ESC,
	};

private:
	std::unordered_map<unsigned int, bool> _keyMap;
	bool proccessMouseMovement = true;
	bool proccessKeyboard = true;
	bool proccessMouse = true;
};

#endif