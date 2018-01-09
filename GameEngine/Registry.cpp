/*
Author: Ben Brenkman

Notes: This is a Registry clas, it is static therefore accsesible everywhere. You can use this class to register objects you want globaly available. Then you can call it from anywhere without the need to pass the object around
*/

#include "Registry.h"

// Initialize the variables
RenderEngine* Registry::renderEngine = nullptr;
std::unordered_map<std::string, int*> Registry::registry;

Registry::Registry()
{
	
}

// Registers an object by storing the pointer to the object and storing it in a hash map with a string as the key
void Registry::registerClass(std::string name, int* objectPointer) {

}

template <class T>
int* Registry::getRegisteredClass(std::string name) {
	auto object = registry.find(name);
	if (object != registry.end()) {
		return static_cast<T>(object);
	}
	else {
		return nullptr;
	}
}

Registry::~Registry()
{
}
