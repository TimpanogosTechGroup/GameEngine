/**
	File:
    Purpose: 

    @author Isaac Draper, Ben Brenkman
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include <iostream>
#include "PhysicsEngine.h"
#include "Model.h"
#include "Logger.h"

using namespace std;

void PhysicsEngine::Update(double delta, ModelManager& modelManager) {
//	dynamicsWorld->stepSimulation(delta / 2000, 5);
//
//	//for (int i = 0; i < modelManager.size(); i++) {
//	//	btTransform trans;
//	//	rigidBodies.at(i+1)->getMotionState()->getWorldTransform(trans);
//	//	modelManager.GetModel(i)->SetPosition(glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z()));
//	//	modelManager.GetModel(i)->SetTransform(trans);
//	//}
//
//	for (auto &iter : modelManager.getPhysicalInstances()) {
//		btTransform trans;
//		rigidBodies[iter.second->getName()]->getMotionState()->getWorldTransform(trans);
//		//std::cout << rigidBodies[iter.second->getName()]->getMotionState()->getWorldTransform(trans) << endl;
//		//iter.second->setInstancePosition(glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z()));
//		iter.second->setInstanceTrasnform(trans);
//		//iter.second->setInstanceTrasnform(trans);
//	}
}