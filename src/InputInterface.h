/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef INPUT_INTERFACE_H
#define INPUT_INTERFACE_H

#include "InputManager.h"

class InputInterface {

	/*
	* This function updates the map and interprets them into game global input definitions
	*/
	virtual void update() = 0;

	virtual InputManager::GameInputControl getInputState() = 0;
};

#endif