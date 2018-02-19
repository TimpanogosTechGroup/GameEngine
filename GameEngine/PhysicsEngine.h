#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>
#include "MotionState.h"

#include "ModelManager.h"
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
		motionStates.push_back(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -10, 0))));
	
		collisionObjects.push_back(new btStaticPlaneShape(btVector3(0, 1, 0), 1));
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, motionStates.at(0), collisionObjects.at(0), btVector3(0, 0, 0));
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
	bool AddObject(Object obj) {
		btBoxShape* shape = new btBoxShape(btVector3(btScalar(obj.boundingBox.GetxDist() / 2), btScalar(obj.boundingBox.GetyDist() / 2), btScalar(obj.boundingBox.GetzDist() / 2)));
		
		collisionObjects.push_back(shape);

		motionStates.push_back(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(obj.GetPostion().x, obj.GetPostion().y, obj.GetPostion().z))));
		AddRigidBody(collisionObjects.at(collisionObjects.size() - 1), motionStates.at(motionStates.size() -1));
		return true;
	}
	bool AddModel(Model model) {
		btBoxShape* shape = new btBoxShape(btVector3(btScalar(model.boundingBox.GetxDist() / 2), btScalar(model.boundingBox.GetyDist() / 2), btScalar(model.boundingBox.GetzDist() / 2)));

		collisionObjects.push_back(shape);

		motionStates.push_back(new btDefaultMotionState(model.GetTrasform()));
		//motionStates.push_back(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(model.GetPostion().x, model.GetPostion().y, model.GetPostion().z))));
		AddRigidBody(collisionObjects.at(collisionObjects.size() - 1), motionStates.at(motionStates.size() - 1));
		return true;
	}
	bool AddRigidBody(btCollisionShape* collisionShape, btMotionState* motionState) {
		btScalar mass = 1;
		btVector3 fallInertia(0, 0, 0);
		collisionShape->calculateLocalInertia(mass, fallInertia);
		btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, motionState, collisionShape, fallInertia);
		fallRigidBodyCI.m_startWorldTransform(btVector3(10, 10, 10));
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

	void Update(double delta, ModelManager& modelManager);

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
	std::vector<btMotionState*> motionStates; // ground is at index 0
};

#endif