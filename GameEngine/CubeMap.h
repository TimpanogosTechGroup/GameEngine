#pragma once
#include "Model.h"
class CubeMap :
	public Model
{
private:
	Texture* texture;
	std::vector<std::string> textureLoc;

public:
	CubeMap(const char* textureName);
	~CubeMap();

	void SetTexture(Texture* texture) { this->texture = texture; };
	Texture* getTexture() { return texture; };

	std::vector<std::string> &getTextureLocations() { return textureLoc; };
};

