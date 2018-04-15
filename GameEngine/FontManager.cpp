/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#include "FontManager.h"
#include "Logger.h"
#include "FontManagerException.h"


FontManager::FontManager()
{
	if (FT_Init_FreeType(&fontLibrary))
		throw new FontManagerException();
}


FontManager::~FontManager()
{
	FT_Done_FreeType(fontLibrary);
	for (auto font : fonts) {
		font.second->clean();
		delete font.second;
	}
}

void FontManager::loadFont(std::string fontName)
{
	//Logger::Log<FontManager>(DEBUG, "Initializing...");
	Font* font = new Font();
	if (FT_New_Face(fontLibrary, fontName.c_str(), 0, &font->getFace()))
		throw new FontManagerException();
	FT_Set_Pixel_Sizes(font->getFace(), 0, 48);
	font->init();
	fonts[fontName] = font;
}

Font & FontManager::getFont(std::string fontname)
{
	return *fonts[fontname];
}
