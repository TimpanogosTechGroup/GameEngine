/**
File: Profiler.cpp
Purpose: This is the cpp file to the Profiler class. This class is used to profile the game engine and report on key metircs taken

@author Ben Brenkman
@version 1.0

Copyright (c) 2018 All Rights Reserved
*/

#include "Profiler.h"
#include <iomanip>
#include <string>
#include <SDL/SDL.h>
#include <time.h>
#include <sstream>
#include <iostream>
#include <fstream>

// This keeps track of all the profiles
std::unordered_map<std::string, Profiler::Profile> Profiler::profiles;
std::stack<std::string> Profiler::profileStack;
std::vector<Profiler::Profile> Profiler::logStack;

ULARGE_INTEGER Profiler::lastCPU, Profiler::lastSysCPU, Profiler::lastUserCPU;
int Profiler::numProcessors;
double Profiler::lastPercent;
HANDLE Profiler::self;

double Profiler::getCPULoadPercent() {
	FILETIME ftime, fsys, fuser;
	ULARGE_INTEGER now, sys, user;
	double percent;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&now, &ftime, sizeof(FILETIME));

	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&sys, &fsys, sizeof(FILETIME));
	memcpy(&user, &fuser, sizeof(FILETIME));
	percent = (sys.QuadPart - lastSysCPU.QuadPart) +
		(user.QuadPart - lastUserCPU.QuadPart);
	percent /= (now.QuadPart - lastCPU.QuadPart);
	percent /= numProcessors;

	if (std::isnan(percent) || percent == 0)
		return lastPercent * 100;

	lastCPU = now;
	lastUserCPU = user;
	lastSysCPU = sys;
	lastPercent = percent;

	return percent * 100;
}

Profiler::Profile Profiler::endProfile(std::string name) {
	if (profiles.find(name) != profiles.end()) {
		Profile prof = profiles[name];
		prof.setEndTime(SDL_GetTicks());
		prof.setEndCPU(getCPULoadPercent());
		return prof;
	}
	return Profile();
}

// Initializes the CPU information
void Profiler::init() {
	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;

	GetSystemInfo(&sysInfo);
	numProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));

	self = GetCurrentProcess();
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
}

void Profiler::push_back(std::string name) {
	if (profiles.find(name) != profiles.end()) {
		//stop currently named profile
		//logStack.push_back(endProfile(name));
		popName(name);
	}

	profiles[name] = Profile(name, SDL_GetTicks(), getCPULoadPercent(), 0);
	profileStack.push(name);

}

void Profiler::popName(std::string name) {
	if (profiles.find(name) == profiles.end()) {
		while (!profileStack.empty() && profileStack.top() != name) {
			//logStack.push_back(endProfile(name));
			addToLog(endProfile(name));
			profileStack.pop();
		}
		profileStack.pop();
	}
}

void Profiler::pop() {
	if (!profileStack.empty()) {
		//logStack.push_back(endProfile(profileStack.top()));
		addToLog(endProfile(profileStack.top()));
		profileStack.pop();
	}
}

void Profiler::addToLog(Profiler::Profile prof) { // Get this to work
	//for (int i = logStack.size() - 1; i > 0; i--) {
	//	if (logStack.at(i).getName() == prof.getName()) {
	//		if (logStack.at(i).getCPUStartUsage() != prof.getCPUStartUsage() &&
	//			logStack.at(i).getCPUEendUsage() != prof.getCPUEendUsage() &&
	//			//logStack.at(i).getStartMemUsage() != prof.getEndUsage() &&
	//			logStack.at(i).profileDuration() != prof.profileDuration()) {
	//			logStack.push_back(prof);
	//			return;
	//		}
	//	}
	//}

#ifdef PROFILER_LOG
	logStack.push_back(prof);
#endif
}

void Profiler::dump() {
	// Gets the current time, the time that the function was called.
	time_t timev = time(0);
	struct tm timec;
	localtime_s(&timec, &timev);

	// Format the time
	std::ostringstream timeStamp("log//");
	// year-month-day
	timeStamp << timec.tm_year + 1900 << "-" << timec.tm_mon + 1 << "-" << timec.tm_mday;
	// hour:minute:second
	timeStamp << " " << std::right << std::setw(2) << std::setfill('0') << timec.tm_hour << ":" << std::right << std::setw(2) << std::setfill('0') << timec.tm_min << ":" << std::right << std::setw(2) << std::setfill('0') << timec.tm_sec;

	std::ofstream out("log//text.txt");
	std::cout << timeStamp.str() << std::endl;

	out << "Name:," << "start_time," << "end_time," << "average," << "start_percent_cpu_usage," << "end_percent_cpu_usage," << "start_percent_memory_usage," << "end_percent_memory_usage" << std::endl;

	if (!logStack.empty()) {

		for (auto &row : logStack) {
			// Skips the entires that are the same, the time will keep track of the similarities.
			// Modify this so that we check if each type of profile is the same not every profile
				// Write the row to the output file
				out << row.getName() << "," << row.getStartTime() << "," << row.getEndTime() << "," << row.profileDuration() << "," << row.getCPUStartUsage() << "," << row.getCPUEendUsage() << "," << row.getStartMemUsage() << "," << row.getEndUsage() << std::endl;
				
		}
	}

	out.close();
}