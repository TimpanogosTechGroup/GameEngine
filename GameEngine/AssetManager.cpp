/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/

/*
Isaac Draper

This is the implementation to manage loading assets to opengl.

NOT COMPLETE
*/
#include <vector>

#include "AssetManager.h"
#include "ResourceManager.h"
#include "Logger.h"
#include "OpenGlRenderer.h"
#include "FileSystemManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <glm/stb_image.h>

#define LOG(message, level) /
	Logger::Log<AssetManager>(level, message);

#define LOG(message) /
	Logger::Log<AssetManager>(DEBUG, message);

#define LOGS /
	Logger::GetLogStream<AssetManager>()

// ID is the id of the program the shader will be linked to - initial value will be changed
Shader* AssetManager::LoadShader(const char* vertexPath, const char* fragmentPath) {
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	std::ofstream output;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		LOGS << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ :: " << vertexPath;
		Logger::LogClassStream<AssetManager>(LoggerLevel::ERROR);
		
	}
	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	Shader* shader = new Shader();

	Registry::GetRenderEngine()->CompileShader(SHADER_VERTEX, shader->vertex.GetID(), vShaderCode);
	Registry::GetRenderEngine()->CompileShader(SHADER_FRAGMENT, shader->fragment.GetID(), fShaderCode);
	Registry::GetRenderEngine()->LinkShaderProgram(*shader);
	
	LOG(std::string("Successfully loaded shader: " + std::string(vertexPath)).c_str(), DEBUG);

	return shader;
}

// basic version, eventually edit wrapping and filtering parameters
Texture* AssetManager::LoadTexture(const char* file) {
	return LoadTexture(file, file);
}

Texture * AssetManager::LoadTexture(const char * name, const char * file)
{

	if (ResourceManager::hasTexture(file) || ResourceManager::hasTexture(name)) {
		LOG("Already Loaded", DEBUG);
		return ResourceManager::getTexture(name);
	}

	Texture* texture = new Texture(); // Create a new texture
									  // Genereate buffers and bind
	glGenTextures(1, &texture->GetID());
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		texture->SetWidth(width);
		texture->SetHeight(height);

		ResourceManager::addTexture(name, texture);
	}
	else
	{
		LOGS << "Failed to load texture: " << file;
		Logger::LogClassStream<AssetManager>(DEBUG);
		LOG(stbi_failure_reason(), DEBUG);
		delete texture;
	}
	stbi_image_free(data);

	return texture;
}

Model* AssetManager::LoadModel(const char* pFile) {
	// not finished
	if (ResourceManager::hasModel(pFile)) {
		LOG("Model already loaded.....might need to double check your code", DEBUG);
	}

	Model* model = new Model();

	// Create an instance of the Importer class
	Assimp::Importer importer;

	//check if file exists
	std::ifstream fin(pFile);
	if (!fin.fail()) {
		fin.close();
	}
	else {
		LOGS << "Couldn't open this file : " << pFile;
		Logger::LogClassStream<AssetManager>(LoggerLevel::SEVERE);
		LOGS << importer.GetErrorString();
		Logger::LogClassStream<AssetManager>(LoggerLevel::SEVERE);
	}

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene) {
		Logger::GetLogStream<AssetManager>() << importer.GetErrorString();
		return nullptr;
	}
	else {
		LOGS << pFile << ": Loaded";
		Logger::LogClassStream<AssetManager>(LoggerLevel::INFO);
	}

	std::vector<float> vertices;
	std::vector<float> colors;
	std::vector<float> normals;
	std::vector<float> uvs;

	bool hasTex = false;

	//*Logger::GetLogStream<AssetManager>() << "File: " << pFile << " INFO" << std::endl << "#Meshes: " << scene->mNumMeshes << std::endl;

	for (unsigned int n = 0; n < scene->mNumMeshes; n++) {
		const aiMesh* mesh = scene->mMeshes[n];
		int iMeshFaces = mesh->mNumFaces;

		for (int k = 0; k < iMeshFaces; k++) {
			const aiFace& face = mesh->mFaces[k];

			for (int j = 0; j < 3; j++) {
				vertices.push_back(mesh->mVertices[face.mIndices[j]].x);
				vertices.push_back(mesh->mVertices[face.mIndices[j]].y);
				vertices.push_back(mesh->mVertices[face.mIndices[j]].z);

				if (mesh->HasNormals()) {
					normals.push_back(mesh->mNormals[face.mIndices[j]].x);
					normals.push_back(mesh->mNormals[face.mIndices[j]].y);
					normals.push_back(mesh->mNormals[face.mIndices[j]].z);
				}
				else {
					normals.push_back(1);
					normals.push_back(1);
					normals.push_back(1);
				}

				if (mesh->HasTextureCoords(0)) {
					uvs.push_back(mesh->mTextureCoords[0][face.mIndices[j]].x);
					uvs.push_back(mesh->mTextureCoords[0][face.mIndices[j]].y);
					//*Logger::GetLogStream<AssetManager>() << mesh->mTextureCoords[0][face.mIndices[j]].x << mesh->mTextureCoords[0][face.mIndices[j]].y << std::endl;
				}
				else {
					uvs.push_back(1);
					uvs.push_back(1);
				}

				//if (mesh->HasVertexColors(0)) {
				//	colors.push_back(mesh->mColors[face.mIndices[j]]->r);
				//	colors.push_back(mesh->mColors[face.mIndices[j]]->g);
				//	colors.push_back(mesh->mColors[face.mIndices[j]]->b);
				//}
			}
		}

		Object* object = new Object(vertices, normals, uvs);
		object->SetMaterial(LoadMaterial(scene, mesh));
		model->AddObject(object);

		vertices.clear();
		colors.clear();
		normals.clear();
		uvs.clear();
	}

	// Everything (assimp) will be cleaned up by the importer destructor
	model->setRotation(0, 0, 0);
	model->SetPosition(glm::vec3(0, 0, 0));
	ResourceManager::addModel(pFile, model);
	model->CreateBoundBox();
	return model;
}

