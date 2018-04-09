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
