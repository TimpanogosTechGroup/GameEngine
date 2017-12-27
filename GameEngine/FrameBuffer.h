/**
Author: Ben Brenkman
Notes: Just some framebuffer stuff

**/

#pragma once
#include "Texture.h"
#include <GLEW\glew.h>

class FrameBuffer
{
public:
	FrameBuffer(unsigned int width, unsigned int height, unsigned int type);
	bool Initialize();
	~FrameBuffer();

private:
	unsigned int ID;
	unsigned int type;
	Texture colorTextureBuffer;
};

