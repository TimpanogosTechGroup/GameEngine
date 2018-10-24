/**
	File:
    Purpose: 

    @author Jon Meilstrup
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "ErrorCode.h"
/*
 * Author: Jon Meilstrup
 *
 * Includes the function definitions for the ErrorCode class:
 *	-string toString() const
 */

std::string ErrorCode::getErrorCode() const
{
	/*
	 * Displays the error code in the form "A101: Example error". Uses a stringstream to make it easier to insert
	 * error code data, then convert to a string.
	 */
	std::stringstream os;
	os << type << code << ": " << summary;
	std::string result;
	os >> result;
	return result;
};