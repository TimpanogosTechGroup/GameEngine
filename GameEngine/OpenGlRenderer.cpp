#include "OpenGlRenderer.h"
#include <iostream>
#include <GLEW\glew.h>

OpenGlRenderer::OpenGlRenderer()
{

}


OpenGlRenderer::~OpenGlRenderer()
{
}

void OpenGlRenderer::CreateWindow(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not initialize: " << std::endl;
	}
	else {
		window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
		if (window == NULL) {
			std::cout << "Couldn't create window :(";
		}
		context = SDL_GL_CreateContext(window);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		glewInit();
		glClearColor(1, 0, 0, 1);
		glViewport(0, 0, width, height);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);


		// Standard clear depth buffer bit and color buffer bit
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void OpenGlRenderer::UpdateScreen() {
	SDL_GL_SwapWindow(window);
}
