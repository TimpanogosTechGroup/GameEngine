#ifndef CHUNK_H
#define CHUNK_H

#include "PerlinGenerator.h"
#include "Verticies.h"

class Chunk {
private:
	// Create a 32 x 32 square
	static const unsigned int CHUNK_SIZE = 32; // has to be multiples of the LOD
	static const unsigned int CHUNK_LOD = 8;
	static const unsigned int INDEX_ARRAY[];
	Verticies verts;
public:
	Chunk() {

	}
	~Chunk() {

	}

	void populate(PerlinGenerator& generator) {
		for (int i = 0; i < CHUNK_SIZE; i++) {
			for (int j = 0; j < CHUNK_SIZE; j++) {
				verts.AddFloat(generator.perlin(i, j, 1.1));
			}
		}

		std::cout << "Genertated Chunk:" << std::endl;
		verts.ToString();
	}
};

#endif