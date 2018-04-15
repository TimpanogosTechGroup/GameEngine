/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#pragma once
#include"Model.h"
#include<vector>

class Scene
{
public:
	std::vector<Model*> models;
	void AddModel(Model* newModel);
	void RemoveModel(Model* modelToRemove);
};

