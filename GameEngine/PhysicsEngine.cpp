#include <iostream>
#include "PhysicsEngine.h"
#include "Model.h"
#include "Logger.h"

void PhysicsEngine::Update(double delta, Model& model, Model& liberty) {
	dynamicsWorld->stepSimulation(delta / 2000, 5);

	btTransform trans;
	rigidBodies.at(1)->getMotionState()->getWorldTransform(trans);
	model.SetPosition(glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z()));
	model.SetTransform(trans);

	rigidBodies.at(2)->getMotionState()->getWorldTransform(trans);
	liberty.SetPosition(glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z()));
	liberty.SetTransform(trans);
	//std::cout << trans.getOrigin().x() << " " << trans.getOrigin().y() << " " << trans.getOrigin().z() << std::endl;
}