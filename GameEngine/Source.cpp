#include "GameEngine.h"

int main(int argc, char** argv) {

	GameEngine gameEngine;

	gameEngine.initialize();
	gameEngine.run();
	gameEngine.shudown();

	return 0;
}