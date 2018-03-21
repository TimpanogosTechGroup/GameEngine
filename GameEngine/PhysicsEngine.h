#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>
#include "MotionState.h"

#include <glm/glm.hpp>
#include "ModelManager.h"
#include "RegistryEntry.h"
#include "Logger.h"
#include "Properties.h"

class PhysicsEngine : public RegistryEntry {
public:
	PhysicsEngine() {
		// We need to change the construction of this constructor
		// Once we implement some way to load the scenes, we'll put the ground loading in the initialization instead of the constructor and then the problem will resolve itself

		broadphase = new btDbvtBroadphase();
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

		dynamicsWorld->setGravity(btVector3(0, Properties::Get<float>("gravity"), 0));
		//dynamicsWorld->setGravity(btVector3(0, 9.8, 0));
		motionStates["ground"] = (new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -10, 0))));
	
		collisionObjects["ground"] = (new btStaticPlaneShape(btVector3(0, 1, 0), 1));
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, motionStates["ground"], collisionObjects["ground"], btVector3(0, 0, 0));
		rigidBodies["ground"] = (new btRigidBody(groundRigidBodyCI));
		AddRigidBodyToWorld(rigidBodies["ground"]);
	}
	~PhysicsEngine() {
		//for (unsigned int i = 0; i < collisionObjects.size(); i++) {
		//	delete collisionObjects.at(i);
		//}
		//for (unsigned int i = 0; i < rigidBodies.size(); i++) {
		//	dynamicsWorld->removeRigidBody(rigidBodies.at(i));
		//	delete rigidBodies.at(i);
		//}

		delete groundMotionState;
		delete fallMotionState;

		delete dynamicsWorld;
		delete solver;
		delete dispatcher;
		delete collisionConfiguration;
		delete broadphase;
	}
	//bool AddObject(Object obj, double mass) {
	//	btBoxShape* shape = new btBoxShape(btVector3(btScalar(obj.boundingBox.GetxDist() / 2), btScalar(obj.boundingBox.GetyDist() / 2), btScalar(obj.boundingBox.GetzDist() / 2)));
	//	
	//	collisionObjects.push_back(shape);

	//	motionStates.push_back(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(obj.GetPostion().x, obj.GetPostion().y, obj.GetPostion().z))));
	//	AddRigidBody(collisionObjects.at(collisionObjects.size() - 1), motionStates.at(motionStates.size() -1), mass);
	//	return true;
	//}
	//bool AddObject(Object obj) {
	//	return AddObject(obj, 1);
	//}
	//bool AddModel(Model& model, double mass) {
	//	btBoxShape* shape = new btBoxShape(btVector3(btScalar(model.boundingBox.GetxDist() / 2), btScalar(model.boundingBox.GetyDist() / 2), btScalar(model.boundingBox.GetzDist() / 2)));

	//	collisionObjects.push_back(shape);

	//	motionStates.push_back(new btDefaultMotionState(model.GetTrasform()));
	//	AddRigidBody(collisionObjects.at(collisionObjects.size() - 1), motionStates.at(motionStates.size() - 1), mass);
	//	return true;
	//}
	bool addModelInstance(PhysicalInstance* instance, double mass) {
		btBoxShape* shape = new btBoxShape(btVector3(btScalar(instance->getModelReference().boundingBox.GetxDist() / 2), btScalar(instance->getModelReference().boundingBox.GetyDist() / 2), btScalar(instance->getModelReference().boundingBox.GetzDist() / 2)));

		collisionObjects[instance->getName()] = shape;

		motionStates[instance->getName()] = new btDefaultMotionState(instance->getInstanceTrasform());
		AddRigidBody(*instance, collisionObjects[instance->getName()], motionStates[instance->getName()], mass);
		return true;
	}
	//bool AddModel(Model& model) {
	//	return AddModel(model, 1);
	//}
	bool AddRigidBody(PhysicalInstance& instance, btCollisionShape* collisionShape, btMotionState* motionState, double m) {
		btScalar mass = static_cast<btScalar>(m);
		btVector3 fallInertia(0, 0, 0);
		collisionShape->calculateLocalInertia(mass, fallInertia);
		btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, motionState, collisionShape, fallInertia);
		fallRigidBodyCI.m_startWorldTransform(btVector3(10, 10, 10));
		rigidBodies[instance.getName()] = new btRigidBody(fallRigidBodyCI);
		if (AddRigidBodyToWorld(rigidBodies[instance.getName()]))
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

	void AddForce(std::string name, glm::vec3 f) {
		AddForce(name, btVector3(f.x, f.y, f.z));
	}
	void AddForce(std::string i, btVector3 force) {
		rigidBodies.at(i)->activate(true);
		//rigidBodies.at(i)->applyCentralForce(force);
		rigidBodies.at(i)->applyForce(force, btVector3(0, 1, 0));
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

	//std::vector<btCollisionShape*> collisionObjects; // ground is at index 0
	//std::vector<btRigidBody*> rigidBodies; // ground is at index 0
	//std::vector<btMotionState*> motionStates; // ground is at index 0

	std::unordered_map<std::string, btRigidBody*> rigidBodies;
	std::unordered_map<std::string, btCollisionShape*> collisionObjects;
	std::unordered_map<std::string, btMotionState*> motionStates;
};

#endif