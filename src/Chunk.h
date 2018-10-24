#ifndef CHUNK_H
#define CHUNK_H

#include "PerlinGenerator.h"
#include "PhysicalInstance.h"
#include "Verticies.h"
#include "RenderItem.h"
#include "Object.h"
#include "ResourceManager.h"
#include <vector>
#include "MemoryManager.h"

class Chunk : public RenderItem, MemoryManager {
public:
	static const unsigned int CHUNK_SIZE = 32; // has to be multiples of the LOD
	Material* tmp;
private:
	// Create a 32 x 32 square
	static const unsigned int CHUNK_LOD = 8;
	static const unsigned int INDEX_ARRAY[];
	Verticies verts;
	Object mesh;
	PhysicalInstance physicalInstance;
	std::vector<unsigned int> indecies;
	int x_offset = 0, y_offset = 0;

	// Loading and unloading markers
	bool markUnload;

public:
	Chunk(int xoff, int yoff) : physicalInstance(), verts() {
		physicalInstance.setInstancePosition(glm::vec3(0, 0, 0));
		x_offset = xoff;
		y_offset = yoff;
	}
	~Chunk() {
		//clean();
	}

	RenderItem VBO;
	RenderItem EBO;

	Object& getMesh() { return mesh; };
	PhysicalInstance& getPhysicalInstance() { return physicalInstance; }

	void populate(PerlinGenerator& generator) {

		std::vector<glm::vec3> verticies(CHUNK_SIZE * CHUNK_SIZE);
		std::vector<glm::vec3> normals(CHUNK_SIZE * CHUNK_SIZE);

		int count = 0;

		for (int i = 0; i < CHUNK_SIZE; i++) {
			for (int j = 0; j < CHUNK_SIZE; j++) {
				int x = i + (x_offset * (CHUNK_SIZE - 1));
				int y = j + (y_offset * (CHUNK_SIZE - 1));
				float height = generator.perlin(x, y, 1.1);

				mesh.GetVerticies().AddFloat(i);
				mesh.GetVerticies().AddFloat(height);
				mesh.GetVerticies().AddFloat(j);

				mesh.GetUVCoords().AddFloat(0);
				mesh.GetUVCoords().AddFloat(0);

				verticies.at(count) = glm::vec3(x, height, y);
				count++;
			}
		}

		// Always remains the same
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

		for (int k = 0; k < indecies.size(); k += 3) {

			glm::vec3 vert1 = verticies.at(indecies.at(k));
			glm::vec3 vert2 = verticies.at(indecies.at(k + 1));
			glm::vec3 vert3 = verticies.at(indecies.at(k + 2));

			glm::vec3 normal = glm::cross(vert2 - vert1, vert3 - vert1);
			glm::normalize(normal);

			normals.at(indecies.at(k)) = normal;
			normals.at(indecies.at(k + 1)) = normal;
			normals.at(indecies.at(k + 2)) = normal;
		}

		//std::cout << "Normals" << std::endl;
		for (auto n : normals) {
			mesh.GetNormals().AddFloat(n.x);
			mesh.GetNormals().AddFloat(n.z);
			mesh.GetNormals().AddFloat(n.y);

			//std::cout << n.x << ", " << n.y << ", " << n.z << std::endl;
		}

		tmp = new Material(1, 1, ResourceManager::getTexture("default"), ResourceManager::getShader("chunk_shader"), glm::vec4(1, 1, 1, 1));
		mesh.SetMaterial(tmp);

		std::cout << "Genertated Chunk:" << std::endl;
		verts.ToString();
	}

	std::vector<unsigned int>& getIndecies() { return indecies; }

	int getChunkXOffset() {
		return x_offset;
	}

	int getChunkYOffset() {
		return y_offset;
	}

	Verticies& getVerticies() {
		return verts;
	}

	static const unsigned int* getLODIndexArrayPtr() {
		return INDEX_ARRAY;
	}

	void update() {

	}

	// Memory Management
	void setup() {

	}

	void clean() {
		delete tmp;
	}
};

#endif