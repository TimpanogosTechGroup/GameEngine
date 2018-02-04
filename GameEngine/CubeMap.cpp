#include "CubeMap.h"



CubeMap::CubeMap(const char* textureName)
{
	std::vector<float> skyboxVertices = 
	{
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	Object* box = new Object();

	for (auto &fl : skyboxVertices) {
		box->GetVerticies().AddFloat(fl);
	}

	this->AddObject(box);

	std::string textr(textureName);
	textr.append("_right.tga");
	std::string textl(textureName);
	textl.append("_left.tga");
	std::string textt(textureName);
	textt.append("_up.tga");
	std::string textb(textureName);
	textb.append("_down.tga");
	std::string textba(textureName);
	textba.append("_back.tga");
	std::string textf(textureName);
	textf.append("_front.tga");


	textureLoc.push_back(textr);
	textureLoc.push_back(textl);
	textureLoc.push_back(textt);
	textureLoc.push_back(textb);
	textureLoc.push_back(textba);
	textureLoc.push_back(textf);
}


CubeMap::~CubeMap()
{
}
