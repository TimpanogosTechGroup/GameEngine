/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef CRASH_HANDLER_H
#define CRASH_HANDLER_H

#include <string>
#include <iostream>

#include "ExceptionTemplate.h"

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
	std::string displayErrorMsg();
	void setError(ExceptionTemplate*& e);
};

#endif