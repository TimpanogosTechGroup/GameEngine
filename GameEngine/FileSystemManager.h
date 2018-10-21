/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef FILE_SYSTEM_MANAGER_H
#define FILE_SYSTEM_MANAGER_H

#include <string>
#include "MemoryManager.h"

class FileSystemManager {
private:
	static std::string pathToHome;
	static std::string modelPathLocation;
	static std::string materialPathLocation;
	static std::string mainDirPath;

//	static const std::string folderName = "Andromeda";
public:
	static std::string getModelPathString(std::string modelName, std::string folderName = "Andromeda") {
		std::string path = "Model/";
		path.append(folderName);
		path.append("/");
		path.append(modelName);
		path.append(".obj");
		return path;
	}

	static void setMainDirPath(std::string pathname) {
		mainDirPath = pathname;
	}

//	static std::string getFolderName() const {
//		return folderName;
//	}

    static std::string getModelPathString() {
	    return mainDirPath + "Model/";
	}

	static std::string getMainDirPath() {
		return mainDirPath;
	}
};

#endif