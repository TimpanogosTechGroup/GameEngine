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
	FrameBuffer(unsigned int width, unsigned int height, unsigned char type);
	bool Initialize();
	unsigned int GetType() { return type; };
	~FrameBuffer();

	Texture* GetColorBuffer() { return colorTextureBuffer; };

	static const unsigned char COLOR_BUFFER = 1;
	static const unsigned char STENCIL_DEPTH = 2;

private:
	unsigned int type;
	RenderItem RBO;
	Texture* colorTextureBuffer;
};

