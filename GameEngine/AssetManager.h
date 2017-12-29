/*
Isaac Draper

This is the header to manage loading assets to opengl.
*/

#pragma once

#include <GLEW\glew.h>

#include <assimp\scene.h>

#include <iostream>
#include <fstream>
#include <sstream>

class AssetManager {
public:
	// Parameters: ID of program, filepath to vertex shader, filepath to fragment shader
	void LoadShader(unsigned int& ID, const char* vertexPath, const char* fragmentPath);
	// Parameters: ID of texture, filepath to image
	void LoadTexture(unsigned int& texture, const char* file);
	void LoadModel(const char* pFile); // not complete, currently working on getting assimp to work

private:
	void CheckCompileErrors(GLuint shader, std::string type);
	void ProcessScene(const aiScene* scene);
};