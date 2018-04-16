#include "Profiler.h"
#include <iomanip>
#include <string>
#include <SDL\SDL.h>
#include <time.h>
#include <sstream>
#include <iostream>
#include <fstream>

std::unordered_map<std::string, Profiler::Profile> Profiler::profiles;
std::stack<std::string> Profiler::profileStack;
std::vector<Profiler::Profile> Profiler::logStack;

ULARGE_INTEGER Profiler::lastCPU, Profiler::lastSysCPU, Profiler::lastUserCPU;
int Profiler::numProcessors;
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
	lastCPU = now;
	lastUserCPU = user;
	lastSysCPU = sys;

	return percent * 100;
}

Profiler::Profile Profiler::endProfile(std::string name) {
	if (profiles.find(name) != profiles.end()) {
		Profile prof = profiles[name];
		prof.setEndTime(SDL_GetTicks());
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
			logStack.push_back(endProfile(name));
			profileStack.pop();
		}
		profileStack.pop();
	}
}

void Profiler::pop() {
	if (!profileStack.empty()) {
		logStack.push_back(endProfile(profileStack.top()));
		profileStack.pop();
	}
}

void Profiler::dump() {
	// Gets the current time, the time that the function was called.
	time_t timev = time(0);
	struct tm timec;
	localtime_s(&timec, &timev);

	// Format the time
	std::ostringstream timeStamp("log\\");
	// year-month-day
	timeStamp << timec.tm_year + 1900 << "-" << timec.tm_mon + 1 << "-" << timec.tm_mday;
	// hour:minute:second
	timeStamp << " " << std::right << std::setw(2) << std::setfill('0') << timec.tm_hour << ":" << std::right << std::setw(2) << std::setfill('0') << timec.tm_min << ":" << std::right << std::setw(2) << std::setfill('0') << timec.tm_sec;

	std::ofstream out("log\\text.txt");
	std::cout << timeStamp.str() << std::endl;

	out << "Name:," << "start_time," << "end_time," << "average," << "start_percent_cpu_usage," << "end_percent_cpu_usage," << "start_percent_memory_usage," << "end_percent_memory_usage" << std::endl;

	for (auto &row : logStack) {
		out << row.getName() << "," << row.getStartTime() << "," << row.getEndTime() << "," << row.profileDuration() << "," << row.getCPUStartUsage() << "," << row.getCPUEendUsage() << "," << row.getStartMemUsage() << "," << row.getEndUsage() << std::endl;
	}

	out.close();
}