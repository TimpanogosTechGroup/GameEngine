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
#include "FontManager.h"
#include "FontManagerException.h"
#include <time.h>

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

	PhysicsEngine physics;

	OpenGlRenderer renderer;
	renderer.CreateWindow(1280, 720);
	renderer.UpdateScreen();
	renderer.SetStatus(RenderEngine::RUNNING);
	renderer.SetBackgroundColor(glm::vec3(0.3, 0.3, 0.3));

	Logger::Log<InputManager>(INFO, "Initializing...");
	InputManager inputManager;

	FontManager fontManager;
	try {
		fontManager.loadFont("fonts\\arial.ttf");
	}
	catch (FontManagerException& e) {
		Logger::Log<FontManager>(ERROR, e.what());
	}
	

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

	CubeMap* cube = AssetManager::LoadCubeMap("Texture\\cubemap\\morning");

	model.SetPosition(glm::vec3(0, 10, 0));
	liberty.SetPosition(glm::vec3(0, 1, 0));
	model.setRotation(0, 1, 0);
	liberty.setRotation(0, 0, 0);

	model.CreateBoundBox();
	liberty.CreateBoundBox();
	cube->CreateBoundBox();
	renderer.CompileBoundingBox(model.boundingBox);
	renderer.CompileBoundingBox(liberty.boundingBox);
	renderer.CompileBoundingBox(cube->boundingBox);

	std::cout << "Models position: " << liberty.GetPostion().x << std::endl;

	renderer.CompileModel(model);
	renderer.CompileModel(liberty);
	renderer.CompileCubeMap(*cube);

	physics.AddModel(model);
	physics.AddModel(liberty);

	// Main loop
	Logger::Log<Logger>(INFO, "Entering main loop");
	int nbFrames = 0;
	double lastTime = time(0);
	double FPS_o = 0;
	double timePerFrame = 0.0;
	while (renderer.GetStatus() == RenderEngine::RUNNING) {

		double currentTime = time(0);
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
											 // printf and reset timer
			//printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			timePerFrame = 1000.0 / double(nbFrames);
			FPS_o = nbFrames;
			nbFrames = 0;
			lastTime += 1.0;
		}

		physics.Update(model, liberty);

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
				if (inputManager.isMouseMovementEnabled())
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
			inputManager.disableMouseMovement();
		}

		// Render cube map first then render the rest of the scene
		renderer.RenderCubeMap(*camera, *cube);
		renderer.RenderBoundingBox(*camera, model, glm::vec3(1, 0, 0));
		renderer.RenderBoundingBox(*camera, liberty, glm::vec3(0, 1, 0));
		renderer.RenderBoundingBox(*camera, *cube, glm::vec3(0, 0, 1));
		renderer.RenderModel(*camera, liberty);
		//renderer.RenderModel(*camera, model);
		std::ostringstream os;
		os << "FPS: " << FPS_o;
		renderer.RenderText(camera, fontManager.getFont("fonts\\arial.ttf"), os.str(), 10, 690, 0.5f, glm::vec3(1, 1, 1));
		os.str("");
		os.clear();
		os << "Time: " << timePerFrame;
		renderer.RenderText(camera, fontManager.getFont("fonts\\arial.ttf"), os.str(), 120, 690, 0.5f, glm::vec3(1, 1, 1));
		// Show the chnages after rendering
		renderer.UpdateScreen();
	}

	Logger::Log<Logger>(INFO, "Exiting main loop");

	SDL_Quit();

	//Scene and Scene Manager Test Stuff
	SceneManager sceneManager;
	sceneManager.CreateNewScene("testScene");
	Scene testScene = *sceneManager.GetScene("testScene");
	testScene.AddModel(&liberty);

	return 0;
}