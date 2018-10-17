/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/

/*
Author: Ben Brenkman
Notes: We can use this class to render different scences at the same time, or create mulitple views for multiplayer mode. Also very helpfull in adding post-proccessing effects
*/

#include "FrameBuffer.h"
#include <SDL/SDL.h>
#include <iostream>
#include <glm/glm.hpp>

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height, unsigned char type)
{
	colorTextureBuffer = new Texture();
	// Sets up the txture of the framebuffer to reflect the screen size;
	colorTextureBuffer->SetWidth(width);
	colorTextureBuffer->SetHeight(height);

	BackgroundColor = glm::vec3(0, 0, 0);

	// Type can include GL_DEPTH#_STENCIL#, or GL_COLOR_ATTACHMENT#
	this->type = type;
	this->buffer_width = width;
	this->buffer_height = height;
}

FrameBuffer::~FrameBuffer()
{
}
