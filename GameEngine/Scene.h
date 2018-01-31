#pragma once
#include"Model.h"
#include<vector>

class Scene
{
	std::vector<Model*> models;
	void AddModel(Model* newModel);
	void RemoveModel(Model* modelToRemove);
};

