/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "SceneManager.h"
#include<string>
#include<unordered_map>

// Creates a new scene and gives the reference
Scene* SceneManager::createNewScene(std::string sceneName)
{
	if (sceneMap.find(sceneName) != sceneMap.end()) {
		Logger::Log<SceneManager>(INFO, std::string("Scene with name: " + sceneName + " already exists.").c_str());
		return sceneMap[sceneName];
	}

	sceneMap[sceneName] = new Scene();
	return sceneMap[sceneName];
}


// Gets an insatance of a scene
Scene * SceneManager::getScene(std::string sceneName)
{
	if (sceneMap.find(sceneName) != sceneMap.end()) {
		return sceneMap[sceneName];
	}

	Logger::Log<SceneManager>(INFO, std::string("Scene with name: " + sceneName + " does not exist. Returning nullptr").c_str());
	return nullptr;
}

// Adds scene to the SceneManager. This lets us load the scene into the world.
void SceneManager::addScene(std::string name, Scene* scene) {
	if (sceneMap.find("name") != sceneMap.end()) {
		Logger::Log<SceneManager>(INFO, std::string("Scene with name: " + name + " already exists.").c_str());
		return;
	}

	sceneMap[name] = scene;
}

void SceneManager::loadSceneIntoWorld(std::string name) {
	if (world) {
		Scene* scene = getScene(name);
		// Load every entity in to the world and translate the coordinate system
	}
}

void SceneManager::unloadScene(std::string name) {

}

void SceneManager::setContext(World* context) {
	if (context) {
		this->world = world;
	}
	else {
		// Throw an pointer null exception
	}
}

void SceneManager::cleanup() {
	for (auto v : sceneMap) {
		//v.second->clean();
		delete v.second;  // Deletes the memory
	}
}
