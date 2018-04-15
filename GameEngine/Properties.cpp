/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include <iostream>
#include <string>
#include <fstream>
#include "Properties.h"

std::unordered_map<std::string, std::string> Properties::properties;

bool Properties::Init() {
	// RENDERER
	properties["renderMode"]			= "fill";
	properties["glLineWidth"]			= "0.5";
	
	// CAMERA/MOUSE
	properties["cameraYaw"]				= "-90.0";
	properties["cameraPitch"]			= "0.0";
	properties["cameraSpeed"]			= "2.5";
	properties["cameraSensitivity"]		= "0.1";
	properties["cameraZoom"]			= "45.0";
	properties["cameraFOV"]				= "45.0";

	// PHYSICS
	properties["gravity"] = "-9.81";

	std::fstream file("properties.txt");
	std::string line, key, val;
	while (std::getline(file, line)) {
		key = line.substr(0, line.find(" "));
		val = line.substr(line.find(" ") + 1);

		properties[key] = val;
	}

	return true;
}

bool Properties::Set(std::string key, std::string value) {
	properties[key] = value;
	return true;
}

/*
ALL PROPERTIES THAT WE CHECK ARE LISTED HERE (MUST KEEP UPDATED):

KEY						OPTIONS
renderMode			= fill, wireframe, lines
gravity				= DOUBLE
glLineWidth			= DOUBLE
cameraYaw			= FLOAT
cameraPitch			= FLOAT
cameraSpeed			= FLOAT
cameraSensitivity	= FLOAT
cameraZoom			= FLOAT
cameraFOV			= FLOAT


*/