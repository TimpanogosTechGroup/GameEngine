#include <iostream>
#include "OpenGlRenderer.h"
#include "AssetManager.h"
#include "Object.h"
#include "PrimitiveShape.h"
#include "Registry.h"

using namespace std;

int main(int argc, char** argv) {

	OpenGlRenderer renderer;
	renderer.CreateWindow(640, 480);
	renderer.UpdateScreen();
	renderer.SetStatus(RenderEngine::RUNNING);

	Registry::SetRenderEngine(&renderer);
	Registry::PrintClassName<OpenGlRenderer>();
	Shader* shader = AssetManager::LoadShader("Shader\\vert.glsl", "Shader\\frag.glsl");
	Texture* text = AssetManager::LoadTexture("Texture\\test.jpg");


	Object test = *PrimitiveShape::GenerateSquare(1, 1, Material(1, 1, text, shader, glm::vec3(1, 1, 0)));
	Object tes1 = *PrimitiveShape::GenerateSquare(-1, -1, Material(1, 1, text, shader, glm::vec3(0, 1, 1)));
	
	renderer.CompileObject(test);
	renderer.CompileObject(tes1);

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
		renderer.RenderObject(tes1);
		renderer.UpdateScreen();
	}

	SDL_Quit();
	

	cout << "GameEngine" << endl;
	return 0;
}