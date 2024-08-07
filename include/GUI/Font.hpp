#ifndef FONT_HPP_
#define FONT_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace GUI
{
	
enum class CenteredAlign
{
	YES,
	NO
};
	
class Font
{
	
public:
	Font();
	Font(const char* p_path, int size);
	~Font();
	
	void openFont(const char* p_path, int size);
	void unload();
	
	TTF_Font* getFont() const { return font; }
	
	SDL_Texture* CreateTextTexture(SDL_Renderer* renderer, const char* text, SDL_Color color);

private:
	TTF_Font* font;
	
};

}

#endif
