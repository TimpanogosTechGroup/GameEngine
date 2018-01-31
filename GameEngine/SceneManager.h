#pragma once
#include"Scene.h"
#include<unordered_map>

class SceneManager
{
	std::unordered_map<std::string, Scene*> sceneMap;
	void CreateNewScene(std::string sceneName);
	Scene* GetScene(std::string sceneName);
};

