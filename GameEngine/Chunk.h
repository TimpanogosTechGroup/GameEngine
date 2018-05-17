#ifndef CHUNK_H
#define CHUNK_H

#include "PerlinGenerator.h"
#include "PhysicalInstance.h"
#include "Verticies.h"
#include "RenderItem.h"
#include "Object.h"
#include "ResourceManager.h"
#include <vector>

class Chunk : public RenderItem {
private:
	// Create a 32 x 32 square
	static const unsigned int CHUNK_SIZE = 8; // has to be multiples of the LOD
	static const unsigned int CHUNK_LOD = 8;
	static const unsigned int INDEX_ARRAY[];
	Verticies verts;
	Object mesh;
	PhysicalInstance physicalInstance;
	std::vector<unsigned int> indecies;

public:
	Chunk() : physicalInstance(), verts() {
		physicalInstance.setInstancePosition(glm::vec3(0, 0, 0));
	}
	~Chunk() {

	}

	RenderItem VBO;
	RenderItem EBO;

	Object& getMesh() { return mesh; };
	PhysicalInstance& getPhysicalInstance() { return physicalInstance; }

	void populate(PerlinGenerator& generator) {
		for (int i = 0; i < CHUNK_SIZE; i++) {
			for (int j = 0; j < CHUNK_SIZE; j++) {
				//verts.addDouble(i);
				//verts.addDouble(j);
				//verts.addDouble(0);
				mesh.GetVerticies().AddFloat(i);
				mesh.GetVerticies().AddFloat(generator.perlin(i, j, 1.1));
				mesh.GetVerticies().AddFloat(j);

				mesh.GetNormals().AddFloat(1);
				mesh.GetNormals().AddFloat(1);
				mesh.GetNormals().AddFloat(1);

				mesh.GetUVCoords().AddFloat(0);
				mesh.GetUVCoords().AddFloat(0);
				//verts.addDouble(generator.perlin(i, j, 1.1));
			}
		}

		for (int i = 0; i < CHUNK_SIZE - 1; i++) {
			for (int j = 0; j < CHUNK_SIZE - 1; j++) {
				indecies.push_back((j * CHUNK_SIZE) + i);
				indecies.push_back((j * CHUNK_SIZE) + i + 1);
				indecies.push_back((j * CHUNK_SIZE) + i + CHUNK_SIZE);

				indecies.push_back((j * CHUNK_SIZE) + i + 1);
				indecies.push_back((j * CHUNK_SIZE) + i + 1 + CHUNK_SIZE);
				indecies.push_back((j * CHUNK_SIZE) + i + CHUNK_SIZE);
			}
		}

		Material* tmp = new Material(1, 1, ResourceManager::getTexture("default"), ResourceManager::getShader("color_shader"), glm::vec4(1, 1, 1, 1));
		mesh.SetMaterial(tmp);

		std::cout << "Genertated Chunk:" << std::endl;
		verts.ToString();
	}

	std::vector<unsigned int>& getIndecies() { return indecies; }

	Verticies& getVerticies() {
		return verts;
	}

	static const unsigned int* getLODIndexArrayPtr() {
		return INDEX_ARRAY;
	}
};

#endif