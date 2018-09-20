/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef SCENE_H
#define SCENE_H

#include"Entity.h"
#include<vector>
#include <glm\glm.hpp>

class Scene{
public:
	std::vector<Entity*> entities;
	void addEntity(Entity* entityToAdd, glm::vec3 entityPosition);
	void removeEntity(Entity* entity);

private:
	glm::vec3 worldLocation;
};

#endif