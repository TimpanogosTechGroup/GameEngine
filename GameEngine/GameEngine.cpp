/**
	File:
    Purpose: 

    @author Ben Brenkman
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "GameEngine.h"

#ifdef CreateWindow
#define temp_Create CreateWindow
#undef CreateWindow
#endif

#define LOG(message) \
	Logger::Log<GameEngine>(DEBUG, message);

GameEngine::GameEngine() {

}

GameEngine::~GameEngine() {

}

void GameEngine::initialize(const char subystems) {
	Properties::Init();

	if (shouldInitialize(subystems, GAME_ENGINE_SUBSYSTEM_RENDERER)) {
		Registry::Register("renderer", &renderer);

		Registry::SetRenderEngine(&renderer);

		renderer.CreateWindow("Andromeda", 1280, 720);
		renderer.UpdateScreen();
		renderer.SetStatus(RenderEngine::RUNNING);
		renderer.SetBackgroundColor(glm::vec3(0.3, 0.3, 0.3));
		renderer.loadDefaults();
		Logger::Log<GameEngine>(DEBUG, "Initialized the rendering engine");
		setInitializedSystem(GAME_ENGINE_SUBSYSTEM_RENDERER);
	}
	if (shouldInitialize(subystems, GAME_ENGINE_SUBSYSTEM_FONT)) {
		try {
			fontManager.loadFont(ARIAL);
			Logger::Log<FontManager>(DEBUG, "Initializing...");
			setInitializedSystem(GAME_ENGINE_SUBSYSTEM_FONT);
		}
		catch (FontManagerException& e) {
			Logger::Log<FontManager>(LoggerLevel::SEVERE, e.what());
		}
	}
	if (shouldInitialize(subystems, GAME_ENGINE_SUBSYSTEM_CAMERA)) {
		setInitializedSystem(GAME_ENGINE_SUBSYSTEM_CAMERA);
	}
	if (shouldInitialize(subystems, GAME_ENGINE_SUBSYSTEM_FILE_SYSTEM)) {
		FileSystemManager::getInstance().initialize();
		setInitializedSystem(GAME_ENGINE_SUBSYSTEM_FILE_SYSTEM);
	}
	if (shouldInitialize(subystems, GAME_ENGINE_SUBSYSTEM_INPUT)) {
		inputManager.initialize();
		setInitializedSystem(GAME_ENGINE_SUBSYSTEM_FILE_SYSTEM);
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
			if (inputManager.isMouseMovementEnabled() && isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
				camera->ProcessMouseMovement(static_cast<float>(event.motion.xrel), static_cast<float>(-event.motion.yrel));
			break;
		}
	}

	// Process input
	/*if (inputManager.gamepadLX() != 0) {
		std::cout << "Left Stick X: " << inputManager.gamepadLX() << std::endl;
	}*/
		bool cameraRotate = false;
		
		if (inputManager.isKeyPressed(SDLK_w) || inputManager.gamepadLY() > 0)
			if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
			camera->ProcessKeyboard(FORWARD, delta);
		if (inputManager.isKeyPressed(SDLK_s) || inputManager.gamepadLY() < 0)
			if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
			camera->ProcessKeyboard(BACKWARD, delta);
		if (inputManager.isKeyPressed(SDLK_a) || inputManager.gamepadLX() < 0)
			if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
			camera->ProcessKeyboard(LEFT, delta);
		if (inputManager.isKeyPressed(SDLK_d) || inputManager.gamepadLX() > 0)
			if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
			camera->ProcessKeyboard(RIGHT, delta);
		if (inputManager.isKeyPressed(SDLK_LSHIFT) || inputManager.gamepadA())
			if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
			camera->ProcessKeyboard(UP, delta);
		if (inputManager.isKeyPressed(SDLK_LCTRL) || inputManager.gamepadB())
			if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
			camera->ProcessKeyboard(DOWN, delta);
		if (inputManager.isGamepadEnabled()) {
			if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
				camera->ProcessMouseMovement(stof(inputManager.gamepadRX()), stof(inputManager.gamepadRY()), true);
		}
		else {
			if (inputManager.isKeyPressed(SDLK_LEFT))
				if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
					camera->ProcessMouseMovement(0.3f, 0, true);
			if (inputManager.isKeyPressed(SDLK_RIGHT))
				if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
					camera->ProcessMouseMovement(-0.3f, 0, true);
			if (inputManager.isKeyPressed(SDLK_UP))
				if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
					camera->ProcessMouseMovement(0, 0.3f, true);
			if (inputManager.isKeyPressed(SDLK_DOWN))
				if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
					camera->ProcessMouseMovement(0, -0.3f, true);
		}
		if (inputManager.isKeyPressed(SDLK_ESCAPE) || inputManager.isGamepadEnabled()) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_CaptureMouse(SDL_FALSE);
			inputManager.disableMouseMovement();
		}
		if (inputManager.isKeyPressed(SDLK_TAB)) {
			if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
			camera->EnableLookAt();
		}
		else {
			if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_CAMERA))
			camera->DisableLookAt();
		}
}

float GameEngine::stof(short s) {
	if (s == 0) {
		return s;
	}
	int sign = (s > 0) ? 1 : -1;
	s = abs(s) - 1000;
	s /= 5295;
	float f = (float)(s * 0.1 * sign);
	return f;
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
		PROFILE_PUSH("framestart");
		// FPS counter and profiler
		double currentTime = static_cast<double> (time(0));
		nbFrames++;
		if (currentTime - lastTime >= 1.0) {
			timePerFrame = 1000.0 / double(nbFrames);
			FPS_o = nbFrames;
			nbFrames = 0;
			lastTime += 1.0;
		}

		float delta = .002f;
		proccessInput(delta); // proccess input
		
		// Delete this later
		if (inputManager.isGamepadEnabled() && inputManager.gamepadSelect()) {
			return;
		}

		PROFILE_PUSH("render update");
		if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_RENDERER)) {
			renderer.BindDefaultFrameBuffer();
			renderer.Clear();
		}

		if (currentWorld) {
			currentWorld->update();
			currentWorld->render();
		}

		PROFILE_POP;
		
		PROFILE_PUSH("render text"); // Text rendering so far is the most expensive operation
		// Render the FPS and time per frame variables
		os << "FPS: " << FPS_o;
		//renderer.RenderText(camera, fontManager.getFont(ARIAL), os.str(), 10, 690, 0.5f, glm::vec3(1, 1, 1));
		os.str("");
		os.clear();
		os << "Time: " << timePerFrame;
		//renderer.RenderText(camera, fontManager.getFont(ARIAL), os.str(), 120, 690, 0.5f, glm::vec3(1, 1, 1));
		os.str("");
		os.clear();
		PROFILE_POP;
		// Show the changes after rendering
		PROFILE_PUSH("buffer swap");
		if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_RENDERER))
		renderer.UpdateScreen(); // Shouuld take less than 2 milliseconds
		PROFILE_POP;

		PROFILE_POP;
	}
}

void GameEngine::shudown() {
	inputManager.deleteGamepad();
	LOG("Shuting down Game Engine");
	LOG("Cleaning up ResourceManager");
	ResourceManager::clean();
	if (isSubSystemInitialized(GAME_ENGINE_SUBSYSTEM_WORLD)) {
	}
	clean();
}

void GameEngine::clean() {
	FileSystemManager::getInstance().clean();
	fontManager.clean();
}

void GameEngine::setup() {

}