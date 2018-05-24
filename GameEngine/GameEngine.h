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


class GameEngine
{
private:
	PhysicsEngine* physicsEngine;
	FontManager fontManager;
	OpenGlRenderer renderer;
	InputManager inputManager;
	Camera* camera = nullptr;
	Model* liberty = nullptr;
	Model* cube1 = nullptr;
	Model* barrel = nullptr;
	ModelManager modelManager;
	Chunk* chunk;
	Chunk* chunk2;
	Chunk* chunk3;
	Chunk* chunk4;
	CubeMap cube;
public:
	GameEngine();
	~GameEngine();

	/**

	*/
	void initialize();
	void run();
	void shudown();
	void proccessInput(double delta);
};

#endif