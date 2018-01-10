#include "ResourceManager.h"

std::unordered_map<std::string, Texture*> ResourceManager::textures;
std::unordered_map<std::string, Shader*> ResourceManager::shaders;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
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

void ResourceManager::addShader(std::string name, Shader* shader) {
	shaders[name] = shader;
}

void ResourceManager::addTexture(std::string name, Texture* texture) {
	textures[name] = texture;
}
