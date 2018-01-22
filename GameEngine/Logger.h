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
	static LoggerLevel level;
	static std::unordered_map<std::string, std::ostringstream*> logStreams;
};

#endif LOGGER_H

template <class T>
inline void Logger::Log(LoggerLevel level, const char* printLine)
{
	time_t timev = time(0);
	struct tm * timec = localtime(&timev);
	std::ostringstream date;
	// year-month-day
	date << timec->tm_year + 1900 << "-" << timec->tm_mon + 1 << "-" << timec->tm_mday;
	// hour:minute:second
	date << " " << std::right << std::setw(2) << std::setfill('0') <<  timec->tm_hour << ":" << std::right << std::setw(2) << std::setfill('0') << timec->tm_min << ":" << std::right << std::setw(2) << std::setfill('0') << timec->tm_sec;

	switch (level)
	{
	case INFO:
		std::cout << date.str() << " [" << typeid(T).name() << "] INFO: " << printLine << std::endl;
		break;
	case ERROR:
		std::cout << date.str() << " [" << typeid(T).name() << "] ERROR: " << printLine << std::endl;
		break;
	case SEVERE:
		std::cout << date.str() << " [" << typeid(T).name() << "] SEVERE: " << printLine << std::endl;
		break;
	case EXPCEPTION:
		std::cout << date.str() << " [" << typeid(T).name() << "] EXCEPTION: " << printLine << std::endl;
		break;
	case LOG:
		std::cout << date.str() << " [" << typeid(T).name() << "] LOG: " << printLine << std::endl;
		break;
	case DEBUG:
		std::cout << date.str() << " [" << typeid(T).name() << "] DEBUG: " << printLine << std::endl;
		break;
	case RELEASE:
		std::cout << date.str() << " [" << typeid(T).name() << "] RELEASE: " << printLine << std::endl;
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