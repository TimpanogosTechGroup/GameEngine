#include <iostream>
#include "PhysicsEngine.h"
#include "Model.h"
#include "Logger.h"

void PhysicsEngine::Update(double delta, ModelManager& modelManager) {
	dynamicsWorld->stepSimulation(delta / 2000, 5);

	//for (int i = 0; i < modelManager.size(); i++) {
	//	btTransform trans;
	//	rigidBodies.at(i+1)->getMotionState()->getWorldTransform(trans);
	//	modelManager.GetModel(i)->SetPosition(glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z()));
	//	modelManager.GetModel(i)->SetTransform(trans);
	//}

	for (auto &iter : modelManager.getPhysicalInstances()) {
		btTransform trans;
		rigidBodies[iter.second.getName()]->getMotionState()->getWorldTransform(trans);
		iter.second.setInstancePosition(glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z()));
		iter.second.setInstanceTrasnform(trans);
	}
}