#include "GameEngine.h"

#define LOG(message, level) \
	Logger::Log<GameEngine>(level, message);

#define LOG(message) \
	Logger::Log<GameEngine>(DEBUG, message);

GameEngine::GameEngine() : cube("Texture\\cubemap\\morning") {

}

GameEngine::~GameEngine() {
	delete physicsEngine;
	delete camera;
	delete liberty;
	delete cube1;
	delete barrel;
}

void GameEngine::initialize() {
	Properties::Init();

	Registry::Register("renderer", &renderer);
	Registry::Register("fontManager", &fontManager);
	Registry::Register("physicsEngine", physicsEngine); //We need to change the construciton of the phsyics engine
	Registry::Register("inputManager", &inputManager);

	Registry::SetRenderEngine(&renderer);

	physicsEngine = new PhysicsEngine();

	renderer.CreateWindow("Andromeda", 1280, 720);
	renderer.UpdateScreen();
	renderer.SetStatus(RenderEngine::RUNNING);
	renderer.SetBackgroundColor(glm::vec3(0.3, 0.3, 0.3));
	renderer.loadDefaults();

	camera = new Camera();

	try {
		fontManager.loadFont("fonts\\arial.ttf");
		Logger::Log<FontManager>(DEBUG, "Initializing...");
	}
	catch (FontManagerException& e) {
		Logger::Log<FontManager>(ERROR, e.what());
	}


	//Load models and stuff
	AssetManager::LoadModelFull("Model\\cube.obj"); // Use the asset manager to load the model and add it to the resource manager
	AssetManager::LoadModelFull("Model\\Barrel.obj");
	AssetManager::LoadModelFull("Model\\spherepbr.obj");
	AssetManager::LoadModelFull("Model\\Gladius.obj");

	cube = *AssetManager::LoadCubeMap("Texture\\cubemap\\morning");

	modelManager.push_back_instance(new PhysicalInstance(std::string("cube"), ResourceManager::getModel("Model\\cube.obj"), glm::vec3(0, 10, 0), glm::vec3(0, 10, 0), 1.0));
	modelManager.push_back_instance(new PhysicalInstance(std::string("cube1"), ResourceManager::getModel("Model\\cube.obj"), glm::vec3(0, 0, 0), glm::vec3(0, 5, 0), 1.0));
	modelManager.push_back_instance(new PhysicalInstance(std::string("barrel"), ResourceManager::getModel("Model\\Barrel.obj"), glm::vec3(0, 0, 0), glm::vec3(0, 5, 0), 1.0));
	modelManager.push_back_instance(new PhysicalInstance(std::string("sphere"), ResourceManager::getModel("Model\\spherepbr.obj"), glm::vec3(0, 0, 0), glm::vec3(0, 5, 0), 1.0));
	modelManager.push_back_instance(new PhysicalInstance(std::string("sphere1"), ResourceManager::getModel("Model\\spherepbr.obj"), glm::vec3(0, 0, 0), glm::vec3(0, 5, 0), 1.0));
	modelManager.push_back_instance(new PhysicalInstance(std::string("Gladius"), ResourceManager::getModel("Model\\Gladius.obj"), glm::vec3(0, 0, -20), glm::vec3(0, 5, 0), 1.0));
	

 	for (auto &iter : modelManager.getPhysicalInstances()) {
		physicsEngine->addModelInstance(iter.second, 1);
	}
}

void GameEngine::proccessInput(double delta) {
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
	if (inputManager.isKeyPressed(SDLK_TAB)) {
		camera->EnableLookAt();
	}
	else {
		camera->DisableLookAt();
	}
}

void GameEngine::run() {
	double cir = 0;
	int nbFrames = 0;
	double lastTime = static_cast<double> (time(0));
	double FPS_o = 0;
	double timePerFrame = 0.0;
	std::ostringstream os;
	LOG("Starting the main loop");
	LOG("Tesing the log macro, we need to add it to every file that uses the logging class to simplify the code.", DEBUG);
	while (renderer.GetStatus() == RenderEngine::RUNNING) {
		cir += 0.005;

		// FPS counter and profiler
		double currentTime = static_cast<double> (time(0));
		nbFrames++;
		if (currentTime - lastTime >= 1.0) {
			timePerFrame = 1000.0 / double(nbFrames);
			FPS_o = nbFrames;
			nbFrames = 0;
			lastTime += 1.0;
		}

		// update physics with respect to delta
		physicsEngine->AddForce("cube", glm::vec3(20 * sin(cir), 20 * sin(cir), 20 * cos(cir)));
		physicsEngine->AddForce("cube1", glm::vec3(0, 10, 0));
		physicsEngine->AddForce("Gladius", glm::vec3(0, 50 / ((*modelManager.getPhysicalInstance("Gladius")).getInstancePosition().y*2 + 1), 0));
		physicsEngine->Update(timePerFrame, modelManager);

		float delta = .002f;
		proccessInput(delta); // proccess input

		renderer.BindDefaultFrameBuffer();
		renderer.Clear();
		// Render cube map first then render the rest of the scene
		renderer.RenderCubeMap(*camera, cube);
		renderer.RenderBoundingBox(*camera, *modelManager.getPhysicalInstance("cube1"), glm::vec3(1, 0, 0));
		renderer.RenderBoundingBox(*camera, *modelManager.getPhysicalInstance("cube"), glm::vec3(0, 0, 1));
		renderer.RenderBoundingBox(*camera, *modelManager.getPhysicalInstance("barrel"), glm::vec3(0, 0, 1));
		renderer.RenderPhysicalInstance(*camera, *modelManager.getPhysicalInstance("cube"));
		renderer.RenderPhysicalInstance(*camera, *modelManager.getPhysicalInstance("cube1"));
		renderer.RenderPhysicalInstance(*camera, *modelManager.getPhysicalInstance("barrel"));
		renderer.RenderPhysicalInstance(*camera, *modelManager.getPhysicalInstance("sphere"));
		renderer.RenderPhysicalInstance(*camera, *modelManager.getPhysicalInstance("sphere1"));
		renderer.RenderPhysicalInstance(*camera, *modelManager.getPhysicalInstance("Gladius"));

		// Render the FPS and time per frame variables
		os << "FPS: " << FPS_o;
		renderer.RenderText(camera, fontManager.getFont("fonts\\arial.ttf"), os.str(), 10, 690, 0.5f, glm::vec3(1, 1, 1));
		os.str("");
		os.clear();
		os << "Time: " << timePerFrame;
		renderer.RenderText(camera, fontManager.getFont("fonts\\arial.ttf"), os.str(), 120, 690, 0.5f, glm::vec3(1, 1, 1));
		os.str("");
		os.clear();
		// Show the changes after rendering
		renderer.UpdateScreen();
	}
}

void GameEngine::shudown() {

}