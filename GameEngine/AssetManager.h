/*
Isaac Draper

This is the header to manage loading assets to opengl.
*/

#pragma once

#include <GLEW\glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "Object.h"
#include "Model.h"
#include "Material.h"
#include "Texture.h"
#include "Registry.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\cimport.h>
#include <assimp\postprocess.h>

class AssetManager {
public:
	// Parameters: filepath to vertex shader, filepath to fragment shader
	static Shader* LoadShader(const char* vertexPath, const char* fragmentPath);
	// Parameters: ID of texture, filepath to image
	static Texture* LoadTexture(const char* file);

	static Model* LoadModel(const char* pFile, Texture* texture, Shader* frameBufferEffects); // not complete, currently working on getting assimp to work

private:
	static Material* LoadMaterial(const aiScene* scene, Shader* shader);
};