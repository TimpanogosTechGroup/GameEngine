#pragma once
#include <string>
#include <sstream>
using std::ostream;
using std::stringstream;
using std::string;

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