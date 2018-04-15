/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/

/**
	This is the header to manage loading assets to opengl.
	
	@author Isaac Draper, Ben Brenkman
	@version 1.0
*/

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

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
#include "CubeMap.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\cimport.h>
#include <assimp\postprocess.h>

class AssetManager {
public:
	/** 
		Parameters: filepath to vertex shader, filepath to fragment shader

		@param vertexPath the file location of the vertext shader
		@param fragmentPath the file location of the fragment shader

	*/
	static Shader* LoadShader(const char* vertexPath, const char* fragmentPath);

	/**
		loads a texture and adds it to the resource mananger

		@param file the texture file location
		@return the pointer to the texture being loaded

	*/
	static Texture* LoadTexture(const char* file);
	static Texture* LoadTexture(const char* name, const char* file);

	/**
		Load the model from the file pFile

		@param pFile the file location of the model
		@return the model that was loaded
	*/
	static Model* LoadModel(const char* pFile); // not complete, currently working on getting assimp to work

	static void LoadModelFull(const char* pFile, const char* folderName = "Andromeda");

	/**
		Loads a cube map with the texture starting at pFile and adding a _dir for each face

		@param pFile the file location to the texture with the cubemap
		@return the loaded cubemap
	*/
	static CubeMap* LoadCubeMap(const char* pFile);
private:
	/**
		load the material from an assimp scene of a specific model

		@param scene the assimp scene to get the material from
		@param mesh the mesh that we want the material
		@return the material that we want
	*/
	static Material* LoadMaterial(const aiScene* scene, const aiMesh* mesh);
};

#endif