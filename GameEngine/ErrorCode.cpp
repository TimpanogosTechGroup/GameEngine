#include "ErrorCode.h"

string ErrorCode::toString() const
{
	stringstream os;
	os << type << code << ": " << summary;
	string result;
	os >> result;
	return result;
}