/*
Isaac Draper:

Shader class to be implemented by Ben

Most of this class is not used right now, primarily just the texture right now.
*/

#pragma once

#include "Texture.h"
#include "Shader.h"
#include <glm\glm.hpp>

class Material {
public:
	Material() {
		this->diffuse = 0;
		this->specular = 0;
		this->texture = NULL;
		this->color = glm::vec3(1, 1, 1);
	};
	Material(float diff, float spec, Texture tex, Shader* sh) {
		this->diffuse = diff;
		this->specular = spec;
		this->texture = tex;
		this->shader = sh;
		this->color = glm::vec3(1, 1, 1);
	};
	Material(float diff, float spec, Texture tex, Shader* sh, glm::vec3 col) {
		this->diffuse = diff;
		this->specular = spec;
		this->texture = tex;
		this->shader = sh;
		this->color = col;
	};

	float GetDiffuse() { return this->diffuse; };
	float GetSpecular() { return this->specular; };
	Shader* GetShader() { return shader; };
	void SetDiffuse(int diff) { this->diffuse = diff; };
	void SetSpecular(int spec) { this->specular = spec; };
	void SetTexture(Texture tex) { this->texture = tex; };
	void SetShader(Shader* sh) { this->shader = sh; };
	void SetColor(glm::vec3 col) { this->color = col; };

private:
	float diffuse;
	float specular;
	Texture texture;
	Shader* shader;
	glm::vec3 color; // Color of the material
};