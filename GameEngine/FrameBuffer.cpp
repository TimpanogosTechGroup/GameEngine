#include "FrameBuffer.h"



FrameBuffer::FrameBuffer(unsigned int width, unsigned int height, unsigned int type)
{
	colorTextureBuffer.SetWidth(width);
	colorTextureBuffer.SetHeight(height);
	this->type = type;
}

bool FrameBuffer::Initialize() {
	// Generate the id tags for the frambuffer
	glGenFramebuffers(1, &ID);
	glBindBuffer(type, ID);

	// Generate an empty texture buffer for the framebuffer to render to
	glGenTextures(1, &colorTextureBuffer.GetID());
	glBindTexture(GL_TEXTURE_2D, colorTextureBuffer.GetID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, colorTextureBuffer.GetWidth(), colorTextureBuffer.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureBuffer.GetID(), 0);

	// Check to see if everything worked out all right
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

FrameBuffer::~FrameBuffer()
{
}
