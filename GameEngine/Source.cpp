#include <iostream>
#include <SDL/SDL.h>
#include <stdio.h>
#include "OpenGlRenderer.h"

using namespace std;

int main(int argc, char** argv) {

	OpenGlRenderer renderer;
	renderer.CreateWindow(640, 480);
	renderer.UpdateScreen();

	cout << "GameEngine" << endl;
	return 0;
}