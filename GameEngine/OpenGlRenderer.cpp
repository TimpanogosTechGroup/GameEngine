/*
Author: Ben Brenkman
Notes: This is the rendering class for OpenGl, all calls related to OpenGl should be located in here. But for now do what you can.
		This class will help create windows, change frambuffers, bind textures, render objects, and do all that crazy rending stuff
*/

#include "OpenGlRenderer.h"
#include <iostream>
#include <GLEW\glew.h>

OpenGlRenderer::OpenGlRenderer()
{

}


OpenGlRenderer::~OpenGlRenderer()
{
}

// Creates a window
void OpenGlRenderer::CreateWindow(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not initialize: " << std::endl;
	}
	else {
		// Creates a window
		window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
		if (window == NULL) {
			std::cout << "Couldn't create window :(";
		}
		context = SDL_GL_CreateContext(window);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// Setsup glew and sets the clear color (background color)
		glewInit();
		glClearColor(1, 0, 0, 1);
		glViewport(0, 0, width, height);
		
		// Polygon mode is the way OpenGl renders the triangles, you can change the setting here to get wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Sets depth test so pixels rendererd underneath other pixels don't overrite those pixels (you get a really weird looking picture if you don't do this
		glEnable(GL_DEPTH_TEST);


		// Standard clear depth buffer bit and color buffer bit
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

// Swaps the render buffers so we can see the changes that we have rendered
void OpenGlRenderer::UpdateScreen() {
	// Updates the screen by swapping buffers
	SDL_GL_SwapWindow(window);
}

// Binds a framebuffer so we can render to it
void OpenGlRenderer::BindFramBuffer(FrameBuffer frame) {
	glBindFramebuffer(GL_FRAMEBUFFER, frame.GetID());
}

// Effectively unbinds the bound frame buffer setting it back to default render location.
void OpenGlRenderer::BindDefaultFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Graphics card calls
bool OpenGlRenderer::CompileObject(Object& object) {

	glGenVertexArrays(1, &object.GetIDVAO());
	glBindVertexArray(object.GetIDVAO());
	glGenBuffers(1, &object.GetIDVBO());

	glBindBuffer(GL_ARRAY_BUFFER, object.GetIDVBO());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * object.GetVerticies().Size(), object.GetVerticies().GetValues(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;

}
//bool CompileObjectAtt(Object& object, char attributes); // Get this to work somehow, make a very flexible rendering function
bool OpenGlRenderer::RenderObject(Object& object) {
	glBindVertexArray(object.GetIDVAO());
	glDrawArrays(GL_TRIANGLES, 0, object.GetVerticies().Size() / 3);
	glBindVertexArray(0);

	return true;
}
//bool RenderObject(Object& object, char attributes);

void OpenGlRenderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}