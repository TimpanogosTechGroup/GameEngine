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