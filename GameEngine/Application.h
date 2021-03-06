#ifndef APPLICATION_H
#define APPLICATION_H

#include "GameEngine.h"
#include "ThreadPool.h"
//#include "Profiler.h"

class Application
{
private:
public:
	Application();
	~Application();

	/*
	This function is designed to start up and initialize evrything
	There is a very specific order that the subsystems must be initialized in
	This function is designed to reduce the errors and manage the most important initialization for you

	First initialize the Game Engine and all the subsystems you will need
	Second initialize any other subsystems that are not initialized by the game engine
	These are game specific subsystems

	Thrid initialize the world and GUI manager etc. You can also load some resources, basic ones just for the gui

	Forth add GUI elemnts and load some resources. You can seperate the loading of resources
	You can either do it all here, and if you have done the Game Engine initialization properly
	You will have a loading screen, or you can create your own costum screen and load somewhere else
	Must load all essential resources here

	Fifth register proccess that need to take place, eg. final resource laoding
	*/
	virtual void run() {}

	/*
	This passes the proccess to the Game Engine to run the main loop, it is called after the initialization
	Or you can direcrtly call all the rendering calls in the World and in the Renderer
	Have fun with that one hahahaha
	*/
	virtual void initialize() {}

	/*
	This is the start up template script, this just creates a new StartApp instance
	And then hands over the proccess to the application.
	This function will then handle background proccess, and calls a few callback functions
	These call back functions can be used to start up the game engine and set up your game
	*/
	virtual void shutdown() {}

	void launch();
};

#endif