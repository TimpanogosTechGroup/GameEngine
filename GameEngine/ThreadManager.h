#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <thread>
#include <vector>

class ThreadManager {
	public:
		ThreadManager();
		~ThreadManager();

		template <typename T>
		bool addToThread(T(*f)) {
			std::thread thr(f);
			/*
			if (this->threads.push_back(std::thread f))
				return true;
			else
			*/
				return false;
		}
	private:
		std::vector<std::thread> threads;
};

#endif THREAD_MANAGER_H