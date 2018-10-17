/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef GARBAGE_COLLECTOR_H
#define GARBAGE_COLLECTOR_H

#include <vector>

class GarbageCollector {
private:
	std::vector<void *> memoryBlock;
	
public:
	void addMemoryToGarbageCollector(void * ptr) {
		memoryBlock.push_back(ptr);
	}

	void collectGarbage() {
//		for (auto v : memoryBlock) {
//			delete v;
//		}
//		memoryBlock.clear();
	}
};

#endif