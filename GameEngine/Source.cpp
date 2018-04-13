#include "GameEngine.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define VS_MEM_CHECK;
#endif

int main(int argc, char** argv) {
	VS_MEM_CHECK;

	GameEngine gameEngine;

	gameEngine.initialize();
	gameEngine.run();
	gameEngine.shudown();

	return 0;
}