#pragma once
#include <string>
#include "ErrorCode.cpp"
using std::string;

/*
 * Author: Jon Meilstrup
 *
 * Includes class declaration for ExceptionTemplate.
 *
 * This is an interface that should have only virtual functions. This class is what all
 * exception classes inherit from. Contains a string error message and an ErrorCode error code.
 */

class ExceptionTemplate
{
public:
	ExceptionTemplate(void) {}
	~ExceptionTemplate(void) {}
	static const string errorMessage;
	static const ErrorCode* errorCode;
};