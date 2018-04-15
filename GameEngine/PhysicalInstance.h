/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef MODEL_H
#define MODEL_H

/*
	This clas holds all the information for an instance of an object
	Scale, Transformation etc.
*/

#include "Model.h"
#include <btBulletDynamicsCommon.h>

class PhysicalInstance
{
private:
	btTransform instanceTransform; // This is the transofmation of the instance
	float instanceScale; // This is the scale factor of the instance
	Model* instanceModelReference; // This is the model that the instance takes after
	std::string instanceName;

	float normalize(float norm, float startRange, float endRange); // Nomrailzes the float
public:
	PhysicalInstance();
	PhysicalInstance(std::string uniqueName, Model* reference, glm::vec3 position, glm::vec3 rotation, float scale);
	~PhysicalInstance();

	btTransform getInstanceTrasform();
	btQuaternion getInstanceRotation();
	btVector3 getInstancePositionbt();
	glm::vec3 getInstancePosition();
	float getInstanceScale();
	Model& getModelReference();

	std::string getName() const { return instanceName; }

	void setInstancePosition(btVector3 position);
	void setInstancePosition(glm::vec3 position);
	void setInstanceRotation(btQuaternion rotation);
	void setInstanceScale(float scale);
	void setInstanceScale(float scale, float range);
	void setInstanceModelReference(Model* model);
	void setInstanceTrasnform(btTransform tran);
};

#endif