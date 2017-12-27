/*
Author: Ben Brenkman
Notes: We can use this class to render different scences at the same time, or create mulitple views for multiplayer mode. Also very helpfull in adding post-proccessing effects
*/

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height, unsigned int type)
{
	// Sets up the txture of the framebuffer to reflect the screen size;
	colorTextureBuffer.SetWidth(width);
	colorTextureBuffer.SetHeight(height);
	// Type can include GL_DEPTH#_STENCIL#, or GL_COLOR_ATTACHMENT#
	this->type = type;
}

bool FrameBuffer::Initialize() {
	// Generate the id tags for the frambuffer
	glGenFramebuffers(1, &id);
	glBindBuffer(GL_FRAMEBUFFER, id);

	// Generate an empty texture buffer for the framebuffer to render to
	glGenTextures(1, &colorTextureBuffer.GetID());
	glBindTexture(GL_TEXTURE_2D, colorTextureBuffer.GetID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, colorTextureBuffer.GetWidth(), colorTextureBuffer.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, type, GL_TEXTURE_2D, colorTextureBuffer.GetID(), 0);

	// Check to see if everything worked out all right
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

FrameBuffer::~FrameBuffer()
{
}
