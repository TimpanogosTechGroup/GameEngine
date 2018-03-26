#include "GameEngine.h"

GameEngine::GameEngine() : cube("Texture\\cubemap\\morning")
{
}

GameEngine::~GameEngine()
{
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
	AssetManager::LoadModel("Model\\cube.obj"); // Use the asset manager to load the model and add it to the resource manager
	AssetManager::LoadModel("Model\\Barrel.obj");
	//AssetManager::LoadModel("Model\\LibertStatue.obj");
	//AssetManager::LoadModel("Model\\Barrel.obj");

	cube = *AssetManager::LoadCubeMap("Texture\\cubemap\\morning");

	//Load models
	//liberty = ResourceManager::getModel("Model\\LibertStatue.obj");
	cube1 = ResourceManager::getModel("Model\\cube.obj");
	//barrel = ResourceManager::getModel("Model\\Barrel.obj");
	
	//Create the bounding boxes to display
	//liberty->CreateBoundBox();
	cube1->CreateBoundBox();
	ResourceManager::getModel("Model\\Barrel.obj")->CreateBoundBox();
	//barrel->CreateBoundBox();
	//renderer.CompileBoundingBox(liberty->boundingBox);
	renderer.CompileBoundingBox(cube1->boundingBox);
	renderer.CompileBoundingBox(ResourceManager::getModel("Model\\Barrel.obj")->boundingBox);
	//renderer.CompileBoundingBox(barrel->boundingBox);
	//renderer.CompileModel(*barrel);
	//renderer.CompileModel(*liberty);
	renderer.CompileModel(*cube1);
	renderer.CompileCubeMap(cube);
	renderer.CompileModel(*ResourceManager::getModel("Model\\Barrel.obj"));

	// Add to model manager
	//modelManager.push_back(cube1);
	//modelManager.push_back(liberty);

	modelManager.push_back_instance(new PhysicalInstance(std::string("cube"), cube1, glm::vec3(0, 10, 0), glm::vec3(0, 10, 0), 1.0));
	modelManager.push_back_instance(new PhysicalInstance(std::string("cube1"), cube1, glm::vec3(0, 0, 0), glm::vec3(0, 5, 0), 1.0));
	modelManager.push_back_instance(new PhysicalInstance(std::string("barrel"), ResourceManager::getModel("Model\\Barrel.obj"), glm::vec3(0, 0, 0), glm::vec3(0, 5, 0), 1.0));
	//modelManager.push_back_instance(new PhysicalInstance(std::string("liberty"), liberty, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1.0));
	//modelManager.push_back_instance(new PhysicalInstance(std::string("barrel"), barrel, glm::vec3(-10, 0, 0), glm::vec3(0, 0, 0), 1.0));

 	for (auto &iter : modelManager.getPhysicalInstances()) {
		physicsEngine->addModelInstance(iter.second, 1);
	}
}

void GameEngine::run() {
	int nbFrames = 0;
	double lastTime = static_cast<double> (time(0));
	double FPS_o = 0;
	double timePerFrame = 0.0;
	std::ostringstream os;
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

		// update physics with respect to delta
		physicsEngine->AddForce("cube", glm::vec3(0, 10, 0));
		physicsEngine->AddForce("cube1", glm::vec3(0, 10, 0));
		physicsEngine->Update(timePerFrame, modelManager);


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
		if (inputManager.isKeyPressed(SDLK_TAB)) {
			camera->EnableLookAt();
		}
		else {
			camera->DisableLookAt();
		}

		// Render cube map first then render the rest of the scene
		renderer.RenderCubeMap(*camera, cube);
		//renderer.RenderBoundingBox(*camera, *barrel, glm::vec3(0, 1, 0));
		//renderer.RenderBoundingBox(*camera, *liberty, glm::vec3(0, 1, 0));
		renderer.RenderBoundingBox(*camera, *cube1, glm::vec3(1, 0, 0));
		renderer.RenderBoundingBox(*camera, cube, glm::vec3(0, 0, 1));
		//renderer.RenderModel(*camera, *liberty);
		//renderer.RenderModel(*camera, *cube1);
		renderer.RenderPhysicalInstance(*camera, *modelManager.getPhysicalInstance("cube"));
		renderer.RenderPhysicalInstance(*camera, *modelManager.getPhysicalInstance("cube1"));
		renderer.RenderPhysicalInstance(*camera, *modelManager.getPhysicalInstance("barrel"));
		//renderer.RenderPhysicalInstance(*camera, *modelManager.getPhysicalInstance("liberty"));
		//renderer.RenderPhysicalInstance(*camera, *modelManager.getPhysicalInstance("barrel"));

		// Render the FPS and time per frame variables
		os << "FPS: " << FPS_o;
		renderer.RenderText(camera, fontManager.getFont("fonts\\arial.ttf"), os.str(), 10, 690, 0.5f, glm::vec3(1, 1, 1));
		os.str("");
		os.clear();
		os << "Time: " << timePerFrame;
		renderer.RenderText(camera, fontManager.getFont("fonts\\arial.ttf"), os.str(), 120, 690, 0.5f, glm::vec3(1, 1, 1));
		os.str("");
		os.clear();
		// Show the chnages after rendering
		renderer.UpdateScreen();
	}
}

void GameEngine::shudown() {

}