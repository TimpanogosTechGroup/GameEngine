#include "Object.h"

Object::Object() { 
	position = glm::vec3(0, 0, 0);
}

void Object::SetMaterial(Material material) {
	this->material = material;
}

void Object::SetPosition(glm::vec3 position) {
	this->position = position;
}

void Object::CreateBoundBox() {
	float xmin, ymin, zmin, xmax, ymax, zmax;

	if (this->verticies.Size() > 8) {

		xmin = this->verticies.GetValue(0);
		ymin = this->verticies.GetValue(1);
		zmin = this->verticies.GetValue(2);
		xmax = this->verticies.GetValue(0);
		ymax = this->verticies.GetValue(1);
		zmax = this->verticies.GetValue(2);

		for (unsigned int i = 0; i < this->verticies.Size() - 2; i+=3) {
			if (this->verticies.GetValue(i) < xmin) {
				xmin = this->verticies.GetValue(i);
			}
			else if (this->verticies.GetValue(i) > xmax) {
				xmax = this->verticies.GetValue(i);
			}
			if (this->verticies.GetValue(i + 1) < ymin) {
				ymin = this->verticies.GetValue(i+1);
			}
			else if (this->verticies.GetValue(i + 1) > ymax) {
				ymax = this->verticies.GetValue(i+1);
			}
			if (this->verticies.GetValue(i + 2) < zmin) {
				zmin = this->verticies.GetValue(i+2);
			}
			else if (this->verticies.GetValue(i + 2) > zmax) {
				zmax = this->verticies.GetValue(i+2);
			}
		}

		if (this->verticies.Size() == 18) {
			this->boundBox.AddFloat(xmin)->AddFloat(ymin)->AddFloat(zmin);
			this->boundBox.AddFloat(xmax)->AddFloat(ymin)->AddFloat(zmin);
			this->boundBox.AddFloat(xmax)->AddFloat(ymax)->AddFloat(zmin);
			this->boundBox.AddFloat(xmin)->AddFloat(ymin)->AddFloat(zmin);
			this->boundBox.AddFloat(xmax)->AddFloat(ymax)->AddFloat(zmin);
			this->boundBox.AddFloat(xmin)->AddFloat(ymax)->AddFloat(zmin);
		}
		else {
			this->boundBox.AddFloat(xmin)->AddFloat(ymin)->AddFloat(zmin);
			this->boundBox.AddFloat(xmax)->AddFloat(ymin)->AddFloat(zmin);
			this->boundBox.AddFloat(xmax)->AddFloat(ymax)->AddFloat(zmin);
			this->boundBox.AddFloat(xmin)->AddFloat(ymax)->AddFloat(zmin);
			this->boundBox.AddFloat(xmin)->AddFloat(ymax)->AddFloat(zmax);
			this->boundBox.AddFloat(xmin)->AddFloat(ymin)->AddFloat(zmax);
			this->boundBox.AddFloat(xmax)->AddFloat(ymin)->AddFloat(zmax);
			this->boundBox.AddFloat(xmax)->AddFloat(ymax)->AddFloat(zmax);
		}
	}
	else {
		std::cout << "ERROR::CreateBoundBox()::Object has less than 3 vertices - cannot create box" << std::endl;
	}

	return;
}