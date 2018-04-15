/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/

/**
Author: Ben Brenkman
Notes: Just some framebuffer stuff

**/

#pragma once
#include "Texture.h"
#include <GLEW\glew.h>
#include <glm\glm.hpp>

class FrameBuffer : public RenderItem
{
public:
	FrameBuffer(unsigned int width, unsigned int height, unsigned char type);

	unsigned int GetType() { return type; };

	unsigned int GetWidth() { return buffer_width; };
	unsigned int GetHeight() { return buffer_height; };

	Texture* GetColorBuffer() { return colorTextureBuffer; };
	RenderItem* GetRbo() { return &RBO; };

	void SetBackgourndColor(glm::vec3 backColor) { BackgroundColor = backColor; };
	glm::vec3 GetBackgroundColor() { return BackgroundColor; };

	static const unsigned char COLOR_BUFFER = 1;
	static const unsigned char STENCIL_DEPTH = 2;

	~FrameBuffer();
private:
	unsigned int type;
	unsigned int buffer_width;
	unsigned int buffer_height;

	RenderItem RBO;
	Texture* colorTextureBuffer;
	glm::vec3 BackgroundColor;
};