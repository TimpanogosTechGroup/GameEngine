/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "PhysicalInstance.h"

#include <iostream>
using namespace std;

PhysicalInstance::PhysicalInstance()
{
	instanceModelReference = nullptr;
}

PhysicalInstance::PhysicalInstance(std::string uniqueName, Model * reference, glm::vec3 position, glm::vec3 rotation, float scale)
{
	instanceName = uniqueName;
	instanceModelReference = reference;
	btTransform trans;
	trans.setOrigin(btVector3(position.x, position.y, position.z));
	trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, 0));
	instanceTransform = trans;
	instanceScale = scale;
}

PhysicalInstance::~PhysicalInstance()
{
}

/*
	Gets the transform of instance
*/
btTransform PhysicalInstance::getInstanceTrasform()
{
	return instanceTransform;
}

/*
	Gets the Rotation of the instance
*/
btQuaternion PhysicalInstance::getInstanceRotation()
{
	return instanceTransform.getRotation();
}

/*
	Get position of the instance
*/
btVector3 PhysicalInstance::getInstancePositionbt()
{
	return instanceTransform.getOrigin();
}

/*
	Get Instance position
*/
glm::vec3 PhysicalInstance::getInstancePosition()
{
	glm::vec3 pos(instanceTransform.getOrigin().getX(), instanceTransform.getOrigin().getY(), instanceTransform.getOrigin().getZ());
	return pos;
}

/*
	Get Instance Scale
*/
float PhysicalInstance::getInstanceScale()
{
	return instanceScale;
}


/*
	Gets the model reference
*/
Model & PhysicalInstance::getModelReference()
{
	// TODO: insert return statement here
	return *instanceModelReference;
}

/*
	Set position of instance
*/
void PhysicalInstance::setInstancePosition(btVector3 position)
{
	instanceTransform.setOrigin(position);
}

/*
	Set position of instance
*/
void PhysicalInstance::setInstancePosition(glm::vec3 position)
{
	btVector3 pos(position.x, position.y, position.z);
	setInstancePosition(pos);
	//instanceTransform.setOrigin(pos);
}

/*
	Set rotation of instance
*/
void PhysicalInstance::setInstanceRotation(btQuaternion rotation)
{
	instanceTransform.setRotation(rotation);
}

/*
	Set instance scale
*/
void PhysicalInstance::setInstanceScale(float scale)
{
	instanceScale = scale;
}

/*
	Set instance scale
*/
void PhysicalInstance::setInstanceScale(float scale, float range)
{
	instanceScale = normalize(scale, 0, range);
}

/*
	Set instance Model reference
*/
void PhysicalInstance::setInstanceModelReference(Model* model)
{
	instanceModelReference = model;
}

void PhysicalInstance::setInstanceTrasnform(btTransform tran)
{
	this->instanceTransform = tran;
}

/*
	Normailizes float values
*/
float PhysicalInstance::normalize(float norm, float startRange, float endRange)
{
	return (endRange - startRange) / norm;
}