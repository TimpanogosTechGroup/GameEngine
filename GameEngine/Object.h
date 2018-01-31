/*
Isaac Draper:
This file is not complete
*/

#pragma once

#include <vector>

#include "Verticies.h"
#include "Material.h"
#include "BoundingBox.h"

class Object : public RenderItem {
public:
	// Constructors
	Object(float vert[], float norms[]) {
		verticies.SetValues(vert);
		normals.SetValues(norms);
		position = glm::vec3(0, 0, 0);
	}
	// this constructor is for model loading, necesarry becuase not possible to get array size using pointer
	Object(float vert[], float norms[], float uvs[], unsigned int size, unsigned int uvSize) {
		verticies.SetValues(vert, size);
		normals.SetValues(norms, size);
		uvCoords.SetValues(uvs, uvSize);
		position = glm::vec3(0, 0, 0);
	}
	Object(std::vector<float> verticies, std::vector<float> normals) {
		
		for (auto &v : verticies) {
			this->verticies.AddFloat(v);
		}
		for (auto &n : normals) {
			this->normals.AddFloat(n);
		}
		position = glm::vec3(0, 0, 0);
	}
	Object(std::vector<float> verticies, std::vector<float> normals, std::vector<float> uvs) {

		for (auto &v : verticies) {
			this->verticies.AddFloat(v);
		}
		for (auto &n : normals) {
			this->normals.AddFloat(n);
		}
		for (auto &uv : uvs) {
			this->uvCoords.AddFloat(uv);
		}

		position = glm::vec3(0, 0, 0);
	}

	Object();
	RenderItem VBO;

	// TODO: Create 3d object to test the order of vertices for rendering purposes - assuming order matters (check bullet)
	void CreateBoundBox(); // NOTE: vertices size must be at least 18 to work properly, 18 will give a plane
	std::vector<float> BoundingBoxMinMaxValues();

	Verticies& GetVerticies() { return verticies; };
	Verticies& GetNormals() { return normals; };
	Material* GetMaterial() { return material; };
	glm::vec3 GetPostion() { return position; };
	Verticies& GetUVCoords() { return uvCoords; };
	Verticies GetBoundBox() { return boundBox; };

	void SetMaterial(Material* mat);
	void SetPosition(glm::vec3 position);
	void SetPosition(double x, double y, double z);
	void ToString();

	BoundingBox boundingBox;

private:
	Verticies verticies;
	Verticies normals;
	Verticies uvCoords;
	Verticies boundBox;

	glm::vec3 position;

	Material* material;
	
};