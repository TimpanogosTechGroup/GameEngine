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
	//Registry::PrintClassName<OpenGlRenderer>();
	Shader* shader = AssetManager::LoadShader("Shader\\vert.glsl", "Shader\\frag.glsl");


	Object test = *PrimitiveShape::GenerateSquare(2, 1, Material(1, 1, NULL, shader, glm::vec3(1, 1, 0)));
	Object tes1 = *PrimitiveShape::GenerateSquare(-1, -1, Material(1, 1, NULL, shader, glm::vec3(0, 1, 1)));

	std::cout << ::endl;

	test.CreateBoundBox();
	tes1.CreateBoundBox();

	test.GetBoundBox().ToString();
	tes1.GetBoundBox().ToString();
	
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