/*
Isaac Draper

This is the header to manage loading assets to opengl.
*/

#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <glm\stb_image.h>
#include <GLEW\glew.h>


#include <iostream>
#include <fstream>
#include <sstream>

class AssetManager {
public:
	// Parameters: ID of program, filepath to vertex shader, filepath to fragment shader
	void LoadShader(unsigned int& ID, const char* vertexPath, const char* fragmentPath);
	// Parameters: ID of texture, filepath to image
	void LoadTexture(unsigned int& texture, const char* file);
	void LoadModel(); // not complete, currently working on getting assimp to work

private:
	void CheckCompileErrors(GLuint shader, std::string type);
};