#pragma once
#include <string>
#include "ErrorCode.cpp"
using std::string;

class ExceptionTemplate
{
public:
	ExceptionTemplate(void) {}
	~ExceptionTemplate(void) {}
	static const string errorMessage;
	static const ErrorCode errorCode;
};