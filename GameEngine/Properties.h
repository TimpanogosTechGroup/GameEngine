#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <unordered_map>
#include <fstream>

class Properties {
public:
	static bool Init();
	static bool Set(std::string key, std::string value);
	template <typename T>
	static T Get(std::string key);
private:
	static std::unordered_map<std::string, std::string> properties;
};

template <typename T>
inline T Properties::Get(std::string key) {

	auto var = properties.find(key);
	if (var != properties.end()) {
		std::string val = var->second;
		std::stringstream stream(val);
		T rtnVal;
		stream >> rtnVal;
		return rtnVal;
	}

	return NULL;
}

#endif PROPERTIES_H