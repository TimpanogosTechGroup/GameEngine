#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <thread>
#include <vector>

class ThreadManager {
	public:
		ThreadManager();
		~ThreadManager();

		bool joinThreadsToMain();

		template <typename T>
		bool addToThread(T(*f)) {
			int size = this->threads.size();
			this->threads.push_back(std::thread(*f));
			if (size + 1 == this->threads.size())
				return true;
			else
				return false;
		}
	private:
		std::vector<std::thread> threads;
};

#endif THREAD_MANAGER_H