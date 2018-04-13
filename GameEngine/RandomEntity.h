#ifndef RANDOM_ENTITY_H
#define RANDOM_ENTITY_H

#include "DynamicEntity.h"
#include "Renderable.h"
#include "OpenGlRenderer.h"
#include "World.h"

/*
Author: Ben Brenkman aka JustBremkman

Description:
This is a test class to test out the entity system
*/

class RandomEntity : public virtual DynamicEntity, Renderable {
private:

public:
	RandomEntity(PhysicalInstance ph) {
		this->setPhysicalInstance(ph);
	}
	~RandomEntity() {};
	void update() override {

	}

	void render() override { // Render the entity
		Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->RenderPhysicalInstance(World::getInstance().getCamera(), getPhysicalInstance());
	}

	void onWorldTickUpdate() override {

	}
};

#endif