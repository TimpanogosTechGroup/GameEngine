/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/

/*
Isaac Draper:
This class does not include the actual texture information, perhaps it would be good to store the
opengl texture ID here? --> What do you think of this method? I added a new class that holds the ID info.

*/

#pragma once
#include "RenderItem.h"

class Texture : public RenderItem {
public:
	// We can set default values in the constructor, so we don't need to have two constructors
	Texture(unsigned int widthPix = 0, unsigned int heightPix = 0) {
		this->width = widthPix;
		this->height = heightPix;
	}

	int GetWidth() { return this->width; }
	int GetHeight() { return this->height; }
	void SetWidth(int w) { this->width = w; }
	void SetHeight(int h) { this->height = h; }

private:
	int width;
	int height;
};