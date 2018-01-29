#pragma once
#include "RenderItem.h"
#include <math.h>
#include <cmath>

class BoundingBox : public RenderItem
{
public:
	BoundingBox(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax);
	BoundingBox();
	~BoundingBox();

	// Set the individual xMin, yMin, zMin, xMax, yMax, zMax values seperatly
	void SetxMax(float value);
	void SetyMax(float value);
	void SetzMax(float value);
	void SetxMin(float value);
	void SetyMin(float value);
	void SetzMin(float value);

	// Get the individual xMin, yMin, zMin, xMax, yMax, zMax values seperatly
	float GetxMax();
	float GetyMax();
	float GetzMax();
	float GetxMin();
	float GetyMin();
	float GetzMin();

	// Set the Min values and Max values
	void SetMinValues(float xMin, float yMin, float zMin);
	void SetMaxValues(float xMax, float yMax, float zMax);

	float GetxDist() { return abs(xMax - xMin); }
	float GetyDist() { return abs(yMax - yMin); }
	float GetzDist() { return abs(zMax - zMin); }

	RenderItem VBO;

	void ToString();

private:
	float xMin, yMin, zMin, xMax, yMax, zMax;
};

