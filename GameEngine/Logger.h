#ifndef LOGGER_H
#define LOGGER_H
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
#include <unordered_map>
#include <string>
#include <time.h>

enum LoggerLevel {
	INFO, ERROR, SEVERE, EXPCEPTION, LOG, DEBUG, RELEASE
};

class Logger
{
public:
	Logger() {};
	template <class T>
	static void Log(LoggerLevel level, const char* printLine);
	template <class T>
	static void Log(LoggerLevel level);
	static void SetLoggerLevel(LoggerLevel level) {	};
	const static LoggerLevel GetLoggerLevel() { return level; };
	template <class T>
	static std::ostringstream* GetLogStream();
	~Logger() {};

private:
	static LoggerLevel level; // Level at which to display the logging
	static std::unordered_map<std::string, std::ostringstream*> logStreams; // this holds each stream that is associated with a class
};

template <class T>
inline void Logger::Log(LoggerLevel level, const char* printLine)
{
	// Gets the current time, the time that the function was called.
	time_t timev = time(0);
	struct tm * timec = localtime(&timev);

	// Format the time
	std::ostringstream timeStamp;
	// year-month-day
	timeStamp << timec->tm_year + 1900 << "-" << timec->tm_mon + 1 << "-" << timec->tm_mday;
	// hour:minute:second
	timeStamp << " " << std::right << std::setw(2) << std::setfill('0') <<  timec->tm_hour << ":" << std::right << std::setw(2) << std::setfill('0') << timec->tm_min << ":" << std::right << std::setw(2) << std::setfill('0') << timec->tm_sec;

	// Extract name of class T
	std::istringstream className(typeid(T).name());
	std::string CName;
	className >> CName;
	if (CName == "class")
		className >> CName;

	switch (level)
	{
	case INFO:
		std::cout << timeStamp.str() << " [INFO][" << CName << "] " << printLine << std::endl;
		break;
	case ERROR:
		std::cout << timeStamp.str() << " [ERROR][" << CName << "] " << printLine << std::endl;
		break;
	case SEVERE:
		std::cout << timeStamp.str() << " [SEVERE][" << CName << "] " << printLine << std::endl;
		break;
	case EXPCEPTION:
		std::cout << timeStamp.str() << " [EXCEPTION][" << CName << "] " << printLine << std::endl;
		break;
	case LOG:
		std::cout << timeStamp.str() << " [LOG][" << CName << "] " << printLine << std::endl;
		break;
	case DEBUG:
		std::cout << timeStamp.str() << " [DEBUG][" << CName << "] " << printLine << std::endl;
		break;
	case RELEASE:
		std::cout << timeStamp.str() << " [RELEASE][" << CName << "] " << printLine << std::endl;
		break;
	default:
		break;
	}
}

template <class T>
inline void Logger::Log(LoggerLevel level = LoggerLevel::DEBUG)
{
	// Log and print out
	Log<T>(level, GetLogStream<T>()->str().c_str());
	// Clear the string stream so it doesnt pile up
	GetLogStream<T>()->str("");
}

template <class T>
std::ostringstream* Logger::GetLogStream() {
	auto stream = logStreams.find(typeid(T).name());
	if (stream == logStreams.end()) {
		std::ostringstream* sstream = new std::ostringstream;
		logStreams[typeid(T).name()] = sstream;
		return sstream;
	}
	else {
		return stream->second;
	}
}

#endif LOGGER_H