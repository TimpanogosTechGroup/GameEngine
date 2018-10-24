#include "StartApp.h"
//#include "World.h"
//#include "Logger.h"

// Memory detection
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#endif

/*
	This constructor is for your own personal use

	WARNING WARNING WARNING WARNING
	Do not initialize subsystems here
	
*/


void glDebugOutput(GLenum source,
				   GLenum type,
				   GLuint id,
				   GLenum severity,
				   GLsizei length,
				   const GLchar *message,
				   const void *userParam)
{
	// ignore non-significant error/warning codes
	if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " <<  message << std::endl;

	switch (source)
	{
		case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
		case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

StartApp::StartApp()
{
}

/*
	Basic cleanup here, just make sure you don't have any memory leaks
	We can't do everything for you ;)
	That being said we do most of the heavy lifting for you.
*/
StartApp::~StartApp()
{
	delete camera, world;
}

/*
	This function is designed to start up and initialize evrything
	There is a very specific order that the subsystems must be initialized in
	This function is designed to reduce the errors and manage the most important initialization for you

	First initialize the Game Engine and all the subsystems you will need

	Second initialize any other subsystems that are not initialized by the game engine
		These are game specific subsystems

	Third initialize the world and GUI manager etc. You can also load some resources, basic ones just for the gui

	Forth add GUI elemnts and load some resources. You can seperate the loading of resources
		You can either do it all here, and if you have done the Game Engine initialization properly
		You will have a loading screen, or you can create your own costum screen and load somewhere else
		Must load all essential resources here

	Fifth register proccess that need to take place, eg. final resource laoding
*/
void StartApp::initialize() {

	engine.initialize(GameEngine::GAME_ENGINE_ALL_SUBSYSTEMS);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugOutput, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

	world = new World(); // Create a new world instance
	world->initialize(); // Initialize the world
	camera = new Camera();
	world->setActiveCamera(camera); // Set the active camera, TODO create more controls to change camera etc.

	AssetManager::LoadModelFull("Caltrop");

	AssetManager::LoadModelFull("Caltrop");
	Entity* rand = new RandomEntity(std::string("Caltrop"));
	world->addEntityToWorld(rand);

	world->setCubeMap(AssetManager::LoadCubeMap("resources/Texture/cubemap/morning")); // Load cube map and such into engine and set World's cubemap
	engine.setWorld(world); // Set the current world in Game Engine, will recieve updates, events, rendering calls etc.
}

/*
	This passes the proccess to the Game Engine to run the main loop, it is called after the initialization
	Or you can direcrtly call all the rendering calls in the World and in the Renderer
	Have fun with that one hahahaha
*/
void StartApp::run() {
	engine.run();
}

void StartApp::shutdown() {
	world->shutdown();
	engine.shudown();
}

/*
	This is the start up template script, this just creates a new StartApp instance
	And then hands over the proccess to the application.
	This function will then handle background proccess, and calls a few callback functions
	These call back functions can be used to start up the game engine and set up your game
*/
int main(int argc, char** argv) {

	//VS_MEM_CHECK;
	
	StartApp app;
	app.launch(argc, argv);

	return 0;
}