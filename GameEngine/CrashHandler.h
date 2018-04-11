#pragma once
#include "ExceptionTemplate.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

/*
 * Author: Jon Meilstrup
 *
 * Includes class declaration for CrashHandler class.
 *
 * This is used to keep track of any errors thrown in our code. It contains an ExceptionTemplate* (which all exceptions
 * will conform to via polymorphism).
 *
 * string displayErrorMsg()
 *		-See CrashHandler.cpp for a description of this function.
 *
 * void setError(ExceptionTemplate*& e)
 *		-Simple setter. If you really need to understand what this does, see CrashHandler.cpp
 */

class CrashHandler
{
private:
	ExceptionTemplate* e;
public:
	CrashHandler(ExceptionTemplate*& e) : e(e){}
	~CrashHandler() {}
	string displayErrorMsg() {};
	void setError(ExceptionTemplate*& e) {};
};