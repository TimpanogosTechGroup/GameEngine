/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#pragma once

// All things that are managed by opengl have an ID, so this class keeps that nicely handled.
class RenderItem {
public:
	unsigned int &GetID() { return id; };
	void SetId(unsigned int ID) { id = ID; };

protected:
	unsigned int id = 0;
};