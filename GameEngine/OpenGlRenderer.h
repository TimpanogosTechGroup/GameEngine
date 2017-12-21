#pragma once
#include "RenderEngine.h"
#include <SDL\SDL.h>

class OpenGlRenderer :
	public RenderEngine
{
public:
	OpenGlRenderer();
	~OpenGlRenderer();

	void CreateWindow(int width, int height);
	void UpdateScreen();

private:
	SDL_Window* window = NULL;
	SDL_GLContext context;
};

