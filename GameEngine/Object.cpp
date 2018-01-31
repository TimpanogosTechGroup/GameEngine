#include "Object.h"
#include <iomanip>

Object::Object() { 
	position = glm::vec3(0, 0, 0);
}

void Object::SetMaterial(Material* material) {
	this->material = material;
}

void Object::SetPosition(glm::vec3 position) {
	this->position = position;
}

void Object::SetPosition(double x, double y, double z) {
	glm::vec3 pos(x, y, z);
	this->SetPosition(pos);
}

void Object::CreateBoundBox() {
	float xmin, ymin, zmin, xmax, ymax, zmax;
	std::vector<float> values;

	if (this->verticies.Size() > 8) {
		values = BoundingBoxMinMaxValues();
		
		xmin = values.at(0);
		ymin = values.at(1);
		zmin = values.at(2);
		xmax = values.at(3);
		ymax = values.at(4);
		zmax = values.at(5);

		boundingBox.SetMinValues(xmin, ymin, zmin);
		boundingBox.SetMaxValues(xmax, ymax, zmax);

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

std::vector<float> Object::BoundingBoxMinMaxValues() {
	float xmin, ymin, zmin, xmax, ymax, zmax;
	std::vector<float> values;

	xmin = this->verticies.GetValue(0);
	ymin = this->verticies.GetValue(1);
	zmin = this->verticies.GetValue(2);
	xmax = this->verticies.GetValue(0);
	ymax = this->verticies.GetValue(1);
	zmax = this->verticies.GetValue(2);

	for (unsigned int i = 0; i < this->verticies.Size() - 2; i += 3) {
		if (this->verticies.GetValue(i) < xmin) {
			xmin = this->verticies.GetValue(i);
		}
		else if (this->verticies.GetValue(i) > xmax) {
			xmax = this->verticies.GetValue(i);
		}
		if (this->verticies.GetValue(i + 1) < ymin) {
			ymin = this->verticies.GetValue(i + 1);
		}
		else if (this->verticies.GetValue(i + 1) > ymax) {
			ymax = this->verticies.GetValue(i + 1);
		}
		if (this->verticies.GetValue(i + 2) < zmin) {
			zmin = this->verticies.GetValue(i + 2);
		}
		else if (this->verticies.GetValue(i + 2) > zmax) {
			zmax = this->verticies.GetValue(i + 2);
		}
	}

	values.push_back(xmin); values.push_back(ymin); values.push_back(zmin);
	values.push_back(xmax); values.push_back(ymax); values.push_back(zmax);
	return values;
}

void Object::ToString() {

	std::cout << "Object: " << std::endl;
	std::cout << "Verticies" << std::endl << std::setw(10) << "x" << std::setw(10) << "y" << std::setw(10) << "z" << std::endl;

	verticies.ToString();
}