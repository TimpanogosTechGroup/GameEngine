/*
Isaac Draper:

Shader class to be implemented by Ben

Most of this class is not used right now, primarily just the texture right now.
*/

#pragma once

#include "Texture.h"
#include "Shader.h"

class Material {
public:
	Material() {
		this->diffuse = 0;
		this->specular = 0;
	}
	Material(int diff, int spec, Texture tex, Shader sh) {
		this->diffuse = diff;
		this->specular = spec;
		this->texture = tex;
		this->shader = sh;
	}
	int GetDiffuse() { return this->diffuse; }
	int GetSpecular() { return this->specular; }
	void SetDiffuse(int diff) { this->diffuse = diff; }
	void SetSpecular(int spec) { this->specular = spec; }
	void SetTexture(Texture tex) { this->texture = tex; }
	void SetShader(Shader sh) { this->shader = sh; }

private:
	int diffuse;
	int specular;
	Texture texture;
	Shader shader;
};