/*
Isaac Draper:
This file is not complete
*/

#pragma once

#include "Verticies.h"
#include "Material.h"

class Object {
public:
	// Constructors
	Object(float vert[], float norms[]) {
		verticies.SetValues(vert);
		normals.SetValues(norms);
	}
	Object();

	void CreateBoundBox(); // not implemented

	Verticies& GetVerticies() { return verticies; };

private:
	Verticies verticies;
	Verticies normals;
	Verticies boundBox;
	Verticies attachNodes; // not implemented

	Material material;
};