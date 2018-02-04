#pragma once

#include <vector>
#include "Object.h"
#include "Logger.h"
#include <btBulletDynamicsCommon.h>

class Model {
public:
	Object* GetObject(unsigned int n) { return this->objects.at(n); }
	void AddObject(Object* obj) { this->objects.push_back(obj); }
	unsigned int NumOfObjects() { return this->objects.size(); }
	Verticies GetBoundBox() { return boundBox; };

	void SetPosition(glm::vec3 p) {
		position = glm::vec3(p);
		for (int i = 0; i < objects.size(); i++) {
			objects.at(i)->SetPosition(p);
		}
	}
	glm::vec3 GetPostion() { return position; };

	void SetTransform(btTransform trans) {
		this->trans = trans;
		for (int i = 0; i < objects.size(); i++) {
			objects.at(i)->SetTransform(trans);
		}
	}

	const btTransform& GetTrasform() const { return trans; };

	void CreateBoundBox(); // NOTE: assumes at least 1 object that is NOT A PLANE (should work with plane, but more vertices than necessary - not tested)
	BoundingBox boundingBox;

private:
	std::vector<Object*> objects;
	Verticies boundBox;
	btTransform trans;
	glm::vec3 position;
};