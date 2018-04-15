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

class FileSystemManager {
private:
	std::string pathToHome;
	std::string modelPathLocation = "Model\\";
	std::string materialPathLocation;

	const std::string folderName = "Andromeda";
public:
	std::string getModelPathString(std::string modelName, std::string folderName = "Andromeda") {
		std::string path = modelPathLocation;
		path.append(folderName);
		path.append("\\");
		path.append(modelName);
		path.append(".obj");
		return path;
	}

	std::string getFolderName() const {
		return folderName;
	}

	/*
	* Starts up the File System Manager, used to find all the model and other folders
	*/
	void initialize() {

	}

	/*
	* Returns the file system instance running.
	*/
	static FileSystemManager& getInstance() {
		static FileSystemManager* fileSystem = nullptr;
		if (!fileSystem) {
			fileSystem = new FileSystemManager();
		}
		return *fileSystem;
	}
};

#endif