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
	template <class T>
	static void PrintClassName() {
		std::cout << typeid(T).name() << std::endl;
	};

	// Registers an object by storing the pointer to the object and storing it in a hash map with a string as the key
	void registerClass(std::string name, int* objectPointer);

	template <typename T>
	int* getRegisteredClass(std::string name);

private:
	static RenderEngine* renderEngine;
	static std::unordered_map<std::string, int*> registry;
};