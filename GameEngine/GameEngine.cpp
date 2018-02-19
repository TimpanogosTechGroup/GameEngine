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
	Model liberty = *AssetManager::LoadModel("Model\\cube.obj");
	liberty.CreateBoundBox();
	renderer.CompileBoundingBox(liberty.boundingBox);
	renderer.CompileModel(liberty);

	// Add to physics
}

void GameEngine::run() {

}

void GameEngine::shudown() {

}