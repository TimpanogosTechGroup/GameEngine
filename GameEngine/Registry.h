#pragma once
#include "RenderEngine.h"

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
		std::cout << typeid(T).name() << std::endl;
	};

private:
	static RenderEngine* renderEngine;
};