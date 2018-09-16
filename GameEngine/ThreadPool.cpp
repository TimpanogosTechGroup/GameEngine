#include "ThreadPool.h"
#include <stdexcept>

ThreadPool::ThreadPool() {

}

ThreadPool::~ThreadPool() {

}

bool ThreadPool::joinThreadsToMain() {
	try {
		for (int i = 0; i < this->threads.size(); i++)
			this->threads[i].join();
	}
	catch (std::exception e) {
		return false;
	}
	return true;
}