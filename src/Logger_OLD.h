#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <ctime>

enum LoggerLevel {
	INFO, ERROR, SEVERE, EXPCEPTION, LOG, DEBUG, RELEASE
};

class Logger
{
public:
	Logger();
	template <class T>
	static void Log(T* classObject, LoggerLevel level, const char* printLine);
	static void SetLoggerLevel(LoggerLevel level) {

	};
	const static LoggerLevel GetLoggerLevel() { return level; };
	~Logger();

private:
	static LoggerLevel level;
};

#endif LOGGER_H

template <class T>
inline void Logger::Log(T* classObject, LoggerLevel level, const char* printLine)
{
	time_t timev = time(0);
	struct tm * timec = localtime(&timev);
	ostringstream date;
	// year-month-day
	date << timec->tm_year + 1900 << "-" << timec->tm_mon + 1 << "-" << timec->tm_mday;
	// hour:minute:second
	date << " " << timec->tm_hour << ":" << timec->tm_min << ":" << timec->tm_sec;

	switch (level)
	{
	case INFO:
		std::cout << date.str() << " [" << typeid(T).name() << "] INFO: " << printLine << std::endl;
		break;
	case ERROR:
		std::cerr << date.str() << " [" << typeid(T).name() << "] ERROR: " << printLine << std::endl;
		break;
	case SEVERE:
		std::cerr << date.str() << " [" << typeid(T).name() << "] SEVERE: " << printLine << std::endl;
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
