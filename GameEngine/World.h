#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include "DynamicEntity.h"
#include "StaticEntity.h"
#include "Logger.h"
#include <vector>

#define LOG(message) \
	Logger::Log<World>(DEBUG, message);

class World {
public:
	static World& getInstance() {
		static World* world = nullptr;
		if (!world) {
			world = new World();
		}
		return *world;
	}

	World() : mWorldEntities() {

	}

	void addEntityToWorld(Entity* e) {
		if (DynamicEntity* entityptr = dynamic_cast<DynamicEntity*>(e)) {
			LOG("Dynamic Entity Added to world");
		}
		else if (StaticEntity* entityptr = dynamic_cast<StaticEntity*>(e)) {
			LOG("StaticBody entity added to the world.");
		}

		mWorldEntities.push_back(e); // Adds it to the world list of entities to update and render and pass events and such
	}

	void update() {
		for (auto &entity : mWorldEntities) {
			entity->update();
		}
	}

private:
	static World* world;
	std::vector<Entity*> mWorldEntities;
};

#endif