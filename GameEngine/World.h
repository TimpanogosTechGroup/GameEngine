/**
	File:
    Purpose: 

    @author Ben Brenkman
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include "DynamicEntity.h"
#include "StaticEntity.h"
#include "Renderable.h"
#include "Logger.h"
#include <vector>
#include "PhysicsEngine.h"
#include "InputManager.h"
#include "Profiler.h"

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

	static void destroy() {
		if (world)
			delete world;
	}

	World() : mWorldEntities(), mRenderableEntities() {}

	void addEntityToWorld(Entity* e) {
		if (DynamicEntity* entityptr = dynamic_cast<DynamicEntity*>(e)) {
			LOG("Dynamic Entity Added to world");
			mPhysicsEngine->addModelInstance(&e->getPhysicalInstance(), 1.0);
			mManager.push_back_instance(&e->getPhysicalInstance());
		}
		else if (StaticEntity* entityptr = dynamic_cast<StaticEntity*>(e)) {
			LOG("StaticBody entity added to the world.");
		}

		if (Renderable* entityptr = dynamic_cast<Renderable*>(e)) {
			mRenderableEntities.push_back(dynamic_cast<Renderable*>(e));
		}

		mWorldEntities.push_back(e); // Adds it to the world list of entities to update and render and pass events and such
	}

	void initialize() {
		mPhysicsEngine = new PhysicsEngine();
	}

	void shutdown() {
		for (int i = 0; i < mWorldEntities.size(); i++) {
			Entity* m = mWorldEntities.at(i);
			delete m;
		}

		delete mPhysicsEngine;
	}

	void update() {
		PROFILE_PUSH("physics update");
		mPhysicsEngine->Update(2, mManager);
		PROFILE_POP;

		PROFILE_PUSH("entity update");
		for (auto &entity : mWorldEntities) {
			entity->update();
		}
		PROFILE_POP;
	}

	void render() {
		for (auto &entity : mRenderableEntities) {
			entity->render();
		}
	}

	Camera& getCamera() {
		return *camera;
	}

	void setCamera(Camera* camera) {
		this->camera = camera;
	}

private:
	static World* world;
	std::vector<Entity*> mWorldEntities;
	std::vector<Renderable*> mRenderableEntities;
	Camera* camera;
	PhysicsEngine* mPhysicsEngine;
	ModelManager mManager;
};

#endif