#pragma once
#include "RenderEngine.h"
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

	// Coolness Right Here! You call this method like this Registry::PrintClassName<Class>(); And out the class in between the <>, the function will print the name of the class.
	// We can use this as part of a logger to find out where the print statement came from
	template <typename T>
	static void PrintClassName() {
		std::istringstream iss(typeid(T).name());
		std::cout << "Yeah" << std::endl;
	};

	// Registers an object by storing the pointer to the object and storing it in a hash map with a string as the key
	static void registerClass(std::string name, void* objectPointer);

	// Gets a restiry entry and attempts to cast it to the template T
	template <typename T>
	static T* GetRegistryEntry(const char* name) {
		return dynamic_cast<T*>(registry[name]);
	}

private:
	static RenderEngine* renderEngine;
	static std::unordered_map<std::string, void*> registry;
};