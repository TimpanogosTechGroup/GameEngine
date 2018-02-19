#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <vector>
#include "Model.h"

class ModelManager {
public:
	ModelManager() {}
	void push_back(Model* model) { models.push_back(model); }
	int size() { return models.size(); }
	Model* GetModel(int i) { return models.at(i); }

private:
	std::vector<Model*> models;
};

#endif