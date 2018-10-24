/**
	File:
    Purpose: 

    @author Jon Meilstrup
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef EXCEPTION_TEMPLATE_H
#define EXCEPTION_TEMPLATE_H
#include <string>
#include "ErrorCode.h"

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
	ExceptionTemplate() : errorCode('A', 120, "Example", "Example") {};
	~ExceptionTemplate(void){};
	std::string errorMessage;
	ErrorCode errorCode;
};

#endif