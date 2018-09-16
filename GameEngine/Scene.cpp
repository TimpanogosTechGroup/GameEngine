/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "Scene.h"

void Scene::addEntity(Model * newModel)
{
	models.push_back(newModel);

	return;
}

void Scene::removeEntity(Model * modelToRemove)
{
	for (int i = 0; i < models.size(); i++)
	{
		if (models.at(i) == modelToRemove)
		{
			models.erase(models.begin() + i);
		}
	}

	return;
}