void AssetManager::LoadModelFull(const char * pFile, const char* folderName)
{
	Model* model = LoadModel(FileSystemManager::getInstance().getModelPathString(pFile, folderName).c_str());

	Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->CompileModel(*model);
	Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->CompileBoundingBox(model->boundingBox);
}

CubeMap * AssetManager::LoadCubeMap(const char * pFile)
{
	CubeMap* cube = new CubeMap(pFile);

	// Load the textures
	if (ResourceManager::hasTexture(pFile)) {
		LOG("Already Loaded", DEBUG);
		//return ResourceManager::getTexture(pFile);
	}

	Texture* texture = new Texture(); // Create a new texture
	 // Genereate buffers and bind
	glGenTextures(1, &texture->GetID());
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->GetID());
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	for (unsigned int i = 0; i < cube->getTextureLocations().size(); i++) {
		stbi_set_flip_vertically_on_load(false); // This is just a quick fix, but it should not work.
		unsigned char *data = stbi_load(cube->getTextureLocations().at(i).c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			texture->SetWidth(width);
			texture->SetHeight(height);
		}
		else
		{
			Logger::GetLogStream<AssetManager>() << "Failed to load texture: " << pFile;
			Logger::LogClassStream<AssetManager>(LoggerLevel::ERROR);
		}
		stbi_image_free(data);
	}

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	ResourceManager::addTexture(pFile, texture);
	cube->SetTexture(texture);

	Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->CompileCubeMap(*cube);

	return cube;
}

Material* AssetManager::LoadMaterial(const aiScene* scene, const aiMesh* mesh) {
	aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
	aiString name;
	aiColor4D diffuse;

	aiString texturePath;
	aiString textureAmbient;
	aiString textureSpec;
	aiString textureNormalPath;

	Texture* texture;
	Texture* textureAO;
	Texture* textureSpecular;
	Texture* textureNormal;

	bool containsText = true;

	if (AI_SUCCESS != mat->Get(AI_MATKEY_NAME, name)) {
		LOGS << "Didn't load model properly... :(";
		Logger::LogClassStream<AssetManager>(LoggerLevel::ERROR);
	}
	else {
		aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
	}
	// Load Diffuse texture map ALBEDO
	if (mat->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), texturePath) == AI_SUCCESS) {
		Logger::GetLogStream<AssetManager>() << "Loaded LOAD_MATERIAL: " << texturePath.C_Str();
		Logger::LogClassStream<AssetManager>(LoggerLevel::DEBUG);
		containsText = false;
		texture = LoadTexture(texturePath.C_Str());
	}
	else {
		LOG("No Diffuse Texture", DEBUG);
		texture = ResourceManager::getTexture("default");
	}

	// Load ambient texture map AMBIENT
	if (mat->Get(AI_MATKEY_TEXTURE(aiTextureType_AMBIENT, 0), textureAmbient) == AI_SUCCESS) {
		LOGS << "Loaded LOAD_MATERIAL: " << textureAmbient.C_Str();
		Logger::LogClassStream<AssetManager>(LoggerLevel::DEBUG);
		textureAO = LoadTexture(textureAmbient.C_Str());
	}
	else {
		LOG("No Ambient Texture.", DEBUG);
		textureAO = ResourceManager::getTexture("default");
	}

	// Load specular/rougness texture map
	if (mat->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), textureSpec) == AI_SUCCESS) {
		LOGS << "Loaded LOAD_MATERIAL: " << textureSpec.C_Str();
		Logger::LogClassStream<AssetManager>(LoggerLevel::DEBUG);
		textureSpecular = LoadTexture(textureSpec.C_Str());
	}
	else {
		LOG("No Specular Texture.", DEBUG);
		textureSpecular = ResourceManager::getTexture("default");
	}

	// Load normals texture map
	if (mat->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), textureNormalPath) == AI_SUCCESS) {
		LOGS << "Loaded LOAD_MATERIAL: " << textureNormalPath.C_Str();
		Logger::LogClassStream<AssetManager>(LoggerLevel::DEBUG);
		textureNormal = LoadTexture(textureNormalPath.C_Str());
	}
	else {
		LOG("No Nomrmal Texture.", DEBUG);
		textureNormal = ResourceManager::getTexture("default");
	}

	// Load metallic texture map
	if (mat->Get(AI_MATKEY_TEXTURE(aiTextureType_SHININESS, 0), textureNormalPath) == AI_SUCCESS) {
		LOGS << "Loaded LOAD_MATERIAL: " << textureNormalPath.C_Str();
		Logger::LogClassStream<AssetManager>(LoggerLevel::DEBUG);
		textureNormal = LoadTexture(textureNormalPath.C_Str());
	}
	else {
		LOG("No Shinniness Texture.", DEBUG);
		textureNormal = ResourceManager::getTexture("default");
	}

	//Shader* other = LoadShader("Shader//color_vert.glsl", "Shader//color_frag.glsl");
	Material* tmp = new Material(1, 1, texture, containsText ? ResourceManager::getShader("color_shader") : ResourceManager::getShader("texture_shader"), glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	return tmp;
}