/*
Author: Ben Brenkman

Our OpenGl implementation of the RenderEngine
*/

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
	void Clear();

	// Graphics card calls
	bool CompileObject(Object& object);
	//bool CompileObjectAtt(Object& object, char attributes); // Get this to work somehow, make a very flexible rendering function
	bool RenderObject(Object& object);
	//bool RenderObject(Object& object, char attributes); // TODO send in the RenderItem and then specify how to render through the attributes char

private:
	SDL_Window* window = NULL;
	SDL_GLContext context;
};

