#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include "Chunk.h"
#include "Registry.h"
#include "OpenGlRenderer.h"
#include "World.h"
#include <vector>
#include <unordered_map>

class ChunkManager {
private:
	std::vector<Chunk*> mActiveChunks;
	std::vector<Chunk*> mPassiveChunks;
	std::unordered_map<glm::vec2, Chunk*> mChunkGrid;
	glm::vec3 mActivePosition;
	OpenGlRenderer renderer;
public:
	ChunkManager(OpenGlRenderer renderer) {
		this->renderer = renderer;
	}

	bool isChunkActive(glm::vec2 position) {
		if (mChunkGrid.find(position) != mChunkGrid.end())
			return true;
		return false;
	}

	Chunk* getChunk(glm::vec2 position) {
		if (isChunkActive(position))
			return mChunkGrid.at(position);
		return nullptr;
	}

	void setChunk(glm::vec2 position, Chunk* chunk) {
		mChunkGrid[position] = chunk;
	}

	void updateActiveChunks() {
		for (auto chunk : mActiveChunks) {
			chunk->update();
		}
	}

	void updatePassiveChunks() {
		for (auto chunk : mPassiveChunks)
			chunk->update();
	}

	void updateChunkManager() {
		int xGridPosition = mActivePosition.x / Chunk::CHUNK_SIZE;
		int yGridPosition = mActivePosition.y / Chunk::CHUNK_SIZE;
		int zGridPosition = mActivePosition.z / Chunk::CHUNK_SIZE;

		
	}

	void renderActiveChunks() {
		for (auto chunk : mActiveChunks) {
			renderer.renderChunk(&World::getInstance().getCamera(), chunk);
		}
	}


	/*
		@param position sets the active position in the world, this allows the chunk manager to manage the chunks accordingly
	*/
	void updateActivePosition(glm::vec3 position) {
			mActivePosition = position;
	}
};

#endif