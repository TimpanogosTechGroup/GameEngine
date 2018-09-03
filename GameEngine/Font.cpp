/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "Font.h"
#include "Registry.h"
#include "OpenGlRenderer.h"


Font::Font()
{
}

void Font::init() {
	Registry::GetRegistryEntry<OpenGlRenderer>("renderer")->initFontBuffer(*this);
}

void Font::addCharacter(const char glyph, Character character)
{
	Characters[glyph] = character;
}

Font::Character & Font::getCharacter(const char glyph)
{
	return Characters[glyph];
}

void Font::clean() {
	FT_Done_Face(face);
}

Font::~Font()
{
}
