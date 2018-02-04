#include <iostream>
#include "PhysicsEngine.h"
#include "Model.h"
#include "Logger.h"

void PhysicsEngine::Update(Model& model, Model& liberty) {
	dynamicsWorld->stepSimulation(1 / 500.f, 5);

	btTransform trans;
	rigidBodies.at(1)->getMotionState()->getWorldTransform(trans);
	model.SetPosition(glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z()));

	rigidBodies.at(2)->getMotionState()->getWorldTransform(trans);
	liberty.SetPosition(glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z()));
	//std::cout << trans.getOrigin().x() << " " << trans.getOrigin().y() << " " << trans.getOrigin().z() << std::endl;
}