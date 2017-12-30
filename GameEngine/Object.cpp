#include "Object.h"

Object::Object() { }

void Object::SetMaterial(Material material) {
	this->material = material;
}

void Object::SetPosition(glm::vec3 position) {
	this->position = position;
}