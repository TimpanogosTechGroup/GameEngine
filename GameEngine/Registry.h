/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef REGISTRY_H
#define REGISTRY_H

#include "RenderEngine.h"
#include "RegistryEntry.h"
#include <unordered_map>

class Registry
{
public:
	Registry();
	~Registry();

	static inline RenderEngine* GetRenderEngine() { return renderEngine; };
	static void SetRenderEngine(RenderEngine* engine) { 
		renderEngine = engine; 
	};

	// Registers an object by storing the pointer to the object and storing it in a hash map with a string as the key
	static void Register(std::string name, RegistryEntry* objectPointer);

	// Gets a restiry entry and attempts to cast it to the template T
	template <typename T>
	static T* GetRegistryEntry(const char* name);

private:
	static RenderEngine* renderEngine;
	static std::unordered_map<std::string, RegistryEntry*> registry;
};

// Gets a restiry entry and attempts to cast it to the template T
template <typename T>
inline T* Registry::GetRegistryEntry(const char* name) {
	return static_cast<T*>(registry[name]);
}

#endif