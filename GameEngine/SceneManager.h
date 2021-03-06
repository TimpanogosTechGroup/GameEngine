/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#pragma once
#include"Scene.h"
#include<unordered_map>

class SceneManager
{
public:
	SceneManager() {};
	~SceneManager() { for (auto scene : sceneMap) delete scene.second; }
	std::unordered_map<std::string, Scene*> sceneMap;
	void CreateNewScene(std::string sceneName);
	Scene* GetScene(std::string sceneName);
};