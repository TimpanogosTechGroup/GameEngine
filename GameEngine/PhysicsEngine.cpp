#include <iostream>
#include "PhysicsEngine.h"
#include "Model.h"
#include "Logger.h"

void PhysicsEngine::Update(Model& model, Model& liberty) {
	dynamicsWorld->stepSimulation(1 / 100.f, 10);

	btTransform trans;
	rigidBodies.at(1)->getMotionState()->getWorldTransform(trans);
	model.SetPosition(glm::vec3(trans.getOrigin().x() / 500, trans.getOrigin().y() / 500, trans.getOrigin().z() / 500));

	rigidBodies.at(2)->getMotionState()->getWorldTransform(trans);
	liberty.SetPosition(glm::vec3(trans.getOrigin().x()/500, trans.getOrigin().y()/500, trans.getOrigin().z()/500));
	//std::cout << trans.getOrigin().x() << " " << trans.getOrigin().y() << " " << trans.getOrigin().z() << std::endl;
}