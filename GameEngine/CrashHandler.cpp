/**
	File:
    Purpose: 

    @author Jon Meilstrup
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "CrashHandler.h"

/*
 * Author: Jon Meilstrup
 *
 * Includes function definitions for CrashHandler class:
 *	-string displayErrorMsg()
 */

std::string CrashHandler::displayErrorMsg()
{
	/*
	 * Logs error message for whatever error was thrown.
	 * Logs in the form:
	 *		A101: Example error -:- Example error thrown on line n.
	 *
	 *		This is an example error. You will never actually get an A101.
	 */
	stringstream os;
	os << e->errorCode; // Because of the way the insertion operator is overridden, you can't insert anything into the stream after it, unless you're on a new line
	os << " -:- " << e->errorMessage << std::endl << std::endl << e->errorCode.example << std::endl;
	std::string result;
	os >> result;
	const char* c = result.c_str();

	Logger::Log<CrashHandler>(ERROR, c);

	return result;
}

void CrashHandler::setError(ExceptionTemplate*& e)
{
	// This is really simple. Just sets the CrashHandler's current exception to the one thrown.
	this->e = e;
}