#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>
#include "RegistryEntry.h"
#include "Logger.h"
#include "Properties.h"

class PhysicsEngine : public RegistryEntry {
public:
	PhysicsEngine(){
		broadphase = new btDbvtBroadphase();
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

		dynamicsWorld->setGravity(btVector3(0, Properties::Get<float>("gravity"), 0));
		groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
		fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	
		collisionObjects.push_back(new btStaticPlaneShape(btVector3(0, 1, 0), 1));
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, collisionObjects.at(0), btVector3(0, 0, 0));
		rigidBodies.push_back(new btRigidBody(groundRigidBodyCI));
		AddRigidBodyToWorld(rigidBodies.at(rigidBodies.size() - 1));
	}
	~PhysicsEngine() {
		for (int i = 0; i < collisionObjects.size(); i++) {
			delete collisionObjects.at(i);
		}
		for (int i = 0; i < rigidBodies.size(); i++) {
			dynamicsWorld->removeRigidBody(rigidBodies.at(i));
			delete rigidBodies.at(i);
		}

		delete groundMotionState;
		delete fallMotionState;

		delete dynamicsWorld;
		delete solver;
		delete dispatcher;
		delete collisionConfiguration;
		delete broadphase;
	}
	bool AddObject(btCollisionShape* shape) { // eventually accept object's vertices
		collisionObjects.push_back(shape);
		AddRigidBody(collisionObjects.at(collisionObjects.size() - 1));
		return true;
	}
	bool AddRigidBody(btCollisionShape* collisionShape) {
		btScalar mass = 1;
		btVector3 fallInertia(0, 0, 0);
		collisionShape->calculateLocalInertia(mass, fallInertia);
		btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, collisionShape, fallInertia);
		rigidBodies.push_back(new btRigidBody(fallRigidBodyCI));
		if (AddRigidBodyToWorld(rigidBodies.at(rigidBodies.size() - 1)))
			return true;
		return false;
	}
	bool AddRigidBodyToWorld(btRigidBody* rigidBody) {
		dynamicsWorld->addRigidBody(rigidBody);
		return true;
	}
	bool RemoveRigidBodyFromWorld(btRigidBody* rigidBody) {
		dynamicsWorld->removeRigidBody(rigidBody);
		return true;
	}

	void PhysicsTest();

private:
	btBroadphaseInterface * broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	btDefaultMotionState* groundMotionState;
	btDefaultMotionState* fallMotionState;

	std::vector<btCollisionShape*> collisionObjects; // ground is at index 0
	std::vector<btRigidBody*> rigidBodies; // ground is at index 0
};

#endif PHYSICSENGINE_H