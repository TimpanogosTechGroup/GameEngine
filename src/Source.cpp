/**
	File: Source.cpp
    Purpose: This is the current entry point to the game engine

    @author Ben Brenkman
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/

#define PROFILER_LOG

#include "GameEngine.h"
#include "Profiler.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define VS_MEM_CHECK
#endif

//int main(int argc, char** argv) {
//	VS_MEM_CHECK;
//
//	src gameEngine;
//	Profiler::init();
//	PROFILE_PUSH("Initialize");
//	gameEngine.initialize();
//	PROFILE_POP;
//	gameEngine.run();
//	gameEngine.shudown();
//	Profiler::dump();
//
//	return 0;
//}