#include "CrashHandler.h"

string CrashHandler::displayErrorMsg()
{
	cout << e->errorCode << " : " << e->errorMessage << endl << endl;
	cout << e->errorCode.example << endl;
}