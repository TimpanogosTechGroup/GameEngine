/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include"Scene.h"
#include<unordered_map>
#include "World.h"

class SceneManager
{
public:
	SceneManager() {};
	~SceneManager() { 
		//for (auto scene : sceneMap) delete scene.second; 
	}

	std::unordered_map<std::string, Scene*> sceneMap;
	Scene* createNewScene(std::string sceneName);
	Scene* getScene(std::string sceneName);
	void addScene(std::string name, Scene* scene);

	void loadSceneIntoWorld(World* world);
	void unloadScene(World* world);

	void cleanup();
};

#endif