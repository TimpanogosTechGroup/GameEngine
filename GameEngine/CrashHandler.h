#pragma once
#include "ExceptionTemplate.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class CrashHandler
{
private:
	ExceptionTemplate* e;
public:
	CrashHandler(ExceptionTemplate* e) : e(e){}
	~CrashHandler() {}
	string displayErrorMsg() {};
};