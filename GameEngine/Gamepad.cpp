#include "Gamepad.h"

Gamepad::Gamepad(int playerNumber)
{
	// Set the Controller Number
	_controllerNum = playerNumber - 1;
}

XINPUT_STATE Gamepad::GetState()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}

bool Gamepad::IsConnected()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	if (Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Gamepad::Vibrate(int leftVal, int rightVal)
{
	// Create a Vibraton State
	XINPUT_VIBRATION Vibration;

	// Zeroise the Vibration
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = leftVal;
	Vibration.wRightMotorSpeed = rightVal;

	// Vibrate the controller
	XInputSetState(_controllerNum, &Vibration);
}

short Gamepad::leftX() {
	short val = GetState().Gamepad.sThumbLX;
	if (val < 1000 && val > -1000) {
		return 0;
	}
	return val;
}

short Gamepad::leftY() {
	short val = GetState().Gamepad.sThumbLY;
	if (val < 1000 && val > -1000) {
		return 0;
	}
	return val;
}

short Gamepad::rightX() {
	short val = GetState().Gamepad.sThumbRX;
	if (val < 1000 && val > -1000) {
		return 0;
	}
	return val;
}

short Gamepad::rightY() {
	short val = GetState().Gamepad.sThumbRY;
	if (val < 1000 && val > -1000) {
		return 0;
	}
	return val;
}

int Gamepad::leftTrig() {
	return (int)GetState().Gamepad.bLeftTrigger;
}

int Gamepad::rightTrig() {
	return (int)GetState().Gamepad.bRightTrigger;
}