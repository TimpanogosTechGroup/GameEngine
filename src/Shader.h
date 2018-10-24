/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#pragma once
#include "RenderItem.h"

enum ShaderType {
	SHADER_VERTEX, 
	SHADER_FRAGMENT, 
	SHADER_GEOMETRY
};

class Shader : public RenderItem
{
public:
	Shader();
	~Shader();

	RenderItem vertex;
	RenderItem fragment;
	RenderItem geometry;
};

