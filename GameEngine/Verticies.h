/*
Isaac Draper:
This file is not complete, simple storage class right now
*/

#pragma once

#include <vector>

class Verticies {
public:
	void SetValues(float vert[]) {
		for (unsigned int i = 0; i < sizeof(vert) / sizeof(vert[0]); i++) {
			values.push_back(vert[i]);
		}
	};

	// You cannot return an array from a function, arrays are too large and so must be returned by pointer
	float* GetValues() { return &values[0]; };

private:
	std::vector<float> values;
};