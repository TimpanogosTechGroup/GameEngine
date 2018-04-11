#include "CrashHandler.h"

/*
 * Author: Jon Meilstrup
 *
 * Includes function definitions for CrashHandler class:
 *	-string displayErrorMsg()
 */

string CrashHandler::displayErrorMsg()
{
	/*
	 * Logs error message for whatever error was thrown.
	 * Logs in the form:
	 *		A101: Example error -:- Example error thrown on line n.
	 *
	 *		This is an example error. You will never actually get an A101.
	 */
	cout << e->errorCode << " -:- " << e->errorMessage << endl << endl;
	cout << e->errorCode->example << endl;
}

void CrashHandler::setError(ExceptionTemplate*& e)
{
	// This is really simple. Just sets the CrashHandler's current exception to the one thrown.
	this->e = e;
}