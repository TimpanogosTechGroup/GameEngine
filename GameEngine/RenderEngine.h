/*
Author: Ben Brenkman

This is the RenderEngine class, we will have different implementations of this class that will help us keep our code really clean and prevent breaking and a lot of heart ache when we expand and try and implement VR, DirectX or go mobile
*/
#pragma once

class RenderEngine {
public:
	void CreateWindow(int width, int height);
	void UpdateScreen();
	enum Status {RUNNING, ERROR, SHUTDOWN};
	Status GetStatus() { return status; };
	void SetStatus(Status stat) { status = stat; };

private:
	int window_height = 0;
	int window_width = 0;
	Status status;
};