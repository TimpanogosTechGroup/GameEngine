#pragma once

#include <vector>
#include "Object.h"

class Model {
public:
	Object* GetObject(unsigned int n) { return this->objects.at(n); }
	void AddObject(Object* obj) { this->objects.push_back(obj); }
	unsigned int NumOfObjects() { return this->objects.size(); }
private:
	std::vector<Object*> objects;
};