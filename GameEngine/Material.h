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
		this->color = glm::vec4(1, 1, 1, 1);
	};
	Material(float diff, float spec, Texture* tex, Shader* sh) {
		this->diffuse = diff;
		this->specular = spec;
		this->texture = tex;
		this->shader = sh;
		this->color = glm::vec4(1, 1, 1, 1);
	};
	Material(float diff, float spec, Texture* tex, Shader* sh, glm::vec4 col = glm::vec4(1, 1, 1, 1)) {
		this->diffuse = diff;
		this->specular = spec;
		this->texture = tex;
		this->shader = sh;
		this->color = col;
	};

	const float GetDiffuse() { return this->diffuse; };
	const float GetSpecular() { return this->specular; };
	Shader* GetShader() { return shader; };
	const glm::vec4 GetColor() { return color; };
	Texture* GetTexture() { return texture; };
	void SetDiffuse(float diff) { this->diffuse = diff; };
	void SetSpecular(float spec) { this->specular = spec; };
	void SetTexture(Texture* tex) { this->texture = tex; };
	void SetShader(Shader* sh) { this->shader = sh; };
	void SetColor(glm::vec3 col) {
		this->color[0] = col[0];
		this->color[1] = col[1];
		this->color[2] = col[2];
		this->color[3] = 1.0f;
	};
	void SetColor(glm::vec4 col) { this->color = col; };

private:
	float diffuse; // These will become reduntant
	float specular; // These will become reduntant

	Texture* texture; // Texture of the object

	// These textures are needed for the PHysically Based Rendinring (PBR)
	Texture* normalMap; // Normal map of the object
	Texture* albedoMap; // Albedo map
	Texture* metallicMap; // Metallic map
	Texture* roughnessMap; // Roughness maps
	Texture* aoMap; // Occlusion map

	Shader* shader; // The pointer to the shader of the object
	glm::vec4 color; // Color of the object
};