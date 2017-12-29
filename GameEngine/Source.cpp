#include <iostream>
#include "OpenGlRenderer.h"
#include "AssetManager.h"
#include "Object.h"
#include "PrimitiveShape.h"

using namespace std;

int main(int argc, char** argv) {

	OpenGlRenderer renderer;
	renderer.CreateWindow(640, 480);
	renderer.UpdateScreen();
	renderer.SetStatus(RenderEngine::RUNNING);

	Object test = *PrimitiveShape::GenerateSquare(10, 10, Material());
	
	renderer.CompileObject(test);

	// Main loop
	while (renderer.GetStatus() == RenderEngine::RUNNING) {
		renderer.Clear();
		// We'll take out all of this input stuff out and make an InputManager class
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case  SDL_QUIT:
				renderer.SetStatus(RenderEngine::SHUTDOWN);
				break;
			}
		}
		
		renderer.RenderObject(test);
		renderer.UpdateScreen();
	}

	SDL_Quit();
	

	cout << "GameEngine" << endl;
	return 0;
}