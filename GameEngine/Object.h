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

	// TODO: Create 3d object to test the order of vertices for rendering purposes - assuming order matters (check bullet)
	void CreateBoundBox(); // NOTE: vertices size must be at least 18 to work properly, 18 will give a plane

	Verticies& GetVerticies() { return verticies; };
	Material* GetMaterial() { return &material; };
	glm::vec3 GetPostion() { return position; };
	Verticies& GetUVCoords() { return uvCoords; };
	Verticies GetBoundBox() { return boundBox; }

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