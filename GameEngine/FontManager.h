/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H
#include <ft2build.h>
#include FT_FREETYPE_H
#include <unordered_map>
#include <string>
#include "Font.h"
#include "Registry.h"
#include "FontManagerException.h"
#include "MemoryManager.h"

// Define the basic fonts and such
#define ARIAL "fonts\\arial.ttf"

class FontManager : public RegistryEntry
{
private:
	FT_Library fontLibrary;
	std::unordered_map<std::string, Font*> fonts;
public:
	FontManager();
	~FontManager();
	void loadFont(std::string fontName);
	Font& getFont(std::string fontname);

	void clean();
	void setup();
};

#endif