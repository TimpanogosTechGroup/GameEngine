#include "GameEngine.h"


GameEngine::GameEngine()
{

}


GameEngine::~GameEngine()
{
}

void GameEngine::initialize() {
	Registry::Register("renderer", &renderer);
	Registry::Register("fontManager", &fontManager);
	Registry::Register("physicsEngine", &physicsEngine);
	Registry::Register("inputManager", &inputManager);

	Properties::Init();

	renderer.CreateWindow(1280, 720);
	renderer.UpdateScreen();
	renderer.SetStatus(RenderEngine::RUNNING);
	renderer.SetBackgroundColor(glm::vec3(0.3, 0.3, 0.3));

	try {
		fontManager.loadFont("fonts\\arial.ttf");
		Logger::Log<FontManager>(DEBUG, "Initializing...");
	}
	catch (FontManagerException& e) {
		Logger::Log<FontManager>(ERROR, e.what());
	}

	cube = *AssetManager::LoadCubeMap("Texture\\cubemap\\morning");

	//Load models
	liberty = *AssetManager::LoadModel("Model\\cube.obj");
	liberty.CreateBoundBox();
	renderer.CompileBoundingBox(liberty.boundingBox);
	renderer.CompileModel(liberty);

	// Add to physics
	modelManager.push_back(&liberty);
	physicsEngine.AddModel(liberty);

}

void GameEngine::run() {
	int nbFrames = 0;
	double lastTime = time(0);
	double FPS_o = 0;
	double timePerFrame = 0.0;
	std::ostringstream os;
	while (renderer.GetStatus() == RenderEngine::RUNNING) {

		// FPS counter and profiler
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

		// update physics with respect to delta
		physicsEngine.Update(timePerFrame, modelManager);

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
					camera.ProcessMouseMovement(static_cast<float>(event.motion.xrel), static_cast<float>(-event.motion.yrel));
				break;
			}
		}

		// Process input
		if (inputManager.isKeyPressed(SDLK_w))
			camera.ProcessKeyboard(FORWARD, delta);
		if (inputManager.isKeyPressed(SDLK_s))
			camera.ProcessKeyboard(BACKWARD, delta);
		if (inputManager.isKeyPressed(SDLK_a))
			camera.ProcessKeyboard(LEFT, delta);
		if (inputManager.isKeyPressed(SDLK_d))
			camera.ProcessKeyboard(RIGHT, delta);
		if (inputManager.isKeyPressed(SDLK_LSHIFT))
			camera.ProcessKeyboard(UP, delta);
		if (inputManager.isKeyPressed(SDLK_LCTRL))
			camera.ProcessKeyboard(DOWN, delta);
		if (inputManager.isKeyPressed(SDLK_LEFT))
			camera.ProcessMouseMovement(0.3f, 0, true);
		if (inputManager.isKeyPressed(SDLK_RIGHT))
			camera.ProcessMouseMovement(-0.3f, 0, true);
		if (inputManager.isKeyPressed(SDLK_UP))
			camera.ProcessMouseMovement(0, 0.3f, true);
		if (inputManager.isKeyPressed(SDLK_DOWN))
			camera.ProcessMouseMovement(0, -0.3f, true);
		if (inputManager.isKeyPressed(SDLK_ESCAPE)) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_CaptureMouse(SDL_FALSE);
			inputManager.disableMouseMovement();
		}
		if (inputManager.isKeyPressed(SDLK_TAB)) {
			camera.EnableLookAt();
		}
		else {
			camera.DisableLookAt();
		}

		// Render cube map first then render the rest of the scene
		renderer.RenderCubeMap(camera, cube);
		renderer.RenderBoundingBox(camera, liberty, glm::vec3(0, 1, 0));
		renderer.RenderBoundingBox(camera, cube, glm::vec3(0, 0, 1));
		renderer.RenderModel(camera, liberty);

		// Render the FPS and time per frame variables
		os << "FPS: " << FPS_o;
		renderer.RenderText(&camera, fontManager.getFont("fonts\\arial.ttf"), os.str(), 10, 690, 0.5f, glm::vec3(1, 1, 1));
		os.str("");
		os.clear();
		os << "Time: " << timePerFrame;
		renderer.RenderText(&camera, fontManager.getFont("fonts\\arial.ttf"), os.str(), 120, 690, 0.5f, glm::vec3(1, 1, 1));
		os.str("");
		os.clear();
		// Show the chnages after rendering
		renderer.UpdateScreen();
	}
}

void GameEngine::shudown() {

}