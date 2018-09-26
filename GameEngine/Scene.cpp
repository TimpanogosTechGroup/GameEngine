/**
	File: Scene.cpp
    Purpose: This class is to help with the coordinate system. It uses local coordinates with entities 
	and then translates those coordinates into world coordinates

    @author Ben Brenkman
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "Scene.h"

// Adds entity to the scene with a position. Will be added to the world and the coordinates translated.
void Scene::addEntity(Entity * entity, glm::vec3 entityPosition)
{
	entity_pos entry;
	entry.entity = entity;
	entry.position = entityPosition;
	entries.push_back(entry);

	return;
}

// Isn't used
void Scene::removeEntity(Entity * modelToRemove)
{

	return;
}
