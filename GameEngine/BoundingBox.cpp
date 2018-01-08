#include "BoundingBox.h"
#include <iostream>

BoundingBox::BoundingBox(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax)
{
	this->xMin = xMin;
	this->yMin = xMin;
	this->zMin = xMin;
	this->xMax = xMax;
	this->yMax = xMax;
	this->zMax = xMax;
}

BoundingBox::BoundingBox() {
	this->xMin = 0;
	this->yMin = 0;
	this->zMin = 0;
	this->xMax = 0;
	this->yMax = 0;
	this->zMax = 0;
}

BoundingBox::~BoundingBox()
{
}

// Set the individual xMin, yMin, zMin, xMax, yMax, zMax values seperatly
void BoundingBox::SetxMax(float value) {
	this->xMax = value;
}
void BoundingBox::SetyMax(float value) {
	this->yMax = value;
}
void BoundingBox::SetzMax(float value) {
	this->zMax = value;
}
void BoundingBox::SetxMin(float value) {
	this->xMin = value;
}
void BoundingBox::SetyMin(float value) {
	this->yMin = value;
}
void BoundingBox::SetzMin(float value) {
	this->zMin = value;
}

// Get the individual xMin, yMin, zMin, xMax, yMax, zMax values seperatly
float BoundingBox::GetxMax() {
	return this->xMax;
}
float BoundingBox::GetyMax() {
	return this->yMax;
}
float BoundingBox::GetzMax() {
	return this->zMax;
}
float BoundingBox::GetxMin() {
	return this->xMin;
}
float BoundingBox::GetyMin() {
	return this->yMin;
}
float BoundingBox::GetzMin() {
	return this->zMin;
}

// Set the Min values and Max values
void BoundingBox::SetMinValues(float xMin, float yMin, float zMin) {
	this->xMin = xMin;
	this->yMin = yMin;
	this->zMin = zMin;
}
void BoundingBox::SetMaxValues(float xMax, float yMax, float zMax) {
	this->xMax = xMax;
	this->yMax = yMax;
	this->zMax = zMax;
}

void BoundingBox::ToString() {
	std::cout << "boudning Box: " << std::endl;
	std::cout << "X Min: " << xMin << ", Y Min: " << yMin << ", Z Min " << zMin << std::endl;
	std::cout << "X Max: " << xMax << ", Y Max: " << yMax << ", Z Max " << zMax << std::endl;
}