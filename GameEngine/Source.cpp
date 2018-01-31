#include "Properties.h"
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
#include <string>
#include <iostream>
#include "Logger.h"
#include "LuaScript.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"

extern "C" {
#include <lua\lua.hpp>
#include <lua\lua.h>
#include <lua\lauxlib.h>
#include <lua\lualib.h>
}

using namespace std;

int main(int argc, char** argv) {

	Properties::Init();
	Logger::Log<OpenGlRenderer>(LoggerLevel::INFO, "Initializing...");

	OpenGlRenderer renderer;
	renderer.CreateWindow(800, 600);
	renderer.UpdateScreen();
	renderer.SetStatus(RenderEngine::RUNNING);
	renderer.SetBackgroundColor(glm::vec3(0.3, 0.3, 0.3));

	Logger::Log<InputManager>(INFO, "Initializing...");
	InputManager inputManager;

	Logger::Log<Registry>(INFO, "Initializing...");
	Registry::SetRenderEngine(&renderer);
	Registry::Register("renderer", &renderer);
	Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->init(); // WARNING may not return anything, check for nullptr!!

	//renderer.init();

	Camera* camera = new Camera();
	camera->Move(BACKWARD, 1);

	Logger::Log<Logger>(INFO, "Loading models");
	ResourceManager::loadModel("Model\\LibertStatue.obj", "statue");
	Model model = *AssetManager::LoadModel("Model\\cube.obj");
	Model liberty = *ResourceManager::getModel("statue");

	model.CreateBoundBox();
	liberty.CreateBoundBox();
	renderer.CompileBoundingBox(model.boundingBox);
	renderer.CompileBoundingBox(liberty.boundingBox);
	
	renderer.CompileModel(model);
	renderer.CompileModel(liberty);

	// Main loop
	Logger::Log<Logger>(INFO, "Entering main loop");
	while (renderer.GetStatus() == RenderEngine::RUNNING) {

		float delta = .002f;

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
				inputManager.pressKey(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				inputManager.releaseKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				camera->ProcessMouseMovement(static_cast<float>(event.motion.xrel), static_cast<float>(-event.motion.yrel));
				break;
			}
		}
		
		// Process input
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
			camera->ProcessMouseMovement(0.3f, 0, true);
		if (inputManager.isKeyPressed(SDLK_RIGHT))
			camera->ProcessMouseMovement(-0.3f, 0, true);
		if (inputManager.isKeyPressed(SDLK_UP))
			camera->ProcessMouseMovement(0, 0.3f, true);
		if (inputManager.isKeyPressed(SDLK_DOWN))
			camera->ProcessMouseMovement(0, -0.3f, true);
		if (inputManager.isKeyPressed(SDLK_ESCAPE)) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_CaptureMouse(SDL_FALSE);
		}
			
		renderer.RenderBoundingBox(*camera, model, glm::vec3(1, 0, 0));
		renderer.RenderBoundingBox(*camera, liberty, glm::vec3(0, 1, 0));
		renderer.RenderModel(*camera, liberty);

		renderer.UpdateScreen();
	}

	Logger::Log<Logger>(INFO, "Exiting main loop");

	SDL_Quit();

	PhysicsEngine physics;
	Logger::Log<PhysicsEngine>(LoggerLevel::INFO, "Physics Test");
	physics.PhysicsTest();
	
	return 0;
}