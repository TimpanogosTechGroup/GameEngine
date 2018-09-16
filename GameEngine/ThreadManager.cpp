#include "ThreadManager.h"
#include <stdexcept>

ThreadManager::ThreadManager() {

}

ThreadManager::~ThreadManager() {

}

bool ThreadManager::joinThreadsToMain() {
	try {
		for (int i = 0; i < this->threads.size(); i++)
			this->threads[i].join();
	}
	catch (std::exception e) {
		return false;
	}
	return true;
}