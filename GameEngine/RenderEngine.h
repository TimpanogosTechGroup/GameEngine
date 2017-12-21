#pragma once

class RenderEngine {
public:
	void CreateWindow(int width, int height);
	void UpdateScreen();

private:
	int window_height = 0;
	int window_width = 0;
};