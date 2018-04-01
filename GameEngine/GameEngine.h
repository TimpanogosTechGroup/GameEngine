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