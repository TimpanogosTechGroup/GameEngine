#include <iostream>
#include "PhysicsEngine.h"
#include "Object.h"
#include "Logger.h"

void PhysicsEngine::PhysicsTest() {
	btCollisionShape* fallShape = new btSphereShape(1);
	btCollisionShape* fallShape2 = new btSphereShape(1);

	Object p;
	Object p2;

	AddObject(p);
	AddObject(p2);

	std::cout << rigidBodies.size();

	for (int i = 0; i < 30; i++) {
		dynamicsWorld->stepSimulation(1 / 60.f, 10);

		for (int j = 1; j < rigidBodies.size() - 1; j++) {
			btTransform trans;
			rigidBodies.at(i)->getMotionState()->getWorldTransform(trans);
			
			std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
		}
	}
}