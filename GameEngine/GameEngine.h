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


class GameEngine: public MemoryManager
{
private:
	FontManager fontManager;
	OpenGlRenderer renderer;
	InputManager inputManager;
	Camera* camera = nullptr;
	ModelManager modelManager;
	CubeMap* cube;
		static GameEngine* engine;
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
		if (engine)
			delete engine;
	}

	static const char GAME_ENGINE_ALL_SUBSYSTEMS = 0;
	static const char GAME_ENGINE_SUBSYSTEM_RENDERER = 1;
	static const char GAME_ENGINE_SUBSYSTEM_AUDIO = 2;
	static const char GAME_ENGINE_SUBSYSTEM_FONT = 4;
	static const char GAME_ENGINE_SUBSYSTEM_WORLD = 6;

	/**

	*/
	void initialize(const char subystems);
	void run();
	void shudown();
	void proccessInput(double delta);
	void clean();
	void setup();
};

#endif