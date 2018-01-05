#include <iostream>
#include "OpenGlRenderer.h"
#include "AssetManager.h"
#include "Object.h"
#include "PrimitiveShape.h"
#include "Registry.h"
#include "FrameBuffer.h"
#include "PhysicsEngine.h"
#include "Camera.h"

using namespace std;

int main(int argc, char** argv) {

	OpenGlRenderer renderer;
	renderer.CreateWindow(640, 480);
	renderer.UpdateScreen();
	renderer.SetStatus(RenderEngine::RUNNING);
	renderer.SetBackgroundColor(glm::vec3(0.3, 0.3, 0.3));

	Registry::SetRenderEngine(&renderer);
	Registry::PrintClassName<OpenGlRenderer>();

	Camera* camera = new Camera();
	camera->Move(BACKWARD, 1);

	Shader* shader = AssetManager::LoadShader("Shader\\light_vert.glsl", "Shader\\sun_frag.glsl");
	Shader* frameBufferEffects = AssetManager::LoadShader("Shader\\Framebuffer\\kernel_vert.glsl", "Shader\\Framebuffer\\kernel_frag.glsl");
	Texture* text = AssetManager::LoadTexture("Texture\\test.jpg");

	FrameBuffer* buffer = renderer.CreateFramebuffer(640, 480);

	//Object test = *PrimitiveShape::GenerateSquare(1, 1, Material(1, 1, text, shader, glm::vec3(1, 1, 0)));
	//Object tes1 = *PrimitiveShape::GenerateSquare(-1, -1, Material(1, 1, text, shader, glm::vec3(0, 1, 1)));
	Object model = *AssetManager::LoadModel("Model\\monkey.obj", text, shader); // TODO: remove params 1 and 2, temporary to prevent crashing


	//Object frame = *PrimitiveShape::GenerateSquare(1, 1, Material(1, 1, buffer->GetColorBuffer(), frameBufferEffects, glm::vec3(1, 1, 1)));

	//test.CreateBoundBox(); // Maybe we should move this method call into the OpenGlRenderer::CompileObject(Object* object) method later
	//tes1.CreateBoundBox(); 
	//frame.CreateBoundBox();
	model.CreateBoundBox();

	std::cout << std::endl << "Bounding Boxes: " << std::endl;
	//test.GetBoundBox().ToString();
	//tes1.GetBoundBox().ToString();
	//frame.GetBoundBox().ToString();
	model.GetBoundBox().ToString();

	std:cout << std::endl;
	
	//renderer.CompileObject(test);
	//renderer.CompileObject(tes1);
	//renderer.CompileObject(frame);
	renderer.CompileObject(model);

	//model.ToString();

	std::cout << "model data:" << std::endl;
	std::cout << "# of vertices: " << model.GetVerticies().Size() << std::endl;

	// Main loop
	while (renderer.GetStatus() == RenderEngine::RUNNING) {

		float delta = .16;
		renderer.BindDefaultFrameBuffer();
		renderer.Clear();
		// We'll take out all of this input stuff out and make an InputManager class
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case  SDL_QUIT:
				renderer.SetStatus(RenderEngine::SHUTDOWN);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_w:
					camera->ProcessKeyboard(FORWARD, delta);
					break;
				case SDLK_s:
					camera->ProcessKeyboard(BACKWARD, delta);
					break;
				case SDLK_a:
					camera->ProcessKeyboard(LEFT, delta);
					break;
				case SDLK_d:
					camera->ProcessKeyboard(RIGHT, delta);
					break;
				case SDLK_LSHIFT:
					camera->ProcessKeyboard(UP, delta);
					break;
				case SDLK_LCTRL:
					camera->ProcessKeyboard(DOWN, delta);
					break;
				case SDLK_LEFT:
					camera->ProcessMouseMovement(10, 0, true);
					break;
				case SDLK_RIGHT:
					camera->ProcessMouseMovement(-10, 0, true);
					break;
				case SDLK_UP:
					camera->ProcessMouseMovement(0, 10, true);
					break;
				case SDLK_DOWN:
					camera->ProcessMouseMovement(0, -10, true);
					break;
				}
			}
		}
			
		renderer.RenderObject(*camera, model);
		//renderer.RenderObject(*camera, test);

		renderer.UpdateScreen();
	}

	SDL_Quit();

	PhysicsEngine physics;
	physics.PhysicsTest();

	std::cout << "GameEngine" << std::endl;
	return 0;
}