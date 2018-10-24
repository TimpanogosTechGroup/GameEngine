/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef FONT_MANAGER_EXCEPTION_H
#define FONT_MANAGER_EXCEPTION_H
#include <exception>

class FontManagerException : public std::exception {
private:

public:
	const char* what() const throw () {
		return "Font manager unable to initialize.";
	}
};

#endif