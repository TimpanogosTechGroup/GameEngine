#include "ErrorCode.h"

/*
 * Author: Jon Meilstrup
 *
 * Includes the function definitions for the ErrorCode class:
 *	-string toString() const
 */

string ErrorCode::toString() const
{
	/*
	 * Displays the error code in the form "A101: Example error". Uses a stringstream to make it easier to insert
	 * error code data, then convert to a string.
	 */
	stringstream os;
	os << type << code << ": " << summary;
	string result;
	os >> result;
	return result;
}