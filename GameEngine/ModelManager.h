/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <vector>
#include "Model.h"
#include "PhysicalInstance.h"

class ModelManager {
private:
	std::vector<Model*> models;
	std::unordered_map<std::string, PhysicalInstance*> physicalInstances;
public:
	ModelManager() {}
	~ModelManager() {
		for (auto const& x : physicalInstances) delete x.second;
		//for (auto const& y : models) delete y;
	}
	void push_back(Model* model) { models.push_back(model); }
	int size() { return models.size(); }
	Model* GetModel(int i) { return models.at(i); }

	PhysicalInstance* getPhysicalInstance(std::string name) {
		auto pinstance = physicalInstances.find(name);
		if (pinstance != physicalInstances.end()) {
			return pinstance->second;
		}

		throw std::string("Unable to find model");
	}

	void push_back_instance(PhysicalInstance* physicalInstance) {
		physicalInstances.insert({ physicalInstance->getName(), physicalInstance });
	}

	std::unordered_map<std::string, PhysicalInstance*>& getPhysicalInstances() {
		return physicalInstances;
	}
};

#endif