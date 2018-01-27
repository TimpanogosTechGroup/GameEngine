#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <unordered_map>

class Properties {
public:
	static bool Init();
	static bool Set(std::string key, std::string value);
	static std::string Get(std::string key, std::string value);
private:
	static std::unordered_map<std::string, std::string> properties;
};

#endif PROPERTIES_H