/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include <string>
#include "Logger.h"
#include "ResourceManager.h"

#define LOG(message) /
	Logger::Log<ResourceManager>(DEBUG, message);

std::unordered_map<std::string, Texture*> ResourceManager::textures;
std::unordered_map<std::string, Shader*> ResourceManager::shaders;
std::unordered_map<std::string, Model*> ResourceManager::models;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::clean() {
	LOG("Deleting Textures: ");
	for (auto pointer : textures) {
		delete pointer.second; // A nullptr is being added to the map, we need to get rid of it or not add a nullptr
	}
	std::cout << std::endl;
	LOG("Deleting Shaders: ");
	for (auto pointer : shaders) {
		delete pointer.second;

	}
	std::cout << std::endl;
	LOG("Deleting Models: ");
	for (auto pointer : models) {
		std::cout << "Deleting model" << std::endl;
		delete pointer.second;
	}
}

Shader* ResourceManager::getShader(std::string name) {
	auto shader = shaders.find(name);
	if (shader != shaders.end()) {
		return shader->second;
	}
	else {
		return nullptr;
	}
}

Texture* ResourceManager::getTexture(std::string name) {
	auto texture = textures.find(name);
	if (texture != textures.end()) {
		return texture->second;
	}
	else {
		return textures["default"];
	}
}

Model * ResourceManager::getModel(std::string name)
{
	auto model = models.find(name);
	if (model != models.end()) {
		return model->second;
	}
	else {
		return models["default"];
	}
}

void ResourceManager::addShader(std::string name, Shader* shader) {
	shaders[name] = shader;
}

void ResourceManager::addTexture(std::string name, Texture* texture) {
	textures[name] = texture;
	LOG("Added Texture: ");
	std::cout << texture->GetID() << std::endl;
}

void ResourceManager::addModel(std::string name, Model * model)
{
	models[name] = model;
}

bool ResourceManager::hasTexture(std::string name)
{
	if (textures.find(name) != textures.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool ResourceManager::hasShader(std::string name)
{
	if (shaders.find(name) != shaders.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool ResourceManager::hasModel(std::string name)
{
	if (models.find(name) != models.end()) {
		return true;
	}
	else {
		return false;
	}
}

void ResourceManager::loadModel(const char * pFile, std::string name)
{
	if (ResourceManager::hasModel(pFile)) {
		ResourceManager::addModel(name, ResourceManager::getModel(pFile));
	}
	else {
		ResourceManager::addModel(name, AssetManager::LoadModel(pFile));
	}
}

void ResourceManager::loadModel(const char * pFile)
{
	if (ResourceManager::hasModel(pFile)) {
	
	}
	else {
		ResourceManager::addModel(pFile, AssetManager::LoadModel(pFile));
	}
}
