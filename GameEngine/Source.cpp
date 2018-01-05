#include <iostream>
#include "OpenGlRenderer.h"
#include "AssetManager.h"
#include "Object.h"
#include "PrimitiveShape.h"
#include "Registry.h"
#include "FrameBuffer.h"
#include "PhysicsEngine.h"
#include "Camera.h"
#include "InputManager.h"

using namespace std;

int main(int argc, char** argv) {

	OpenGlRenderer renderer;
	renderer.CreateWindow(640, 480);
	renderer.UpdateScreen();
	renderer.SetStatus(RenderEngine::RUNNING);
	renderer.SetBackgroundColor(glm::vec3(0.3, 0.3, 0.3));

	InputManager inputManager;

	Registry::SetRenderEngine(&renderer);
	Registry::PrintClassName<OpenGlRenderer>();

	Camera* camera = new Camera();
	camera->Move(BACKWARD, 1);

	Shader* shader = AssetManager::LoadShader("Shader\\light_vert.glsl", "Shader\\sun_frag.glsl");
	Shader* frameBufferEffects = AssetManager::LoadShader("Shader\\transform_vert.glsl", "Shader\\transform_frag.glsl");
	Texture* text = AssetManager::LoadTexture("Texture\\test.jpg");

	FrameBuffer* buffer = renderer.CreateFramebuffer(640, 480);
	buffer->SetBackgourndColor(glm::vec3(1, 1, 1));

	//Object test = *PrimitiveShape::GenerateSquare(1, 1, Material(1, 1, text, shader, glm::vec3(1, 1, 0)));
	//Object tes1 = *PrimitiveShape::GenerateSquare(-1, -1, Material(1, 1, text, shader, glm::vec3(0, 1, 1)));
	Object model = *AssetManager::LoadModel("Model\\monkey.obj", text, shader); // TODO: remove params 1 and 2, temporary to prevent crashing


	Object frame = *PrimitiveShape::GenerateSquare(1, 1, new Material(1, 1, buffer->GetColorBuffer(), frameBufferEffects, glm::vec3(1, 1, 1)));

	//test.CreateBoundBox(); // Maybe we should move this method call into the OpenGlRenderer::CompileObject(Object* object) method later
	//tes1.CreateBoundBox(); 
	frame.CreateBoundBox();
	model.CreateBoundBox();

	std::cout << std::endl << "Bounding Boxes: " << std::endl;
	//test.GetBoundBox().ToString();
	//tes1.GetBoundBox().ToString();
	frame.GetBoundBox().ToString();
	model.GetBoundBox().ToString();

	std:cout << std::endl;
	
	//renderer.CompileObject(test);
	//renderer.CompileObject(tes1);
	renderer.CompileObject(frame);
	renderer.CompileObject(model);

	//model.ToString();

	std::cout << "model data:" << std::endl;
	std::cout << "# of vertices: " << model.GetVerticies().Size() << std::endl;

	// Main loop
	while (renderer.GetStatus() == RenderEngine::RUNNING) {

		float delta = .0008;
		//renderer.BindFramBuffer(buffer);
		renderer.Clear();
		// We'll take out all of this input stuff out and make an InputManager class
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case  SDL_QUIT:
				renderer.SetStatus(RenderEngine::SHUTDOWN);
				break;
			case SDL_KEYDOWN:
				inputManager.pressKey(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				inputManager.releaseKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				camera->ProcessMouseMovement(event.motion.xrel, -event.motion.yrel);
				std::cout << "Mouse x offset: " << event.motion.xrel << " y: " << event.motion.yrel << std::endl;
				break;
			}
		}

		if (inputManager.isKeyPressed(SDLK_w))
			camera->ProcessKeyboard(FORWARD, delta);
		if (inputManager.isKeyPressed(SDLK_s))
			camera->ProcessKeyboard(BACKWARD, delta);
		if (inputManager.isKeyPressed(SDLK_a))
			camera->ProcessKeyboard(LEFT, delta);
		if (inputManager.isKeyPressed(SDLK_d))
			camera->ProcessKeyboard(RIGHT, delta);
		if (inputManager.isKeyPressed(SDLK_LSHIFT))
			camera->ProcessKeyboard(UP, delta);
		if (inputManager.isKeyPressed(SDLK_LCTRL))
			camera->ProcessKeyboard(DOWN, delta);
		if (inputManager.isKeyPressed(SDLK_LEFT))
			camera->ProcessMouseMovement(0.3, 0, true);
		if (inputManager.isKeyPressed(SDLK_RIGHT))
			camera->ProcessMouseMovement(-0.3, 0, true);
		if (inputManager.isKeyPressed(SDLK_UP))
			camera->ProcessMouseMovement(0, 0.3, true);
		if (inputManager.isKeyPressed(SDLK_DOWN))
			camera->ProcessMouseMovement(0, -0.3, true);
		if (inputManager.isKeyPressed(SDLK_ESCAPE)) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_CaptureMouse(SDL_FALSE);
		}
			
		renderer.RenderObject(*camera, model);

		//renderer.BindDefaultFrameBuffer();
		//renderer.Clear();

		//renderer.RenderObject(*camera, frame);

		renderer.UpdateScreen();
	}

	SDL_Quit();

	PhysicsEngine physics;
	physics.PhysicsTest();

	std::cout << "GameEngine" << std::endl;
	return 0;
}