#include "ResourceManager.h"

std::unordered_map<std::string, Texture*> ResourceManager::textures;
std::unordered_map<std::string, Shader*> ResourceManager::shaders;
std::unordered_map<std::string, Model*> ResourceManager::models;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	for (auto pointer : textures) {
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
		return nullptr;
	}
}

Model * ResourceManager::getModel(std::string name)
{
	auto model = models.find(name);
	if (model != models.end()) {
		return model->second;
	}
	else {
		return nullptr;
	}
}

void ResourceManager::addShader(std::string name, Shader* shader) {
	shaders[name] = shader;
}

void ResourceManager::addTexture(std::string name, Texture* texture) {
	textures[name] = texture;
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
