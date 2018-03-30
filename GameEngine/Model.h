#pragma once

#include <vector>
#include "Object.h"
#include "Logger.h"
#include <btBulletDynamicsCommon.h>

class Model {
public:
	Model() : boundingBox() {
		trans.setOrigin(btVector3(0, 0, 0));
		trans.setRotation(btQuaternion(0, 0, 0, 0));
	}
	~Model() { for (auto const& x : objects) delete x; }
	Object* GetObject(unsigned int n) { return this->objects.at(n); }
	void AddObject(Object* obj) { this->objects.push_back(obj); }
	unsigned int NumOfObjects() { return this->objects.size(); }
	Verticies GetBoundBox() { return boundBox; };

	void SetPosition(glm::vec3 p) {
		trans.setOrigin(btVector3(p.x, p.y, p.z));
		for (unsigned int i = 0; i < objects.size(); i++) {
			objects.at(i)->SetPosition(p);
		}
	}
	glm::vec3 GetPostion() { return glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()); };

	void SetTransform(btTransform trans) {
		this->trans = trans;
		for (auto &obj : objects) {
			obj->SetTransform(trans);
		}
	}

	void setRotation(float yaw = 0, float pitch = 0, float roll = 0) {
		trans.setRotation(btQuaternion(yaw, pitch, roll));
		for (unsigned int i = 0; i < objects.size(); i++) {
			objects.at(i)->setRotation(yaw, pitch, roll);
		}
	}

	const btTransform& GetTrasform() const { return trans; };

	void CreateBoundBox(); // NOTE: assumes at least 1 object that is NOT A PLANE (should work with plane, but more vertices than necessary - not tested)
	BoundingBox boundingBox;

private:
	std::vector<Object*> objects;
	Verticies boundBox;
	btTransform trans;
};