/*
Isaac Draper:
This file is not complete
*/

#pragma once

#include "Verticies.h"
#include "Material.h"

class Object {
public:
	Object(float vert[], float norms[]) {
		verticies.SetValues(vert);
		normals.SetValues(norms);
	}
	void CreateBoundBox(); // not implemented
private:
	Verticies verticies;
	Verticies normals;
	Verticies boundBox;
	Verticies attachNodes; // not implemented

	Material material;
};