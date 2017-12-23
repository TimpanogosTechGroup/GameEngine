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
	}
	float[] GetValues() {
		return this->values;
	}

private:
	std::vector<float> values;
};