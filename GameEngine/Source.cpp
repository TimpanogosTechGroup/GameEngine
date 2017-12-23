#include <iostream>
#include "OpenGlRenderer.h"

using namespace std;

int main(int argc, char** argv) {

	OpenGlRenderer renderer;
	renderer.CreateWindow(640, 480);
	renderer.UpdateScreen();
	renderer.SetStatus(RenderEngine::RUNNING);

	while (renderer.GetStatus() == RenderEngine::RUNNING) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case  SDL_QUIT:
				renderer.SetStatus(RenderEngine::SHUTDOWN);
				break;
			}
		}
		renderer.UpdateScreen();
	}

	SDL_Quit();
	

	cout << "GameEngine" << endl;
	return 0;
}