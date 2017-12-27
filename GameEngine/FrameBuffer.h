/**
Author: Ben Brenkman
Notes: Just some framebuffer stuff

**/

#pragma once
#include "Texture.h"
#include <GLEW\glew.h>

class FrameBuffer : public RenderItem
{
public:
	FrameBuffer(unsigned int width, unsigned int height, unsigned int type);
	bool Initialize();
	unsigned int GetType() { return type; };
	~FrameBuffer();

private:
	unsigned int type;
	Texture colorTextureBuffer;
};

