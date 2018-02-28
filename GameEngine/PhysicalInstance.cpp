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

btTransform PhysicalInstance::getInstanceTrasform()
{
	return instanceTransform;
}

btQuaternion PhysicalInstance::getInstanceRotation()
{
	return instanceTransform.getRotation();
}

btVector3 PhysicalInstance::getInstancePositionbt()
{
	return instanceTransform.getOrigin();
}

glm::vec3 PhysicalInstance::getInstancePosition()
{
	glm::vec3 pos(instanceTransform.getOrigin().getX(), instanceTransform.getOrigin().getY(), instanceTransform.getOrigin().getZ());
	return pos;
}

float PhysicalInstance::getInstanceScale()
{
	return instanceScale;
}

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