/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "Logger.h"

/*
Do not include this class, it is only here for this purpose to initialize the logStreams
*/

std::unordered_map<std::string, std::ostringstream*> Logger::logStreams;