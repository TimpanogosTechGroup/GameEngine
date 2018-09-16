/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef SCENE_H
#define SCENE_H

#include"Model.h"
#include<vector>
#include "MemoryManager.h"

class Scene : MemoryManager
{
public:
	std::vector<Model*> models;
	void addEntity(Model* newModel);
	void removeEntity(Model* modelToRemove);

	void setup() {}
	void clean() {}
};

#endif