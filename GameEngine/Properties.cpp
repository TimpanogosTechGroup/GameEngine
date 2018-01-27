#include <iostream>
#include <string>
#include <fstream>
#include "Properties.h"

std::unordered_map<std::string, std::string> Properties::properties;

bool Properties::Init() {
	properties["renderMode"] = "fill";
	properties["gravity"] = "9.81";

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

std::string Properties::Get(std::string key, std::string value) {
	auto var = properties.find(key);
	if (var != properties.end())
		return var->second;

	return "ERROR::KEY NOT FOUND";
}

/*
ALL PROPERTIES THAT WE CHECK ARE LISTED HERE (PLEASE KEEP UPDATED):

renderMode = fill, wireframe, lines


*/