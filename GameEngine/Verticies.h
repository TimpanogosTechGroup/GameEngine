/*
Isaac Draper:
This file is not complete, simple storage class right now
*/

#pragma once

#include <vector>
#include <iostream>

class Verticies {
public:
	void SetValues(float vert[]) {
		for (unsigned int i = 0; i < sizeof(vert) / sizeof(vert[0]); i++) {
			values.push_back(vert[i]);
		}
	};
	void SetValues(float vert[], unsigned int size) {
		for (unsigned int i = 0; i < size; i++) {
			values.push_back(vert[i]);
		}
	};

	// You cannot return an array from a function, arrays are too large and so must be returned by pointer
	// This is a neat trick to get the array data from the vector wrapper &name[0] will return the array data
	float* GetValues() { return &values[0]; };
	std::vector<float>* GetValueVector() { return &values; };
	float GetValue(unsigned int i) { return values.at(i); }

	// Adds a float to the vertecies vector
	Verticies* AddFloat(float a);

	int Size() { return values.size(); };

	// Debug function
	void ToString();

private:
	std::vector<float> values;
};