/*
Isaac Draper

This is the header to manage loading assets to opengl.
*/

#pragma once

#include <GLEW\glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <assimp\scene.h>
#include "Shader.h"
#include "Texture.h"

class AssetManager {
public:
	// Parameters: filepath to vertex shader, filepath to fragment shader
	static Shader* LoadShader(const char* vertexPath, const char* fragmentPath);
	// Parameters: ID of texture, filepath to image
	static Texture* LoadTexture(const char* file);

	void LoadModel(const char* pFile); // not complete, currently working on getting assimp to work

private:
	void CheckCompileErrors(GLuint shader, std::string type);
	void ProcessScene(const aiScene* scene);
};