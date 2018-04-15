/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef ERROR_CODE_H
#define ERROR_CODE_H

#include <string>
#include <sstream>

/*
 * Author: Jon Meilstrup
 *
 * Includes class declaration for ErrorCode class.
 *
 * This is used to keep identify any errors thrown in our code. It has an alphanumeric code (e.g. A101), a short summary
 * describing the error, and some example text going more in-depth into the error and showing possible ways the error
 * may have happened.
 *
 * string toString() const: Converts the ErrorCode into a string
 *		-e.g. "A101: Example error"
 *
 * friend ostream& operator<<(ostream& os, const ErrorCode& e): Makes it possible to insert the ErrorCode into an ostream.
 *		-e.g. ostream result;
 *		      ExampleException e;
 *		      result << e;
 *			  return result;
 */

class ErrorCode
{
private:
	char type;
	int code;
	std::string summary;
public:
	std::string example;
	ErrorCode(char type, int code, std::string summary, std::string example) : type(type), code(code), summary(summary), example(example){};
	~ErrorCode() {};

	std::string getErrorCode() const;

	friend std::ostream& operator<<(std::ostream& os, const ErrorCode& e)
	{
		os << e.getErrorCode();
		return os;
	}
};

#endif