#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

class MemoryManager {
public:
	// used for any memory allocations
	virtual void setup() {};
	// used to clean up the memory allocations done
	// Helps keep a better handle on the memory management
	virtual void clean() {};
};

#endif