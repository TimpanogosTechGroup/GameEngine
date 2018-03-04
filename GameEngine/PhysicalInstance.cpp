#include "PhysicalInstance.h"

PhysicalInstance::PhysicalInstance()
{
	instanceModelReference = nullptr;
}

PhysicalInstance::PhysicalInstance(std::string uniqueName, Model & reference, glm::vec3 position, glm::vec3 rotation, float scale)
{
	instanceName = uniqueName;
	instanceModelReference = &reference;
	btTransform trans;
	trans.setOrigin(btVector3(position.x, position.y, position.z));
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

void PhysicalInstance::setInstancePosition(btVector3 position)
{
	instanceTransform.setOrigin(position);
}

void PhysicalInstance::setInstancePosition(glm::vec3 position)
{
	btVector3 pos(position.x, position.y, position.z);
	instanceTransform.setOrigin(pos);
}

void PhysicalInstance::setInstanceRotation(btQuaternion rotation)
{
	instanceTransform.setRotation(rotation);
}

void PhysicalInstance::setInstanceScale(float scale)
{
	instanceScale = scale;
}

void PhysicalInstance::setInstanceScale(float scale, float range)
{
	instanceScale = normalize(scale, 0, range);
}

void PhysicalInstance::setInstanceModelReference(Model& model)
{
	instanceModelReference = &model;
}

float PhysicalInstance::normalize(float norm, float startRange, float endRange)
{
	return (endRange - startRange) / norm;
}