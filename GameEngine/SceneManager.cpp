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

void SceneManager::CreateNewScene(std::string sceneName)
{
	sceneMap[sceneName] = new Scene;
	return;
}

Scene * SceneManager::GetScene(std::string sceneName)
{
	return sceneMap[sceneName];
}
