/*
Isaac Draper:
This class does not include the actual texture information, perhaps it would be good to store the
opengl texture ID here?

*/

#pragma once

class Texture {
public:
	Texture() {
		this->width = 0;
		this->height = 0;
	}
	Texture(int w, int h) {
		this->width = w;
		this->height = h;
	}
	int GetWidth() { return this->width; }
	int GetHeight() { return this->height; }
	void SetWidth(int w) { this->width = w; }
	void SetHeight(int h) { this->height = h; }

private:
	int width;
	int height;
};