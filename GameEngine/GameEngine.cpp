#include "GameEngine.h"
#include "World.h"
#include "Entity.h"
#include "Terrian.h"
#include "RandomEntity.h"

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
	//Registry::Register("fontManager", &fontManager);
	Registry::Register("physicsEngine", physicsEngine); // We need to change the construciton of the phsyics engine
	//Registry::Register("inputManager", &inputManager);

	Registry::SetRenderEngine(&renderer);

	physicsEngine = new PhysicsEngine();

	renderer.CreateWindow("Andromeda", 1280, 720);
	renderer.UpdateScreen();
	renderer.SetStatus(RenderEngine::RUNNING);
	renderer.SetBackgroundColor(glm::vec3(0.3, 0.3, 0.3));
	renderer.loadDefaults();

	camera = new Camera();

	try {
		fontManager.loadFont(ARIAL);
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

	World::getInstance().initialize();

	Terrian* terrian = new Terrian();
	RandomEntity* rand = new RandomEntity(PhysicalInstance(std::string("barrel"), ResourceManager::getModel("Model\\Barrel.obj"), glm::vec3(0, 0, 0), glm::vec3(0, 5, 0), 1.0));
	World::getInstance().addEntityToWorld(terrian);
	World::getInstance().addEntityToWorld(rand);

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

	World::getInstance().setCamera(camera);
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
		// FPS counter and profiler
		double currentTime = static_cast<double> (time(0));
		nbFrames++;
		if (currentTime - lastTime >= 1.0) {
			timePerFrame = 1000.0 / double(nbFrames);
			FPS_o = nbFrames;
			nbFrames = 0;
			lastTime += 1.0;
		}

		World::getInstance().update();

		float delta = .002f;
		proccessInput(delta); // proccess input


		renderer.BindDefaultFrameBuffer();
		renderer.Clear();
		// Render cube map first then render the rest of the scene
		renderer.RenderCubeMap(*camera, cube);

		World::getInstance().render();
		

		// Render the FPS and time per frame variables
		os << "FPS: " << FPS_o;
		renderer.RenderText(camera, fontManager.getFont(ARIAL), os.str(), 10, 690, 0.5f, glm::vec3(1, 1, 1));
		os.str("");
		os.clear();
		os << "Time: " << timePerFrame;
		renderer.RenderText(camera, fontManager.getFont(ARIAL), os.str(), 120, 690, 0.5f, glm::vec3(1, 1, 1));
		os.str("");
		os.clear();
		// Show the changes after rendering
		renderer.UpdateScreen();
	}
}

void GameEngine::shudown() {
	LOG("Shuting down Game Engine");
	LOG("Cleaning up ResourceManager");
	ResourceManager::clean();
}