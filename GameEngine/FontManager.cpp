#include "FontManager.h"

#include "FontManagerException.h"


FontManager::FontManager()
{
	if (FT_Init_FreeType(&fontLibrary))
		throw new FontManagerException();
}


FontManager::~FontManager()
{
	FT_Done_FreeType(fontLibrary);
}

void FontManager::loadFont(std::string fontName)
{
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
