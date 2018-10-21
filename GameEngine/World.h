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
#include "CubeMap.h"
#include "Chunk.h"
#include "PerlinGenerator.h"


class World {
public:
	World() : mWorldEntities(), mRenderableEntities() {}

	void addEntityToWorld(Entity* e) {
		if (DynamicEntity* entityptr = dynamic_cast<DynamicEntity*>(e)) {
            Logger::Log<World>(Logger::LoggerLevel::DEBUG, "Dynamic Entity Added to world");
			mPhysicsEngine->addModelInstance(&e->getPhysicalInstance(), 1.0);
			mManager.push_back_instance(&e->getPhysicalInstance());
		}
		else if (StaticEntity* entityptr = dynamic_cast<StaticEntity*>(e)) {
            Logger::Log<World>(Logger::LoggerLevel::DEBUG, "StaticBody entity added to the world.");
		}

		if (Renderable* entityptr = dynamic_cast<Renderable*>(e)) {
			mRenderableEntities.push_back(dynamic_cast<Renderable*>(e));
		}

		mWorldEntities.push_back(e); // Adds it to the world list of entities to update and render and pass events and such
	}

	void initialize() {
		mPhysicsEngine = new PhysicsEngine();

        PerlinGenerator perlinGenerator;
        chunk = new Chunk(0, 0);
        chunk1 = new Chunk(1, 0);
        chunk2 = new Chunk(1, 1);
		chunk->populate(perlinGenerator);
		chunk1->populate(perlinGenerator);
		chunk2->populate(perlinGenerator);

        cube1 = new Cube();

		Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->compileChunk(chunk);
		Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->compileChunk(chunk1);
		Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->compileChunk(chunk2);
		Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->compileCube(cube1);
	}

	void shutdown() {
		for (int i = 0; i < mWorldEntities.size(); i++) {
			Entity* m = mWorldEntities.at(i);
			delete m;
		}

		delete mPhysicsEngine;
	}

	void update() {
//		PROFILE_PUSH("physics update");
		mPhysicsEngine->Update(2, mManager);
//		PROFILE_POP;

//		PROFILE_PUSH("entity update");
		for (auto &entity : mWorldEntities) {
			entity->update();
		}
//		PROFILE_POP;
	}

	void render() {
		if (cube) // If there is a set cubemap render it
			Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->RenderCubeMap(*activeCamera, *cube);

		for (auto &entity : mRenderableEntities) {
			entity->render(activeCamera);
		}

        Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->renderChunk(activeCamera, chunk);
        Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->renderCube(activeCamera, cube1);
//        Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->renderChunk(activeCamera, chunk1);
//        Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->renderChunk(activeCamera, chunk2);

        Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->RenderObject(*activeCamera, *ResourceManager::getModel(FileSystemManager::getModelPathString("Caltrop"))->GetObject(0));
	}

	void setActiveCamera(Camera* camera) {
		this->activeCamera = camera;
	}

	Camera* getActiveCamera() {
		return activeCamera;
	}

	void setCubeMap(CubeMap* cubemap) {
		if (cubemap) {
			this->cube = cubemap;
			return;
		}

		Logger::Log<World>(Logger::LoggerLevel::SEVERE, "The added cube map was a nullptr");
	}

private:
	std::vector<Entity*> mWorldEntities;
	std::vector<Renderable*> mRenderableEntities;
	Camera* activeCamera;
	PhysicsEngine* mPhysicsEngine;
	ModelManager mManager;
	CubeMap* cube;
	Chunk* chunk;
	Chunk* chunk1;
	Chunk* chunk2;
	Cube* cube1;
};

#endif