#include <iostream>
#include "PhysicsEngine.h"

void PhysicsEngine::PhysicsTest() {
	btCollisionShape* fallShape = new btSphereShape(1);

	AddObject(fallShape);

	for (int i = 0; i < 3; i++) {
		dynamicsWorld->stepSimulation(1 / 60.f, 10);

		btTransform trans;
		rigidBodies.at(1)->getMotionState()->getWorldTransform(trans);

		std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
	}
}