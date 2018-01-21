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
	static void SetLoggerLevel(LoggerLevel level);
	static LoggerLevel GetLoggerLevel();
	~Logger();

private:
	static LoggerLevel level;
};

#endif LOGGER_H

template <class T>
inline void Logger::Log(T* classObject, LoggerLevel level, const char* printLine)
{
	time_t timev;
	struct tm * timec = localtime(&timev);
	time(&timev);

	switch (level)
	{
	case INFO:
		break;
	case ERROR:
		break;
	case SEVERE:
		break;
	case EXPCEPTION:
		break;
	case LOG:
		break;
	case DEBUG:
		std::cout << timec->tm_year << " [" << typeid(T).name() << "] DEBUG:: " << printLine << std::endl;
		break;
	case RELEASE:
		break;
	default:
		break;
	}
}
