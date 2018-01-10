#pragma once
#include <vector>
#include <unordered_map>
#include "Texture.h"
#include "Shader.h"
#include <string>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static Shader* getShader(std::string name);
	static Texture* getTexture(std::string name);

	static void addShader(std::string name, Shader* shader);
	static void addTexture(std::string name, Texture* texture);

private:
	static std::unordered_map<std::string, Texture*> textures;
	static std::unordered_map<std::string, Shader*> shaders;
};

