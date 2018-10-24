/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "Verticies.h"

Verticies* Verticies::AddFloat(float a) {
	values.push_back(a); 
	return this;
}

void Verticies::addDouble(double a) {
	values.push_back(a);
}

// Debug function
void Verticies::ToString() {
	for (auto &i : values) {
		std::cout << i << ", ";
	}
	std::cout << std::endl;
}