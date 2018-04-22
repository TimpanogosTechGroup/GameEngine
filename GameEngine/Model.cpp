/**
	File:
    Purpose: 

    @author Isaac Draper, Ben Brenkman
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "Model.h"

void Model::CreateBoundBox() {
	float xmin, ymin, zmin, xmax, ymax, zmax;
	std::vector<float> values;

	values = this->GetObject(0)->BoundingBoxMinMaxValues();

	xmin = values.at(0);
	ymin = values.at(1);
	zmin = values.at(2);
	xmax = values.at(3);
	ymax = values.at(4);
	zmax = values.at(5);

	for (unsigned int i = 1; i < this->NumOfObjects(); i++) {
		values = this->GetObject(i)->BoundingBoxMinMaxValues();

		if (values.at(0) < xmin) {
			xmin = values.at(0);
		}
		else if (values.at(3) > xmax) {
			xmax = values.at(3);
		}
		if (values.at(1) < ymin) {
			ymin = values.at(1);
		}
		else if (values.at(4) > ymax) {
			ymax = values.at(4);
		}
		if (values.at(3) < zmin) {
			zmin = values.at(3);
		}
		else if (values.at(5) > zmax) {
			zmax = values.at(5);
		}
	}

	boundingBox.SetMinValues(xmin, ymin, zmin);
	boundingBox.SetMaxValues(xmax, ymax, zmax);

	this->boundBox.AddFloat(xmin)->AddFloat(ymin)->AddFloat(zmin);
	this->boundBox.AddFloat(xmax)->AddFloat(ymin)->AddFloat(zmin);
	this->boundBox.AddFloat(xmax)->AddFloat(ymax)->AddFloat(zmin);
	this->boundBox.AddFloat(xmin)->AddFloat(ymax)->AddFloat(zmin);
	this->boundBox.AddFloat(xmin)->AddFloat(ymax)->AddFloat(zmax);
	this->boundBox.AddFloat(xmin)->AddFloat(ymin)->AddFloat(zmax);
	this->boundBox.AddFloat(xmax)->AddFloat(ymin)->AddFloat(zmax);
	this->boundBox.AddFloat(xmax)->AddFloat(ymax)->AddFloat(zmax);
}