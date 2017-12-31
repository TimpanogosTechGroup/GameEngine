/*
Author: Ben Brenkman
Notes: We can use this class to render different scences at the same time, or create mulitple views for multiplayer mode. Also very helpfull in adding post-proccessing effects
*/

#include "FrameBuffer.h"
#include <SDL/SDL.h>
#include <iostream>

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height, unsigned char type)
{
	// Sets up the txture of the framebuffer to reflect the screen size;
	//colorTextureBuffer->SetWidth(width);
	//colorTextureBuffer.SetHeight(height);
	// Type can include GL_DEPTH#_STENCIL#, or GL_COLOR_ATTACHMENT#
	this->type = type;
}

bool FrameBuffer::Initialize() {
	// Generate the id tags for the frambuffer

	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	colorTextureBuffer = new Texture();

	id = framebuffer; // Don't know why this works but there is somthing glitchy with all of this.
	// create a color attachment texture
	glGenTextures(1, &colorTextureBuffer->GetID());
	glBindTexture(GL_TEXTURE_2D, colorTextureBuffer->GetID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 600, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureBuffer->GetID(), 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 600, 480); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
																								  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

FrameBuffer::~FrameBuffer()
{
}
