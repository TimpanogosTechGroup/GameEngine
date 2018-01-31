#include "Scene.h"

void Scene::AddModel(Model * newModel)
{
	models.push_back(newModel);

	return;
}

void Scene::RemoveModel(Model * modelToRemove)
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
