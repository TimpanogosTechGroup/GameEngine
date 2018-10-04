/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef GAME_ENINGE_H
#define GAME_ENGINE_H

#include "Properties.h"
#include "PhysicsEngine.h"
#include "FontManager.h"
#include "OpenGlRenderer.h"
#include "InputManager.h"
#include "Registry.h"
#include "Camera.h"
#include "AssetManager.h"
#include "ResourceManager.h"
#include "ModelManager.h"
#include "MemoryManager.h"
#include "Entity.h"
#include "Terrian.h"
#include "RandomEntity.h"
#include "World.h"
#include "FileSystemManager.h"
#include "Profiler.h"


class GameEngine: public MemoryManager
{
private:
	FontManager fontManager;
	OpenGlRenderer renderer;
	InputManager inputManager;
	Camera* camera = nullptr;
	ModelManager modelManager;
	CubeMap* cube;
	World* currentWorld;
	static GameEngine* engine;

	char excludedSubystems = 0;
	char initializedSystem = 0;

	bool shouldInitialize(const char paramInput, const char testCase) {
		if (paramInput == GAME_ENGINE_ALL_SUBSYSTEMS)
			return true;

		if ((paramInput & testCase) == testCase)
			return true;

		return false;
	}

	void setInitializedSystem(const char system) {
		initializedSystem = initializedSystem | system;
	}
	
public:
	GameEngine();
	~GameEngine();

	static GameEngine& getInstance() {
		static GameEngine* engine = nullptr;
		if (!engine) {
			engine = new GameEngine();
		}
		return *engine;
	}

	static void destroy() {
		static GameEngine* engine;
		if (engine)
			delete engine;
	}

	void excludeSubsystems(const char subsystems) {
		excludedSubystems = excludedSubystems | subsystems;
	};

	bool isSubSystemInitialized(const char system) {
		return (initializedSystem & system) == system;
	}

	void setWorld(World* world) {
		currentWorld = world;
		camera = world->getActiveCamera();
	}

	World* getCurrentWorld() {
		return currentWorld;
	}

	static const char GAME_ENGINE_ALL_SUBSYSTEMS = 0;
	static const char GAME_ENGINE_SUBSYSTEM_RENDERER = 1;
	static const char GAME_ENGINE_SUBSYSTEM_AUDIO = 2;
	static const char GAME_ENGINE_SUBSYSTEM_FONT = 4;
	static const char GAME_ENGINE_SUBSYSTEM_WORLD = 8;
	static const char GAME_ENGINE_SUBSYSTEM_CAMERA = 16;
	static const char GAME_ENGINE_SUBSYSTEM_FILE_SYSTEM = 32;

	/**

	*/
	void initialize(const char subystems);
	void run();
	void shudown();
	void proccessInput(double delta);
	float stof(short s);
	void clean();
	void setup();
};

#endif