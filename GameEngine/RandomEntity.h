/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef RANDOM_ENTITY_H
#define RANDOM_ENTITY_H

#include "DynamicEntity.h"
#include "Renderable.h"
//#include "OpenGlRenderer.h"
//#include "World.h"

/*
Author: Ben Brenkman aka JustBremkman

Description:
This is a test class to test out the entity system
*/

class RandomEntity : public virtual DynamicEntity, Renderable {
private:

public:
	RandomEntity(std::string modelName) { // Change this to get a better way to handle the model reference
		this->setPhysicalInstance(PhysicalInstance(std::string("modelName"), ResourceManager::getModel(getModelLocation(modelName)), glm::vec3(0, 0, 0), glm::vec3(0, 5, 0), 1.0));
	}
	~RandomEntity() {};
	void update() override {

	}

	void render(Camera* camera) override { // Render the entity
		Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->RenderPhysicalInstance(*camera, getPhysicalInstance());
		Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->RenderBoundingBox(*camera, getPhysicalInstance(), glm::vec3(1, 1, 1));
	}

	void onWorldTickUpdate() override {

	}
};

#endif