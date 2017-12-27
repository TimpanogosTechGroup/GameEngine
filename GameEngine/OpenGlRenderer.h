#pragma once
#include "RenderEngine.h"
#include <SDL\SDL.h>
#include "FrameBuffer.h"

class OpenGlRenderer :
	public RenderEngine
{
public:
	OpenGlRenderer();
	~OpenGlRenderer();

	void CreateWindow(int width, int height);
	void UpdateScreen();
	void BindFramBuffer(FrameBuffer frame);
	void BindDefaultFrameBuffer();

private:
	SDL_Window* window = NULL;
	SDL_GLContext context;
};

