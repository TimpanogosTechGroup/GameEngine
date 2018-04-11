#pragma once
#include <string>
#include <sstream>
using std::ostream;
using std::stringstream;
using std::string;

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
	string summary;
public:
	string example;
	ErrorCode(char type, int code, string summary, string example) : type(type), code(code), summary(summary), example(example){};
	~ErrorCode() {};
	string toString() const {};
	friend ostream& operator<<(ostream& os, const ErrorCode& e)
	{
		os << e->toString();
		return os;
	}
};