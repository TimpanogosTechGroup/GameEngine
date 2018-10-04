#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

// No MFC
#define WIN32_LEAN_AND_MEAN

// We need the Windows Header and the XInput Header
#include <windows.h>
#include <XInput.h>

// Now, the XInput Library
// NOTE: COMMENT THIS OUT IF YOU ARE NOT USING
// A COMPILER THAT SUPPORTS THIS METHOD OF LINKING LIBRARIES
#pragma comment(lib, "XInput.lib")

// XBOX Controller Class Definition
class Gamepad
{
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;
public:
	Gamepad(int playerNumber);
	~Gamepad() = default;
	XINPUT_STATE GetState();
	bool IsConnected();
	void Vibrate(int leftVal = 0, int rightVal = 0);
	short leftX();
	short leftY();
	short rightX();
	short rightY();
	int leftTrig();
	int rightTrig();
};

#endif