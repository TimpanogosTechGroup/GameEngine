#pragma once

#include <vector>
#include "Object.h"

class Model {
public:
	Object* GetObject(unsigned int n) { return this->objects.at(n); }
	void AddObject(Object* obj) { this->objects.push_back(obj); }
	unsigned int NumOfObjects() { return this->objects.size(); }
	Verticies GetBoundBox() { return boundBox; };

	void CreateBoundBox(); // NOTE: assumes at least 1 object that is NOT A PLANE (should work with plane, but more vertices than necessary - not tested)
	BoundingBox boundingBox;

private:
	std::vector<Object*> objects;
	Verticies boundBox;
};