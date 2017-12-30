/*
Author: Ben Brenkman

Notes: This is a Registry clas, it is static therefore accsesible everywhere. You can use this class to register objects you want globaly available. Then you can call it from anywhere without the need to pass the object around
*/

#include "Registry.h"

// Initialize the variables
RenderEngine* Registry::renderEngine = nullptr;

Registry::Registry()
{
	
}


Registry::~Registry()
{
}
