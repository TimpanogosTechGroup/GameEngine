/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/

/*
	@Author: Ben Brenkman

	Notes: This is a Registry clas, it is static therefore accsesible everywhere. You can use this class to register objects you want globaly available. Then you can call it from anywhere without the need to pass the object around
*/

#include "Registry.h"
#include <string>

// Initialize the variables
RenderEngine* Registry::renderEngine = nullptr;
std::unordered_map<std::string, RegistryEntry*> Registry::registry;

Registry::Registry() {}

// Registers an object by storing the pointer to the object and storing it in a hash map with a string as the key
void Registry::Register(std::string name, RegistryEntry* objectPointer) {
	if (registry.find(name) != registry.end()) {
		Logger::Log<Registry>(LoggerLevel::SEVERE, "The entry already exists, if you have replaced the entry there might be unexpected code behaviors in the code.");
	}
	else {
		std::string message("Registered class: ");
		message.append(typeid(objectPointer).name());
		message.append(" as ");
		message.append(name);

		Logger::Log<Registry>(LoggerLevel::INFO, message.c_str());
	}

	registry[name] = objectPointer;
}

Registry::~Registry()
{
}
