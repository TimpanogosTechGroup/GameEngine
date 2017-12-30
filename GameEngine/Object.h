/*
Isaac Draper:
This file is not complete
*/

#pragma once

#include "Verticies.h"
#include "Material.h"

class Object : public RenderItem {
public:
	// Constructors
	Object(float vert[], float norms[]) {
		verticies.SetValues(vert);
		normals.SetValues(norms);
	}
	Object();
	RenderItem VBO;

	void CreateBoundBox(); // not implemented

	Verticies& GetVerticies() { return verticies; };
	Material* GetMaterial() { return &material; };
	glm::vec3 GetPostion() { return position; };
	Verticies& GetUVCoords() { return uvCoords; };

	void SetMaterial(Material mat);
	void SetPosition(glm::vec3 position); // TODO this will be made to return the actual position from bullet phyics

private:
	Verticies verticies;
	Verticies normals;
	Verticies uvCoords;

	Verticies boundBox;
	Verticies attachNodes; // not implemented
	glm::vec3 position; // FIXME TODO this will be removed and replaced with the bullet physics stuff
	Material material;
	
};