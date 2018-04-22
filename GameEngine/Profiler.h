/**
File: Profiler
Purpose: This class profiles the game engine, can be used to keep track of every function and how they perform

Check https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process for more information

@author Ben Brenkman
@version 1.0

Copyright (c) 2018 All Rights Reserved
*/

#ifndef PROFILER_H
#define PROFILER_H

#include <unordered_map>
#include <stack>
#include "windows.h"

#define PROFILE_PUSH(name) \
Profiler::push_back(name)

#define PROFILE_POP \
Profiler::pop()

// This is a static class
class Profiler {
public:
	class Profile {
	private:
		std::string name;
		double start_time;
		double end_time;
		double start_percent_cpu_usage;
		double end_percent_cpu_usage;
		double start_percent_memory_usage;
		double end_percent_memory_usage;
	public:
		Profile(std::string name, double startTime, double startCPU, double startMemory) : name(name) {
			start_time = startTime;
			start_percent_cpu_usage = startCPU;
			start_percent_memory_usage = startMemory;
		}

		std::string getName() {
			return name;
		}

		double getStartTime() {
			return start_time;
		}
		double getEndTime() {
			return end_time;
		}
		double getCPUStartUsage() {
			return start_percent_cpu_usage;
		}
		double getCPUEendUsage() {
			return end_percent_cpu_usage;
		}
		double getStartMemUsage() {
			return start_percent_memory_usage;
		}
		double getEndUsage() {
			return end_percent_memory_usage;
		}

		double profileDuration() {
			return end_time - start_time;
		}

		void setEndTime(double time) {
			end_time = time;
		}
		void setEndCPU(double usage) {
			end_percent_cpu_usage = usage;
		}

		Profile() {

		}
		~Profile() {

		}
	}; // None static class
private:
	static std::unordered_map<std::string, Profile> profiles;
	static std::stack<std::string> profileStack;
	static std::vector<Profile> logStack;

	static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
	static int numProcessors;
	static double lastPercent;
	static HANDLE self;

	static double getCPULoadPercent();
	static Profile endProfile(std::string name);
	static void addToLog(Profile prof);

public:

	Profiler() {

	}

	// Initializes the CPU information
	static void init();

	static void push_back(std::string name);

	static void popName(std::string name);

	static void pop();

	static void dump();
};

#endif PROFILER_H