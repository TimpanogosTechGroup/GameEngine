#include <iostream>
#include "PhysicsEngine.h"
#include "Model.h"
#include "Logger.h"

void PhysicsEngine::Update(Model model, Model liberty) {
	dynamicsWorld->stepSimulation(1 / 100.f, 10);

	btTransform trans;
	rigidBodies.at(1)->getMotionState()->getWorldTransform(trans);
	model.SetPosition(glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z()));

	rigidBodies.at(2)->getMotionState()->getWorldTransform(trans);
	liberty.SetPosition(glm::vec3(trans.getOrigin().x()/500, trans.getOrigin().y()/500, trans.getOrigin().z()/500));
	std::cout << trans.getOrigin().x() << " " << trans.getOrigin().y() << " " << trans.getOrigin().z() << std::endl;
}

void PhysicsEngine::PhysicsTest() {
	Object p;
	Object p2;
	Model m1;

	p.SetPosition(glm::vec3(0, 100, 0));
	p2.SetPosition(glm::vec3(0, 10, 0));
	m1.SetPosition(glm::vec3(0, 500, 0));

	AddObject(p);
	AddObject(p2);
	AddModel(m1);

	for (int i = 0; i < 30; i++) {
		dynamicsWorld->stepSimulation(1 / 60.f, 10);

		for (int j = 1; j < rigidBodies.size(); j++) {
			btTransform trans;
			rigidBodies.at(j)->getMotionState()->getWorldTransform(trans);
			std::cout << i << "\t(" << trans.getOrigin().x() << ", " << trans.getOrigin().y() << ", " << trans.getOrigin().z() << ")"<< std::endl;;
		}
	}
}