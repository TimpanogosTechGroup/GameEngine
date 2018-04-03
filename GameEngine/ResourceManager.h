#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <vector>
#include <unordered_map>
#include "Texture.h"
#include "Shader.h"
#include <string>
#include "RegistryEntry.h"
#include "Model.h"
#include "AssetManager.h"

class ResourceManager : public RegistryEntry
{
public:
	ResourceManager();
	~ResourceManager();

	static Shader* getShader(std::string name);
	static Texture* getTexture(std::string name);
	static Model* getModel(std::string name);

	static void addShader(std::string name, Shader* shader);
	static void addTexture(std::string name, Texture* texture);
	static void addModel(std::string name, Model* model);

	static bool hasTexture(std::string name);
	static bool hasShader(std::string name);
	static bool hasModel(std::string name);

	static void loadModel(const char* pFile, std::string name);
	static void loadModel(const char* pFile);

	static void clean();

private:
	static std::unordered_map<std::string, Texture*> textures;
	static std::unordered_map<std::string, Shader*> shaders;
	static std::unordered_map<std::string, Model*> models;
};

#endif RESOURCE_MANAGER_H