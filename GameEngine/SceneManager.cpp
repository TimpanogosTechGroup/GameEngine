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

Scene* SceneManager::createNewScene(std::string sceneName)
{
	if (sceneMap.find(sceneName) != sceneMap.end()) {
		//Logger::Log<SceneManager>(INFO, std::string("Scene with name: " + sceneName + " already exists.").c_str());
		return sceneMap[sceneName];
	}

	sceneMap[sceneName] = new Scene();
	return sceneMap[sceneName];
}

Scene * SceneManager::getScene(std::string sceneName)
{
	if (sceneMap.find(sceneName) != sceneMap.end()) {
		return sceneMap[sceneName];
	}

	//Logger::Log<SceneManager>(INFO, std::string("Scene with name: " + sceneName + " does not exist. Returning nullptr").c_str());
	return nullptr;
}

void SceneManager::addScene(std::string name, Scene* scene) {
	if (sceneMap.find("name") != sceneMap.end()) {
		//Logger::Log<SceneManager>(INFO, std::string("Scene with name: " + name + " already exists.").c_str());
		return;
	}

	sceneMap[name] = scene;
}
