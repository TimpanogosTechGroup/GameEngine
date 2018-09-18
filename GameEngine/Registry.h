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
#include "Logger.h"
#include "ClassCastMismatchExeption.h"
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
	if (registry.find(name) == registry.end()) {
		Logger::Log<Registry>(LoggerLevel::SEVERE, "Unable to find the name of the entry");
		throw new std::string("No registry entry with that name");
	}

	if (T* entry = static_cast<T*>(registry[name])) {
		return static_cast<T*>(registry[name]);
	}
	else {
		Logger::Log<Registry>(LoggerLevel::SEVERE, "Incorrect class type, class mismatch.");
		throw new ClassCastMismatchException();
	}

}

#endif REGISTRY_H