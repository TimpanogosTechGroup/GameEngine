/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef ENTITY_H
#define ENTITY_H

#include "PhysicalInstance.h"
#include "FileSystemManager.h"

/*
Author: Ben Brenkman aka JustBremkman

Description:
This is the base entity class. Has the abstract methods update() and onWorldTickUpdate()
These functions will be inhereted by the inherited classes and define game logic
*/

typedef std::string guid;

class Entity {
private:
	PhysicalInstance mPhsyicalInstance; // This contains the model reference and some basic properties
										//std::string GUID;
										// Add some kind of input management here. Can also use an empty or null one

	bool isTangeable = true; // Sets the property for collision detection
	static const guid ENTITY_STATIC_GUID;

protected:
	void setPhysicalInstance(PhysicalInstance physicalInstance) {
		mPhsyicalInstance = physicalInstance;
	}

	std::string getModelLocation(std::string modelName, std::string folderName = "Andromeda") {
		return FileSystemManager::getInstance().getModelPathString(modelName, folderName);
	}

public:
	virtual void update(void) = 0; // This is the entity update function, is called every frame.
	virtual void onWorldTickUpdate() = 0; // This is the world tick update. All Entities that want this to be called are added to a queue that runs every so often
	virtual ~Entity() {};

	// Member functions
	void setIsTangeable(bool val) {
		isTangeable = val;
	}
	bool isEntityTangeable() {
		return isTangeable;
	}

	PhysicalInstance& getPhysicalInstance() {
		return mPhsyicalInstance;
	}
};

#endif