/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef FONT_H
#define FONT_H
#include <ft2build.h>
#include FT_FREETYPE_H
#include "RenderItem.h"
#include <map>
#include <glm/glm.hpp>
#include <GLEW/glew.h>

class Font : public RenderItem
{
private:
	FT_Face face;
	RenderItem VBO;
public:
	Font();
	~Font();
	struct Character {
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};
	// returns the font face
	FT_Face& getFace() { return face; };
	// initlaizes the font, creates the buffers and stuff
	void init();
	// Gets the VBO renderitem
	RenderItem& getVBO() { return VBO; };
	void addCharacter(const char glyph, Character character);
	Character& getCharacter(const char glyph);
	void clean();
private:
	std::map<const char, Character> Characters;
};

#endif